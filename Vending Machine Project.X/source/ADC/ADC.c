/**********************************************************************************************************************
 * Filename:    ADC.c
 * Version:     1.0
 * Date:        02/5/2023
 * Author:      Hosam Mohamed
 *
 * Description: Contains the implementation of ADC APIs for using the ADC peripheral.
 * 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include <xc.h>
#include "ADC.h"

/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void ADC_Init()       
* \Description     : Initialize the ADC (Freq & Vref & Resolution).
*******************************************************************************/
void ADC_Init( )
{
    ADCON0 &= ~(ADC_CLK_FREQ << 6);     /* Reset Clock */
    ADCON0 |= (ADC_CLK_FREQ << 6);      /* Choose ADC CLK Frequency */
    
    /* Using Internal Vref   */
    /* Choose ADC Resolution */
#if     ADC_RESOLUTION_10_BIT == 1
    ADCON1 = 0x80;
#elif   ADC_RESOLUTION_10_BIT == 0
    ADCON1 = 0x00;
#endif
    /* Enable ADC */
    ADCON0 |= 0x01;
}

/******************************************************************************
* \Syntax          : unsigned int ADC_Read( enum channel )       
* \Description     : Read the ADC value of a specified channel
*******************************************************************************/
unsigned int ADC_Read(ADC_channel_t channel)
{
    unsigned int result;        /* Variable to store the result */
    
    /* Enable analog input for this channel */
    if(channel < 5)     /* Channel is in PORTA */
    {
        ANSEL |= (1 << channel);
        /* Choose channel */
        ADCON0 |= (channel << 2);
    }
    else                /* Channel is in PORTB */
    {
        /* Enable Analog Input for the corresponding pin in PORTB */
            ANSELH |= ( 1<< (channel-8) );
            /* Choose channel */
            ADCON0 |= (channel << 2);
    }
    ADCON0bits.GO = 1;          /* Set GO Bit to start conversion */
    while(ADCON0bits.GO==1);    /* Wait for GO bit to clear=conversion complete */
    
#if     ADC_RESOLUTION_10_BIT == 1
    result =(ADRESH<<8)+ADRESL; /* Combine to produce final 10 bit result */
#elif   ADC_RESOLUTION_10_BIT == 0
    result = ADRESH;             /* 8-bit result */
#endif
    return result;
}


/**********************************************************************************************************************
 *  END OF FILE: ADC.c
 *********************************************************************************************************************/