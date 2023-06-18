/**********************************************************************************************************************
 * Filename:    VM.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the private declaration of Vending Machine APIs and private MACROs, which are used internally
 * 
*********************************************************************************************************************/

#ifndef  VM_PRV_H
#define  VM_PRV_H

/******************************************************************************
* \Syntax          : static void VM_Mode_DrinkSelection( void )       
* \Description     : Private function used to provide a user interface through
                     which the customer can select a drink and view the prices
                     [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DrinkSelection(void);

/******************************************************************************
* \Syntax          : static void VM_Mode_CoinInsertion( void )       
* \Description     : Private function used to simulate the insertion of coins
                     by the customer and the display updates to show the
                     outstanding balance [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_CoinInsertion(void);

/******************************************************************************
* \Syntax          : static void VM_Mode_DispenseDrink( void )       
* \Description     : Private function used to simulate dispensing of the drink
                     by using LED and update LCD display [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DispenseDrink(void);

/******************************************************************************
* \Syntax          : static void VM_Mode_DispenseChange( void )       
* \Description     : Private function used to simulate dispensing of the change
                     by using LED and update LCD display [USED INTERNALLY].
*******************************************************************************/
static void VM_Mode_DispenseChange(void);

/******************************************************************************
* \Syntax          : static void TIMR1_Delay5s( void )       
* \Description     : Private function used to generate 5s delay using Timer1
                     (Polling Mode) [USED INTERNALLY].
*******************************************************************************/
static void TIMR1_Delay5s(void);


#endif  /* VM_PRV_H */