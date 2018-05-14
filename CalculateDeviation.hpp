/*
 * CalculateDeviation.hpp
 *
 *  Created on: May 13, 2018
 *      Author: gab
 */

#ifndef CALCULATEDEVIATION_HPP_
#define CALCULATEDEVIATION_HPP_

#define __NOP __nop
#include "globals.hpp"
#include <ti/devices/msp432p4xx/inc/msp.h>//#include "msp.h"
#include "Task.hpp"
#include "Mailbox.hpp"


class CalculateDeviation : public Task
{
    public:
        //CalculateDeviation();
        //uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
};



#endif /* CALCULATEDEVIATION_HPP_ */
