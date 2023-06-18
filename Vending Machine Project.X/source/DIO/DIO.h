/**********************************************************************************************************************
 * Filename:    DIO.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the declaration of DIO APIs and essential MACROS for port & pin manipulation.
 * 
*********************************************************************************************************************/

#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* If INPUT is not previously defined ... then define it */
#ifndef INPUT
    #define INPUT 1
#endif

/* If OUTPUT is not previously defined ... then define it */
#ifndef OUTPUT
    #define OUTPUT 0
#endif

/* If HIGH is not previously defined ... then define it */
#ifndef HIGH
    #define HIGH 1
#endif

/* If LOW is not previously defined ... then define it */
#ifndef LOW
    #define LOW 0
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Enum for port names */
typedef enum 
{
    DIO_PORTA = 0,
    DIO_PORTB,
    DIO_PORTC
}DIO_port_e;

/* Enum for pin names */
typedef enum
{
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
}DIO_pin_e;

/* Enum for pin modes */
typedef enum
{
    DIO_OUTPUT_MODE = 10,
    DIO_INPUT_MODE_NOPULL = 11,
    DIO_INTERRUPT_CHANGE_MODE = 12
}DIO_mode_e;


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void DIO_setPinMode( enum port, enum pin, enum mode )
* \Description     : Choose the pin mode (output, input, interrupt change)
                     for a specific pin in a specific port.      
*******************************************************************************/
void DIO_setPinMode(DIO_port_e port, DIO_pin_e pin, DIO_mode_e mode);

/******************************************************************************
* \Syntax          : void DIO_setPinValue( enum port, enum pin, enum mode )       
* \Description     : Set the value (HIGH/LOW) of a specific pin in a specific port.   
*******************************************************************************/
void DIO_setPinValue(DIO_port_e port, DIO_pin_e pin, unsigned char value);


#endif /* DIO_H */