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
#include "watchdog.h"
#include "CyLib.h"

extern uint8 bitfield;

RC_t WD_Start(WDT_TimeOut_t timeout)
{
    CyWdtStart(timeout, CYWDT_LPMODE_MAXINTER);
    return RC_SUCCESS;
}

RC_t WD_Trigger()
{   
    CyWdtClear();     
    return RC_SUCCESS;
}


boolean_t WD_CheckResetBit()
{
    boolean_t isReset = FALSE;
    if( CY_RESET_WD == CyResetStatus)
        isReset = TRUE;
    else 
        isReset = FALSE;
    
    return isReset;
}

RC_t WD_Alive(uint8_t myBitPosition)
{
    bitfield |= 1 << myBitPosition;
    return RC_SUCCESS;
}

/* [] END OF FILE */
