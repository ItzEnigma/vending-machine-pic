/**********************************************************************************************************************
 * Filename:    LCD_prv.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the private declaration of LCD APIs and private MACROs, which are used internally.
 * 
*********************************************************************************************************************/

#ifndef LCD_PRV_H
#define LCD_PRV_H

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Display on, cursor off */
#define CMD_DISPLAY_ON      0b00001100
/* Display off */
#define CMD_DISPLAY_OFF     0b00001000


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : static void LCD_Write(char a)        
* \Description     : Private function used to output the data to the LCD Port
                     [USED INTERNALLY]      
*******************************************************************************/
static void LCD_Out ( char a );

#endif /* LCD_PRV_H */