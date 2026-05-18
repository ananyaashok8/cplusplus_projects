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
#include "global.h"

typedef enum {
    WDT_2_TICKS = 0 ,
    WDT_16_TICKS ,
    WDT_128_TICKS ,
    WDT_1024_TICKS      
} WDT_TimeOut_t;


/**
* Activate the Watchdog Trigger
* \param WDT_TimeOut_t timeout - [IN] Timeout Period
* @return RC_SUCCESS
*/
RC_t WD_Start(WDT_TimeOut_t timeout);

/**
* Service the Watchdog Trigger
* @return RC_SUCCESS
*/
RC_t WD_Trigger();


/**
* Checks the watchdog bit
* @return TRUE if watchdog reset bit was set
*/
boolean_t WD_CheckResetBit();


/*
 * This function shall be called by every runnable using a uniqe position, i.e. 
 * Runnable_0 sets bit at position 0, Runnable_1 sets bit at position 1 and so 
 * on.
*/
RC_t WD_Alive(uint8_t myBitPosition);

/* [] END OF FILE */
