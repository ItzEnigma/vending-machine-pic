/**********************************************************************************************************************
 * Filename:    VM.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the declaration of Vending Machines APIs and essential MACROS and ENUMS for VM operation.
 * 
*********************************************************************************************************************/

#ifndef VM_H
#define VM_H



/**********************************************************************************************************************
 *  CONSTANT MACROS
 *********************************************************************************************************************/

#define     _ENABLE_GLOBAL_INTERRUPTS()       (INTCONbits.GIE = 1)
#define     _ENABLE_PERIPHERAL_INTERRUPTS()   (INTCONbits.PEIE = 1)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Vending Machine States */
typedef enum
{
    VM_STATE_INITIAL = 200,
    VM_STATE_DRINK_SELECTION,
    VM_STATE_COIN_INSERTION,
    VM_STATE_DRINK_DISPENSE,
    VM_STATE_DRINK_READY,
    VM_STATE_DISPENSE_CHANGE,
    VM_STATE_TILT_SENSING,
    VM_STATE_ALARM
}VM_state_e;

/* Vending Machine Drinks */
typedef enum
{
    VM_DRINK_COLA = 0,
    VM_DRINK_LEMONADE,
    VM_DRINK_ORANGE,
    VM_DRINK_WATER
}VM_drink_e;

/* Vending Machine Coins */
/* NOTE: Coins are divided by 10 here so that it wouldn't take program memory to make division. */
typedef enum
{
    VM_COIN_COLA_80         = 8,
    VM_COIN_LEMONADE_80     = 8,
    VM_COIN_ORANGE_60       = 6,
    VM_COIN_WATER_50        = 5,
}VM_coin_e;

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
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
void VM_Init(void);

/******************************************************************************
* \Syntax          : void VM_Running( void )       
* \Description     : to be called in main function to run the vending machine
*******************************************************************************/
void VM_Running(void);


#endif /* VM_H */