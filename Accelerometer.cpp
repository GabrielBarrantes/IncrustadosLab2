/*
 * Accelerometer.cpp
 *
 *  Created on: May 12, 2018
 *      Author: gab
 */

#include "Accelerometer.hpp"

/*Accelerometer::Accelerometer()
{
    //m_u16BITN = i_BITN;
}*/

uint8_t Accelerometer::run()
{
    //#########################
    // Trigger the conversion in the ADC,
    // the ADC14_IRQHandler( ) procedure run at the end of conversion
    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
    //#########################
    return(NO_ERR);
}

uint8_t Accelerometer::setup()
{
    // Set P6.1 for Analog input (X-Axis).
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;
    P6->DIR &= ~BIT1;
    // Set P4.0 for Analog input (Y-Axis).
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;
    P4->DIR &= ~BIT0;
    // Set P4.2 for Analog input (Z-Axis).
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;
    P4->DIR &= ~BIT2;
    //Configure the ADC
    ADC14->CTL0 = ADC14_CTL0_CONSEQ_1  |
                  ADC14_CTL0_PDIV_0    |
                  ADC14_CTL0_SHS_0     |
                  ADC14_CTL0_DIV_7     |
                  ADC14_CTL0_SSEL__MCLK|
                  ADC14_CTL0_SHT0_1    |
                  ADC14_CTL0_ON        |
                  ADC14_CTL0_SHP;
    //Configure the ADC memory outs, MCTL[0]= x, MCTL[1]= y, MCTL[2]= z
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_0| ADC14_MCTLN_EOS ;

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;
    ADC14->IER0 = ADC14_IER0_IE2;
    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);

    return(NO_ERR);
}


