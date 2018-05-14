/*
 * RefreshScreen.hpp
 *
 *  Created on: May 13, 2018
 *      Author: gab
 */

#ifndef REFRESHSCREEN_HPP_
#define REFRESHSCREEN_HPP_

#define __NOP __nop
#include <ti/devices/msp432p4xx/inc/msp.h>//#include "msp.h"
#include "Task.hpp"

extern "C"
{
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
}





class RefreshScreen : public Task
{
    public:
        //RefreshScreen();
        //uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
        int32_t currentH;
};




#endif /* REFRESHSCREEN_HPP_ */
