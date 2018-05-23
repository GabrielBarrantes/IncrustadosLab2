//#include "msp.h"
#include "main.hpp"
#include "globals.hpp"
#include "Scheduler.hpp"
#include "Task.hpp"
#include "LED.hpp"
#include "Accelerometer.hpp"
#include "CalculateDeviation.hpp"
#include "RefreshScreen.hpp"



extern "C"
{
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
}
// ##########################
// Global/Static declarations
// ##########################
uint8_t Task::m_u8NextTaskID = 0; // - Init task ID

volatile static uint64_t g_SystemTicks = 0; // - The system counter.

Mailbox* g_Mailbox = Mailbox::getMailbox();
Scheduler g_MainScheduler; // - Instantiate a Scheduler

// #########################
//          MAIN
// #########################
void main(void)
{
    // - Run the overall setup function for the system
    Setup();

    /////////////////////////////////////////////////////////////////////
    // - Instantiate the Tasks
    Accelerometer AccelerometerXYZ;
    CalculateDeviation Deviation;
    RefreshScreen Screen;
    LED BlueLED(BIT2);
    //LED GreenLED(BIT1);

    // - Attach the Tasks to the Scheduler;
    //////////////////////////////////////////////////////////////////////////////////////////
    g_MainScheduler.attach(& AccelerometerXYZ, TaskType_Periodic,TaskActiveTrue,1);
    g_MainScheduler.attach(& Deviation, TaskType_Periodic,TaskActiveTrue,1);
    g_MainScheduler.attach(& Screen, TaskType_Periodic,TaskActiveTrue,3);
    g_MainScheduler.attach(&BlueLED,TaskType_Periodic, TaskActiveTrue,500);
    //g_MainScheduler.attach(&GreenLED, TaskType_Periodic,TaskActiveTrue,1000);

    //////////////////////////////////////////////////////////////////////////////////////////

    // - Run the Setup for the scheduler and all tasks
    g_MainScheduler.setup();
    // - Main Loop
    while(1)
    {
        //Graphics_fillRectangle(const Graphics_Context *context,const Graphics_Rectangle *rect);
        //Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);

    	__wfe(); // Wait for Event
        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //- Only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }
}

// **********************************
// Setup function for the application
// @input - none
// @output - none
// **********************************
void Setup(void)
{
	// ****************************
	//         DEVICE CONFIG
	// ****************************
	// - Disable WDT
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	// ****************************
	//         PORT CONFIG
	// ****************************
	// - P1.0 is connected to the Red LED
	// - This is the heart beat indicator.
	P1->DIR |= BIT0; //Red LED

	// ****************************
	//       TIMER CONFIG
	// ****************************
	// - Configure Timer32_1  with MCLK (3Mhz), Division by 1, Enable the interrupt, Periodic Mode
	// - Enable the interrupt in the NVIC
	// - Start the timer in UP mode.
	// - Re-enable interrupts
	TIMER32_1->LOAD = TIMER32_COUNT; //~1ms ---> a 48Mhz
	TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
	NVIC_SetPriority(T32_INT1_IRQn,1);
	NVIC_EnableIRQ(T32_INT1_IRQn);
	__enable_irq();

    // ****************************
    //       SCREEN CONFIG
    // ****************************
    /////////////////////////////////////////////////////////////////////
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);

    Graphics_clearDisplay(&g_sContext);

    Graphics_setForegroundColor(&g_sContext, 0x000000FF);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 0;
    g_sRectangle.yMin = 63;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
    //Graphics_drawLineH(&g_sContext, 0, 127, 63);

    Graphics_setForegroundColor(&g_sContext, 0x00DAA520);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 64;
    g_sRectangle.yMin = 127;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
	return;
}

extern "C"
{
    // - Handle the Timer32 Interrupt
	void T32_INT1_IRQHandler(void)
	{
		TIMER32_1->INTCLR = 0U;
		P1->OUT ^= BIT0; // - Toggle the heart beat indicator (1ms)
		g_SystemTicks++;
		return;
	}

	void ADC14_IRQHandler(void)
	{
	    __disable_irq();

	    //ENVIAR MENSAJE AL SHEDUCLER CON LAS COORDENADAS

	    x=ADC14->MEM[0];
	    y=ADC14->MEM[1];
	    z=ADC14->MEM[2];


	    ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
	    __enable_irq();
	    return;
	}
}
