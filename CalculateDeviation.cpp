/*
 * CalculateDeviation.cpp
 *
 *  Created on: May 13, 2018
 *      Author: gab
 */

#include "CalculateDeviation.hpp"
#include <stdio.h>
#include <math.h>
/*
CalculateDeviation::CalculateDeviation()
{
    //m_u16BITN = i_BITN;
}*/

uint8_t CalculateDeviation::run()
{
    //#########################
    // Calculate the deviation using the measurements on ADC output
    uint16_t l_x;
    uint16_t l_y;
    uint16_t l_z;

    l_x=ADC14->MEM[0];
    l_y=ADC14->MEM[1];
    l_z=ADC14->MEM[2];


    int yn; int zn;
    yn=l_y-8192;
    zn=l_z-8192;
    uint32_t l_h;
    h = (int32_t) (63 * yn / (sqrt(yn*yn+zn*zn)));
    l_h =(uint32_t) h;
    st_Message l_stMessage;
    l_stMessage.bMessageValid = true;
    l_stMessage.u8DestinationID = 0x2;
    l_stMessage.u8SourceID = 0x1;
    l_stMessage.u32MessageData = l_h;
    this->sendMessage(l_stMessage);
    //#########################
    return(NO_ERR);
}

uint8_t CalculateDeviation::setup()
{

    return(NO_ERR);
}


