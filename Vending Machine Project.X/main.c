/**********************************************************************************************************************
 * Filename:    main.c
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the main application that runs the vending machine.
 * 
 *********************************************************************************************************************/

/* Clock Frequency */
#define _XTAL_FREQ 4000000UL


/* Configuration bits */
#pragma config FOSC = HS        /*     High-speed crystal oscillator       */
#pragma config WDTE = OFF       /*     Watchdog Timer off                  */
#pragma config PWRTE = OFF      /*     Power-up Timer off                  */
#pragma config CP = OFF         /*     Code Protection off                 */
#pragma config BOREN = OFF      /*     Brown-out Reset off                 */
#pragma config LVP = OFF        /*     Low Voltage Programming off         */        
#pragma config CPD = OFF        /*     Data Code Protection off            */        
#pragma config WRT = OFF        /*     Flash Memory Write Protection off   */                

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h>
#include "source/VendingMachine/VM.h"


/*               Main Function                   */

void main()
{
    /* Initialize the Vending Machine */
    VM_Init();
    
    /* Run the Vending Machine */
    while(1)
    {
        VM_Running();
    }
}
