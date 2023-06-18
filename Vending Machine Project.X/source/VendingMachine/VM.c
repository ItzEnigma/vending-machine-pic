/**********************************************************************************************************************
 * Filename:    VM.c
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the implementation of DIO APIs for port & pin manipulation.
 * 
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h>

#include "VM.h"
#include "VM_prv.h"
#include "../DIO/DIO.h"
#include "../ADC/ADC.h"
#include "../LCD/LCD.h"


/**********************************************************************************************************************
 *  CONSTANT MACROS
 *********************************************************************************************************************/

/* Number of overflows with period value = 142 to generate 2 Hz Signal */
#define         TIMER2_NO_OF_OVERFLOWS_2HZ           (unsigned char) 22

/* 2V VR */
#define     TILT_SWITCH_VOLT_ADC        0x199

/* Display Entire space in row (to clear it) */
#define     _LCD_SPACE_ROW()              ( LCD_PutString("          "))

/* Display Zero + spaces */
#define     _LCD_0_SPACE_ROW()              ( LCD_PutString("0              "))

/* Display Progress Bar */
#define     _LCD_DISPLAY_PROGRESS()         (LCD_PutString("...."))

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/

static unsigned int adc_val = 0;                                /* ADC Value */

/* Temp variable to store the value of deciaml to ASCII */
static char temp[2] = {0};

/* Static Global Variables */
static volatile unsigned char gCurrentState = VM_STATE_INITIAL; /* Current State of the Vending Machine */
static volatile unsigned char gCurrentDrink = 0;                /* Current Selected Drink */
static volatile signed char gCurrentDrinkPrice = 0;             /* Current Selected Drink Price */

/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void VM_Init( void )       
* \Description     : initializes system components and enter drink selection mode
                        --> Push Buttons: interrupt-on-change
                        --> LCD: 4-bit mode
                        --> LEDs: output simulating dispensers
                        --> Buzzer: output
                        --> Potentiometer (VR2): ADC simulating tilt-sensor
*******************************************************************************/
void VM_Init(void)
{
    /* Current State --> Initial State */
    gCurrentState = VM_STATE_INITIAL;

    /* LEDs RA0 and RA1 --> Output and LOW initially */
    DIO_setPinMode(DIO_PORTA, DIO_PIN0, DIO_OUTPUT_MODE);
    DIO_setPinMode(DIO_PORTA, DIO_PIN1, DIO_OUTPUT_MODE);
    DIO_setPinValue(DIO_PORTA, DIO_PIN0, LOW);
    DIO_setPinValue(DIO_PORTA, DIO_PIN1, LOW);
    /* Alarm Buzzer RA2 --> Output and LOW initially */
    DIO_setPinMode(DIO_PORTA, DIO_PIN2, DIO_OUTPUT_MODE);
    DIO_setPinValue(DIO_PORTA, DIO_PIN0, LOW);
    /* Push Buttons RB0, RB1 and RB2 interrupt-on-change */
    DIO_setPinMode(DIO_PORTB, DIO_PIN0, DIO_INTERRUPT_CHANGE_MODE);
    DIO_setPinMode(DIO_PORTB, DIO_PIN1, DIO_INTERRUPT_CHANGE_MODE);
    DIO_setPinMode(DIO_PORTB, DIO_PIN2, DIO_INTERRUPT_CHANGE_MODE);

    /* Init ADC to use VR2 (tilt-sensor simulation) */
    ADC_Init();
    
    /* Timer2 Configuration */
    T2CONbits.TMR2ON = 0;       /* Disable Timer2 */
    T2CONbits.T2CKPS = 3;       /* Prescaler 1:16 */
    T2CONbits.TOUTPS = 0x9;     /* Postscaler 1:10 */
    PIE1bits.TMR2IE = 1;        /* Enable Timer2 Interrupt */
    PIR1bits.TMR2IF = 0;        /* Clear Timer2 Flag */
    PR2 = 0x8E;                 /* Load Timer2 Period Register */
    T2CONbits.TMR2ON = 1;       /* Enable Timer2 */
    TMR2 = 0;
    
    /* LCD INIT */
    LCD lcd = { &PORTC, 0, 3, 4, 5, 6, 7 }; /* PORT, RS, EN, D4, D5, D6, D7 */
    LCD_Init(lcd);
    LCD_Clear();
    
    _ENABLE_GLOBAL_INTERRUPTS();             /* Enable Global Interrupts (GIE) */
    _ENABLE_PERIPHERAL_INTERRUPTS();         /* Enable peripheral interrupts   */
    
    /* Enter Drink Selection Mode */
    /* Current State --> Drink Selection State */
    gCurrentState = VM_STATE_DRINK_SELECTION;
    /* Current Drink --> Cola Drink */
    gCurrentDrink = VM_DRINK_COLA;
    
    LCD_SetCursor(0,0);
    LCD_PutString("Select Drink:");
}

/******************************************************************************
* \Syntax          : void VM_Running( void )       
* \Description     : to be called in main function to run the vending machine
*******************************************************************************/
void VM_Running(void)
{
    /* If final state reached (Drink Ready) ... reset Vending Machine */
    if(gCurrentState == VM_STATE_INITIAL)
        VM_Init();        /* Reset Vending Machine */
        
    /* Check Current State and Execute the corresponding function */
    switch (gCurrentState)
    {
    case VM_STATE_DRINK_SELECTION:
        VM_Mode_DrinkSelection();
        break;
    case VM_STATE_COIN_INSERTION:
        VM_Mode_CoinInsertion();
        break;
    case VM_STATE_DRINK_DISPENSE:
        VM_Mode_DispenseDrink();
        break;
    case VM_STATE_DRINK_READY:
        LCD_SetCursor(0,0);
        LCD_PutString("Please Collect    ");
        LCD_SetCursor(1,0);
        LCD_PutString("Your Drink!     ");
        /* Using Timer1 to generate 5s Delay */
        TIMR1_Delay5s();
        gCurrentState = VM_STATE_INITIAL;       /* Reset Vending Machine State */
        break;
    case VM_STATE_DISPENSE_CHANGE:
        VM_Mode_DispenseChange();
        break;
    default:
        break;
    }
}


/******************************************************************************
* \Syntax          : static void VM_Mode_DrinkSelection( void )       
* \Description     : Private function used to provide a user interface through
                     which the customer can select a drink and view the prices
                     [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DrinkSelection(void)
{
    /* Display the current selected drink and its price */
    LCD_SetCursor(1,0);
    switch (gCurrentDrink)
    {
        case VM_DRINK_COLA:
            LCD_PutString("Cola 80p      ");
            break;
        case VM_DRINK_LEMONADE:
            LCD_PutString("Lemonade 80p");
            break;
        case VM_DRINK_ORANGE:
            LCD_PutString("Orange 60p    ");
            break;
        case VM_DRINK_WATER:
            LCD_PutString("Water 50p     ");
            break;
    }
}

/******************************************************************************
* \Syntax          : static void VM_Mode_CoinInsertion( void )       
* \Description     : Private function used to simulate the insertion of coins
                     by the customer and the display updates to show the
                     outstanding balance [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_CoinInsertion(void)
{
    /* If drink price is not paid yet */
    if(gCurrentDrinkPrice > 0)
    {
        /* Convert decimal value to ASCII character to be displayed */
        temp[0] = '0' + (gCurrentDrinkPrice);
    
        /* Display the following on LCD */
        LCD_SetCursor(0,0);
        LCD_PutString("Insert Coins:  ");
        LCD_SetCursor(1,0);
        LCD_PutString(temp);
        _LCD_0_SPACE_ROW();
    }
    else if (gCurrentDrinkPrice <= 0)               /* Dispense Drink */
        gCurrentState = VM_STATE_DRINK_DISPENSE;
}

/******************************************************************************
* \Syntax          : static void VM_Mode_DispenseDrink( void )       
* \Description     : Private function used to simulate dispensing of the drink
                     by using LED and update LCD display [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DispenseDrink(void)
{
        DIO_setPinValue(DIO_PORTA, DIO_PIN0, HIGH);     /* RA0 HIGH */
        /* Display the following on LCD */
        LCD_SetCursor(0,0);
        LCD_PutString("Drink Dispensing");
        LCD_SetCursor(1,0);
        _LCD_SPACE_ROW();
        LCD_SetCursor(1,0);
        /* Using Timer0 to generate 5s Delay */
        OPTION_REGbits.T0CS = 0;    /* Set clock source to internal (timer mode) */
        OPTION_REGbits.PSA = 0;     /* Set prescaler to Timer 0                  */
        OPTION_REGbits.PS = 7;      /* Set prescaler bits to 111 for 1:256       */
        for(unsigned char i=0 ; i<76 ; i++)
        {
            while (!INTCONbits.TMR0IF); /* Delay loop: Wait until TMR0 overflows */
            if(i == 1)
                    _LCD_DISPLAY_PROGRESS();
            else if(i == 20)
                    _LCD_DISPLAY_PROGRESS();
            else if(i == 40)
                    _LCD_DISPLAY_PROGRESS();
            else if(i == 70)
                    _LCD_DISPLAY_PROGRESS();
            INTCONbits.TMR0IF = 0;  /* Reset overflow flag, TMR0IF */
        }
        DIO_setPinValue(DIO_PORTA, DIO_PIN0, LOW);     /* RA0 LOW */
        if(gCurrentDrinkPrice == 0)         /* No Change */
            gCurrentState = VM_STATE_DRINK_READY;
        else                                /* There is change */
            gCurrentState = VM_STATE_DISPENSE_CHANGE;
}

/******************************************************************************
* \Syntax          : static void VM_Mode_DispenseChange( void )       
* \Description     : Private function used to simulate dispensing of the change
                     by using LED and update LCD display [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DispenseChange(void)
{
    /* Calculate the number of coins to be dispensed */
    char change_count = 0;
    while(gCurrentDrinkPrice != 0)    /* While there is still change */
        {
            gCurrentDrinkPrice++;
            change_count++;
        }
        /* Convert decimal value to ASCII character to be displayed */
        temp[0] = '0' + (change_count);

        DIO_setPinValue(DIO_PORTA, DIO_PIN1, HIGH);     /* RA1 HIGH */
        LCD_SetCursor(0,0);
        LCD_PutString("Change due:     ");
        LCD_SetCursor(1,0);
        LCD_PutString(temp);
        _LCD_0_SPACE_ROW();
        /* Using Timer1 to generate 5s Delay */
        TIMR1_Delay5s();
        DIO_setPinValue(DIO_PORTA, DIO_PIN1, LOW);     /* RA1 LOW */
        gCurrentState = VM_STATE_DRINK_READY;
}

/******************************************************************************
* \Syntax          : static void TIMR1_Delay5s( void )       
* \Description     : Private function used to generate 5s delay using Timer1
                     (Polling Mode) [USED INTERNALLY].
*******************************************************************************/
static void TIMR1_Delay5s(void)
{
    T1CON= 0x31;        /* Timer 1, internal clock, 1:8 prescaler */
    TMR1 = 0x76C8;      /* Preload */
    for(unsigned char i=0 ; i<10 ; i++)
    {
        while (!PIR1bits.TMR1IF); /* Delay loop: Wait until TMR1 overflows */
        PIR1bits.TMR1IF = 0;      /* Reset overflow flag */
    }
}

/*************************************************************************************/
/************************** Interrupt service routine (ISR) **************************/
/*************************************************************************************/
void __interrupt() myISR(void)
{
    static volatile unsigned char timer_count = 0;
    
    if (INTCONbits.RBIF) /* If RB interrupt flag is set */
    {
        if (PORTBbits.RB0 == 0) /* If SW0 is pressed (RB0 is low) */
        {
           switch (gCurrentState)
              {
                case VM_STATE_DRINK_SELECTION:
                    if(gCurrentDrink < VM_DRINK_WATER)
                        gCurrentDrink++;                    /* Update Current Drink */
                    else
                        gCurrentDrink = VM_DRINK_COLA;      /* First Drink */
                    break;
                /* Insert 10 coins */
                case VM_STATE_COIN_INSERTION:
                    gCurrentDrinkPrice -= 1;      /* Update Current Drink Price */
                    break;
              }
        }
        else if (PORTBbits.RB1 == 0) /* If SW1 is pressed (RB1 is low) */
        {
            switch (gCurrentState)
              {
                case VM_STATE_DRINK_SELECTION:
                    gCurrentState = VM_STATE_COIN_INSERTION; /* Update Current State */
                    switch (gCurrentDrink)
                    {
                        case VM_DRINK_COLA:
                            gCurrentDrinkPrice = VM_COIN_COLA_80;        /* Update Current Drink Price */
                            break;
                        case VM_DRINK_LEMONADE:
                            gCurrentDrinkPrice = VM_COIN_LEMONADE_80;        /* Update Current Drink Price */
                            break;
                        case VM_DRINK_ORANGE:
                            gCurrentDrinkPrice = VM_COIN_ORANGE_60;        /* Update Current Drink Price */
                            break;
                        case VM_DRINK_WATER:
                            gCurrentDrinkPrice = VM_COIN_WATER_50;        /* Update Current Drink Price */
                            break;
                    }
                    break;
                    /* Insert 20 coins */
                    case VM_STATE_COIN_INSERTION:
                    gCurrentDrinkPrice -= 2;      /* Update Current Drink Price */
                    break;
              }
        }
        else if (PORTBbits.RB2 == 0) /* If SW2 is pressed (RB2 is low) */
        {
            switch (gCurrentState)
            {
                /* Inset 50 coins */
                case VM_STATE_COIN_INSERTION:
                    gCurrentDrinkPrice -= 5;      /* Update Current Drink Price */
                    break;
            }
        }
        INTCONbits.RBIF = 0;         /* Clear RB interrupt flag */
        return;
    }
    if (PIR1bits.TMR2IF)
    {
        timer_count++;
        /* Checks every 500ms the tilt sensor (VR2) for anti-theft detection */
        if(timer_count == TIMER2_NO_OF_OVERFLOWS_2HZ)
        {
            timer_count = 0;                            /* Reset Counter */
            adc_val = ADC_Read(ADC9);           /* Read ADC Channel 9 (VR2) */
            if(adc_val > TILT_SWITCH_VOLT_ADC)  /* If VR2 > 2V */
                DIO_setPinValue(DIO_PORTA, DIO_PIN2, HIGH);     /* Turn on Alarm Buzzer */
            else
                DIO_setPinValue(DIO_PORTA, DIO_PIN2, LOW);      /* Turn off Alarm Buzzer */
        }
        PIR1bits.TMR2IF = 0; /* Reset interrupt flag */
        return;
    }
}



/**********************************************************************************************************************
 *  END OF FILE: VM.c
 *********************************************************************************************************************/