/**********************************************************************************************************************
 * Filename:    ADC.h
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the declaration of ADC APIs and essential MACROS for using the ADC peripheral.
 * NOTE:        The ADC corresponds to PORTA starting from RA0 : RA5.
 * NOTE:        This file contains configuration for ADC (such using 8-bit or 10-bit value, adc clk frequency, etc.)
 * 
*********************************************************************************************************************/

#ifndef ADC_H
#define ADC_H


/**********************************************************************************************************************
 *  Configuration
 *********************************************************************************************************************/

/* Choose ADC Resolution:
    1      -->      ADC Resolution 10-bit
    0      -->      ADC Resolution 8-bit
*/
#define     ADC_RESOLUTION_10_BIT    1

/* Choose ADC Frequency:
    0      -->      ADC CLK = Fosc/2
    1      -->      ADC CLK = Fosc/8
    2      -->      ADC CLK = Fosc/32
    3      -->      ADC CLK = Frc
*/
#define     ADC_CLK_FREQ            1


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* ADC Channels */
typedef enum
{
    ADC0 = 0,
    ADC1 = 1,
    ADC2 = 2,
    ADC3 = 3,
    ADC4 = 4,
    ADC8 = 8,
    ADC9 = 9,
    ADC10 = 10,
    ADC11 = 11,
    ADC12 = 12,
    ADC13 = 13
}ADC_channel_t;


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void ADC_Init()       
* \Description     : Initialize the ADC (Freq & Vref & Resolution).
*******************************************************************************/
void ADC_Init();

/******************************************************************************
* \Syntax          : unsigned int ADC_Read( enum channel )       
* \Description     : Read the ADC value of a specified channel
*******************************************************************************/
unsigned int ADC_Read(ADC_channel_t channel);


#endif /* ADC_H */