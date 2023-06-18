/**********************************************************************************************************************
 * Filename:    LCD.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the declaration of LCD APIs and essential MACROS
 * 
 *********************************************************************************************************************/

#ifndef LCD_H
#define	LCD_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* API Macros that correspond to LCD commands */
#define LCD_Clear() LCD_Cmd(0x01)
#define LCD_DecrementCursor() LCD_Cmd(0x04)
#define LCD_IncrementCursor() LCD_Cmd(0x05)
#define LCD_ShiftDisplayRight() LCD_Cmd(0x06)
#define LCD_ShiftDisplayLeft() LCD_Cmd(0x07)
#define LCD_ShiftRight() LCD_Cmd(0x1C)
#define LCD_ShiftLeft() LCD_Cmd(0x18)
#define LCD_ON()  LCD_Cmd(0x0C)
#define LCD_OFF() LCD_Cmd(0x08)


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* LCD struct that contains the LCD port and pins */    
typedef struct {
    volatile unsigned char*  PORT;  /* Pointer to the LCD port e.g &PORTC */
    unsigned RS :3;                 /* The RS bit of the LCD PORT e.g. 2  */
    unsigned EN :3;                 /* The EN bit of the LCD PORT e.g. 3  */
    unsigned D4 :3;                 /* The D4 bit of the LCD PORT e.g. 4  */
    unsigned D5 :3;                 /* The D5 bit of the LCD PORT e.g. 5  */
    unsigned D6 :3;                 /* The D6 bit of the LCD PORT e.g. 6  */
    unsigned D7 :3;                 /* The D7 bit of the LCD PORT e.g. 7  */
} LCD;
extern LCD lcd;         /* Global LCD struct */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/*                           Functions as MACROS                                      */

/* Sets the LCD cursor position  */
#define LCD_SetCursor( x, y )           \
    do {                                     \
        if ( x == 0 ) {                      \
            LCD_Cmd(0x80 + y);               \
        }                                    \
        else if ( x == 1 ) {                 \
            LCD_Cmd(0xC0 + y);               \
        }                                    \
        else if ( x == 2 ) {                 \
            LCD_Cmd(0x94 + y);               \
        }                                    \
        else if ( x == 3 ) {                 \
            LCD_Cmd(0xD4 + y);               \
        }                                    \
    } while ( 0 )

/* Sends a command to the LCD */
#define LCD_Cmd( c )                     \
        LCD_Write( (c & 0xF0) >> 4 );        \
        LCD_Write( c & 0x0F);        

/*                           Functions                                      */

/******************************************************************************
* \Syntax          : void LCD_Init(LCD display)        
* \Description     : Initializes the LCD (Based On LCD struct)              
*******************************************************************************/
void LCD_Init ( LCD display );

/******************************************************************************
* \Syntax          : void LCD_PutChar(char a)        
* \Description     : Prints a character on the LCD                
*******************************************************************************/
void LCD_PutChar ( char a );

/******************************************************************************
* \Syntax          : void LCD_PutString(char* a)        
* \Description     : Prints a string (array of characters) on the LCD.
*******************************************************************************/
void LCD_PutString ( char *a );

/******************************************************************************
* \Syntax          : void LCD_Write(unsigned char a)        
* \Description     : Write a byte to the LCD           
*******************************************************************************/
void LCD_Write ( unsigned char c );

#endif	/* LCD_H */

