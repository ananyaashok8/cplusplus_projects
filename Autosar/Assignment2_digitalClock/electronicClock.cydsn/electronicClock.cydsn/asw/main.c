/**
* \file main
* \author Peter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
* The file contains two cyclic tasks, whioch both access the same UART to create a critical region
* Depending on priority and timing configuration, the data may get corrupted.
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/


#include "project.h"
#include "global.h"

#include "swc_clock.h"
#include "tft.h"
#include "sp_common.h"
#include "sc_event_type.h"
#include "time.h"


SC_EVENT_data_t buttonStatus;

#undef TRC_SYSTICK

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}



int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();    
    
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers
    UART_LOG_Start();
    UART_LOG_PutString(" System started, uart working.. \n");
    
    TFT_init();
    TFT_setBacklight(255);    
    TFT_print("ELECTRONIC CLOCK \n");
    CLOCK__action_initClock();    
    
    
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    SetRelAlarm(alarm_50ms,100,100);
    SetRelAlarm(alarm_250ms,250,250);    
    SetRelAlarm(alarm_1min,60000,60000);   
    

    //Activate all extended and the background task    
    ActivateTask(tsk_control);
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}


TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


ISR2(isr_Button)
{

    if (BUTTON_1_Read() == 1) 
    {        
        buttonStatus.buttonPress = 1;          
    }
    
    if (BUTTON_2_Read() == 1) 
    {
        buttonStatus.buttonPress = 2; 
        CancelAlarm(alarm_250msEv); 
    }
    
    RTE_SC_EVENT_set(&SO_EVENT_signal,buttonStatus);     
    
}

/* [] END OF FILE */
