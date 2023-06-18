/**********************************************************************************************************************
 * Filename:    DIO.c
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
#include "DIO.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void DIO_setPinDir( enum port, enum pin, enum mode )       
* \Description     : Private function used to set the direction of a pin
                     in a specific port.
*******************************************************************************/
static void DIO_setPinDir(DIO_port_e port, DIO_pin_e pin, unsigned char direction);


/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void DIO_setPinDir( enum port, enum pin, enum mode )       
* \Description     : Private function used to set the direction of a pin
                     in a specific port.
*******************************************************************************/
static void DIO_setPinDir(DIO_port_e port, DIO_pin_e pin, unsigned char direction)
{
    /* Set the direction of the pin in the corresponding port */
    switch(port)
    {
        case DIO_PORTA:
            if(direction == OUTPUT)
                TRISA &= ~(1 << pin);
            else
                TRISA |= (1 << pin);
            break;
        case DIO_PORTB:
            if(direction == OUTPUT)
                TRISB &= ~(1 << pin);
            else
                TRISB |= (1 << pin);
            break;
        case DIO_PORTC:
            if(direction == OUTPUT)
                TRISC &= ~(1 << pin);
            else
                TRISC |= (1 << pin);
            break;
        default:
            break;
    }
}

/******************************************************************************
* \Syntax          : void DIO_setPinMode( enum port, enum pin, enum mode )
* \Description     : Choose the pin mode (output, input, interrupt change)
                     for a specific pin in a specific port.      
*******************************************************************************/
void DIO_setPinMode(DIO_port_e port, DIO_pin_e pin, DIO_mode_e mode)
{
    /* Set the mode of the pin in the corresponding port */
    switch(port)
    {
        case DIO_PORTA:
                ANSEL &= ~(1<<pin); /* Disable Analog Input for the corresponding pin in PORTA */
            switch(mode)
            {
                case DIO_OUTPUT_MODE:
                    DIO_setPinDir(port, pin, OUTPUT);
                    break;
                case DIO_INPUT_MODE_NOPULL:
                    DIO_setPinDir(port, pin, INPUT);
                    break;
                default:    /* Incorrect Mode */
                    break;
            }
            break;
        case DIO_PORTB:
            /* Disable Analog Input for the corresponding pin in PORTB */
            if(pin == 0)
                ANSELH &= ~(1<<4);
            else if (pin == 1)
                ANSELH &= ~(1<<2);
            else if (pin == 2)
                ANSELH &= ~(1<<0);
            else if (pin == 3)
                ANSELH &= ~(1<<1);
            else if (pin == 4)
                ANSELH &= ~(1<<3);
            else if (pin == 5)
                ANSELH &= ~(1<<5);

            switch(mode)
            {
                case DIO_OUTPUT_MODE:
                    DIO_setPinDir(port, pin, OUTPUT);
                    break;
                case DIO_INPUT_MODE_NOPULL:
                    DIO_setPinDir(port, pin, INPUT);
                    break;
                case DIO_INTERRUPT_CHANGE_MODE:
                    /* Note: Global Interrupt will still need to be enabled! */
                    DIO_setPinDir(port, pin, INPUT);
                    IOCB |= 1<<pin;             /* Enable interrupt-on-change to corresponding bit in PORTB */
                    INTCONbits.RBIF = 0;        /* Clear RB interrupt flag           */
                    INTCONbits.RBIE = 1;        /* Enable RB interrupt-on-change     */
                    break;
                default:    /* Incorrect Mode */
                    break;
            }
            break;
        case DIO_PORTC:
            switch(mode)
            {
                case DIO_OUTPUT_MODE:
                    DIO_setPinDir(port, pin, OUTPUT);
                    break;
                case DIO_INPUT_MODE_NOPULL:
                    DIO_setPinDir(port, pin, INPUT);
                    break;
                default:    /* Incorrect Mode */
                    break;
            }
            break;
    }
}

/******************************************************************************
* \Syntax          : void DIO_setPinValue( enum port, enum pin, enum mode )       
* \Description     : Set the value (HIGH/LOW) of a specific pin in a specific port.   
*******************************************************************************/
void DIO_setPinValue(DIO_port_e port, DIO_pin_e pin, unsigned char value)
{
    /* Set the value of the pin in the corresponding port */
    switch(port)
    {
        case DIO_PORTA:
            if(value == LOW)
                PORTA &= ~(1 << pin);
            else
                PORTA |= (1 << pin);
            break;
        case DIO_PORTB:
            if(value == LOW)
                PORTB &= ~(1 << pin);
            else
                PORTB |= (1 << pin);
            break;
        case DIO_PORTC:
            if(value == LOW)
                PORTC &= ~(1 << pin);
            else
                PORTC |= (1 << pin);
            break;
        default:    /* Incorrect Value */
            break;
    }
}


/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/