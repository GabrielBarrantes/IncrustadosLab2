/*
 * globals.hpp
 *
 *  Created on: May 13, 2018
 *      Author: gab
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

extern "C"
{
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
}

//Mailbox* g_Mailbox = Mailbox::getMailbox();
//Scheduler g_MainScheduler; // - Instantiate a Scheduler

uint16_t x; //= 0U;
uint16_t y; //= 0U;
uint16_t z; //= 0U;
int32_t  h; //= 0U;

Graphics_Context g_sContext;
Graphics_Rectangle g_sRectangle;



#endif /* GLOBALS_HPP_ */
