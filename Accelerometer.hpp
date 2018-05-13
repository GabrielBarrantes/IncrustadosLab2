/*
 * Accelerometer.hpp
 *
 *  Created on: May 12, 2018
 *      Author: gab
 */

#ifndef ACCELEROMETER_HPP_
#define ACCELEROMETER_HPP_

#define __NOP __nop
#include "msp.h"
#include "Task.hpp"


class Accelerometer : public Task
{
    public:
        Accelerometer();
        //uint16_t m_u16BITN;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
    protected:
    private:
};

#endif /* ACCELEROMETER_HPP_ */
