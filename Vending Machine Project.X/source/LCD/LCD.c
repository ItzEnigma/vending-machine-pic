/**********************************************************************************************************************
 * Filename:    LCD.c
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the implementation of LCD APIs
 * 
 *********************************************************************************************************************/

#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000UL
#endif

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h>
#include "LCD.h"
#include "LCD_prv.h"

/* LCD Struct Object */
LCD lcd;


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void LCD_Write(char a)        
* \Description     : Private function used to output the data to the LCD Port
                     [USED INTERNALLY]       
*******************************************************************************/
static void LCD_Out ( char c ) {

    if ( c & 1 ){
        *(lcd.PORT) |= 1 << lcd.D4;
    }
    else {
         *(lcd.PORT) &= ~(1 << lcd.D4);
    }

    if ( c & 2 ) {
        *(lcd.PORT) |= 1 << lcd.D5;
    }
    else {
        *(lcd.PORT) &= ~(1 << lcd.D5);
    }

    if ( c & 4 ) {
        *(lcd.PORT) |= 1 << lcd.D6;
    }
    else {
        *(lcd.PORT) &= ~(1 << lcd.D6);
    }

    if ( c & 8 ) {
         *(lcd.PORT) |= 1 << lcd.D7;
    }
    else {
         *(lcd.PORT) &= ~(1 << lcd.D7);
    }
}

/******************************************************************************
* \Syntax          : void LCD_Write(unsigned char a)        
* \Description     : Write a byte to the LCD           
*******************************************************************************/
void LCD_Write ( unsigned char c ) {

    *(lcd.PORT) &= ~(1 << lcd.RS); // => RS = 0
    LCD_Out(c);

    *(lcd.PORT) |= 1 << lcd.EN;    // => E = 1
    __delay_ms(4);
    *(lcd.PORT) &= ~(1 << lcd.EN); // => E = 0
}

/******************************************************************************
* \Syntax          : void LCD_Init(LCD display)        
* \Description     : Initializes the LCD (Based On LCD struct)              
*******************************************************************************/
void LCD_Init ( LCD display ) {
    /* Initialize the LCD struct */
    lcd = display;

    /* Set the LCD pins as output */
    if ( lcd.PORT == &PORTA ) {
        TRISA = 0x00;
    }
    else if ( lcd.PORT == &PORTB ) {
        TRISB = 0x00;
    }
    else if ( lcd.PORT == &PORTC ) {
        TRISC = 0x00;
    }

    // Give some time to the LCD to start function properly
    __delay_ms(20);

    // Send reset signal to the LCD
    LCD_Write(0x03);
    __delay_ms(5);
    LCD_Write(0x03);
    __delay_ms(16);
    LCD_Write(0x03);

    // Specify the data lenght to 4 bits
    LCD_Write(0x02);

    // Set interface data length to 8 bits, number of display lines to 2 and font to 5x8 dots
    LCD_Cmd(0x28);

    // Set cursor to move from left to right
    LCD_Cmd(0x06);
    
    /* Turn LCD ON */
    LCD_ON();
}

/******************************************************************************
* \Syntax          : void LCD_PutChar(char a)        
* \Description     : Prints a character on the LCD                
*******************************************************************************/
void LCD_PutChar ( char c ) {
    // Set the LCD to write mode
   *(lcd.PORT) |= 1 << lcd.RS;   // => RS = 1
    LCD_Out((c & 0xF0) >> 4);    // Data transfer
    
    *(lcd.PORT) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PORT) &= ~(1 << lcd.EN);

    LCD_Out(c & 0x0F);

    *(lcd.PORT) |= 1 << lcd.EN;
    __delay_us(40);
    *(lcd.PORT) &= ~(1 << lcd.EN);
}

/******************************************************************************
* \Syntax          : void LCD_PutString(char* a)        
* \Description     : Prints a string (array of characters) on the LCD.
*******************************************************************************/
void LCD_PutString ( char *a ) {

    for ( int i = 0; a[i] != '\0'; ++i ) {
        LCD_PutChar(a[i]);
    }
}


/**********************************************************************************************************************
 *  END OF FILE: LCD.c
 *********************************************************************************************************************/