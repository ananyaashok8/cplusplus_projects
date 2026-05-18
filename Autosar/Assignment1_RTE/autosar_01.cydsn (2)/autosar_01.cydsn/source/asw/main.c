/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"

#include "joystick.h"
#include "tsk_io.h"
#include "tsk_control.h"
#include "tsk_system.h"
#include "watchdog.h"

#if 0
#include "button.h"
#include "led.h"
#include "seven.h"
#endif

uint8 bitfield = {0};
boolean_t testTerminateFlag = FALSE;
char testcase = ' ';   

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}
void forceShutdownOS();
void checkFault();

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();  
    
    
    
    WD_Start(WDT_1024_TICKS);
    
   
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
    //LED_Init();
    //SEVEN_Init();
    JOYSTICK_Init();
    PWM_Green_Start();
    
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	UART_1_Start();
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();    
	
    //Start the alarm with 1ms cycle time
    SetRelAlarm(alarm_10ms,10,10);
    SetRelAlarm(alarm_1ms,1,1);
    SetRelAlarm(alarm_25ms,250,250);
 
    ActivateTask(tsk_io);
    ActivateTask(tsk_control);
    ActivateTask(tsk_background);
    ActivateTask(tsk_testcase);
    
    UART_1_PutString(" Choose the testcase to perform: \n");
    UART_1_PutString(" a - watchdog force shutdown \n");
    UART_1_PutString(" b - alive monitoring by terminating control task \n");
    
    checkFault();
    
    TerminateTask();
    
}

TASK(tsk_testcase)
{    
    
    testcase = UART_1_GetChar();
    
    switch(testcase)
    {
        case 'a':
                    UART_1_PutString(" testcase 1 \n");  
                    testTerminateFlag = TRUE;                                      
                    break;
        case 'b':
                    UART_1_PutString(" testcase 2 \n");
                    forceShutdownOS();                    
                    break;
        default:
                    break;        
    
    }    
}

TASK(tsk_background)
{
    boolean_t isBitfieldTrue = FALSE;
    while(1)
    {
        
        if(bitfield == 0xF0)
            isBitfieldTrue = TRUE;
        else 
            isBitfieldTrue = FALSE;
        
        if(isBitfieldTrue)
        {
           WD_Trigger();
           bitfield = 0; 
        }
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_buttonShutdown)
{
    if(1 == button_osShutdown_Read())
    {        
         forceShutdownOS(); 
    } 
}

void checkFault()
{
    if(WD_CheckResetBit() == TRUE)
    {
        UART_1_PutString(" OS Shutdown due to watchdog!!!");
    }
    else if(0 == CyResetStatus)
    {
        UART_1_PutString(" system powered on due to POWER ON RESET!!");
    }
    else 
    {
        UART_1_PutString(" someother kind of RESET!!");
    }

}


void forceShutdownOS()
{
    UART_1_PutString(" FORCED RESET!!  watchdog!!!");
    ShutdownOS(0);
}
/* [] END OF FILE */
