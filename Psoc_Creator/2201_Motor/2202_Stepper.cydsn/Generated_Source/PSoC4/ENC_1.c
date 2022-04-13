/*******************************************************************************
* File Name: ENC_1.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the ENC_1
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ENC_1.h"

uint8 ENC_1_initVar = 0u;


/*******************************************************************************
* Function Name: ENC_1_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default ENC_1 configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (ENC_1__QUAD == ENC_1_CONFIG)
        ENC_1_CONTROL_REG = ENC_1_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ENC_1_TRIG_CONTROL1_REG  = ENC_1_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        ENC_1_SetInterruptMode(ENC_1_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        ENC_1_SetCounterMode(ENC_1_COUNT_DOWN);
        ENC_1_WritePeriod(ENC_1_QUAD_PERIOD_INIT_VALUE);
        ENC_1_WriteCounter(ENC_1_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (ENC_1__QUAD == ENC_1_CONFIG) */

    #if (ENC_1__TIMER == ENC_1_CONFIG)
        ENC_1_CONTROL_REG = ENC_1_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        ENC_1_TRIG_CONTROL1_REG  = ENC_1_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ENC_1_SetInterruptMode(ENC_1_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        ENC_1_WritePeriod(ENC_1_TC_PERIOD_VALUE );

        #if (ENC_1__COMPARE == ENC_1_TC_COMP_CAP_MODE)
            ENC_1_WriteCompare(ENC_1_TC_COMPARE_VALUE);

            #if (1u == ENC_1_TC_COMPARE_SWAP)
                ENC_1_SetCompareSwap(1u);
                ENC_1_WriteCompareBuf(ENC_1_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == ENC_1_TC_COMPARE_SWAP) */
        #endif  /* (ENC_1__COMPARE == ENC_1_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (ENC_1_CY_TCPWM_V2 && ENC_1_TIMER_UPDOWN_CNT_USED && !ENC_1_CY_TCPWM_4000)
            ENC_1_WriteCounter(1u);
        #elif(ENC_1__COUNT_DOWN == ENC_1_TC_COUNTER_MODE)
            ENC_1_WriteCounter(ENC_1_TC_PERIOD_VALUE);
        #else
            ENC_1_WriteCounter(0u);
        #endif /* (ENC_1_CY_TCPWM_V2 && ENC_1_TIMER_UPDOWN_CNT_USED && !ENC_1_CY_TCPWM_4000) */
    #endif  /* (ENC_1__TIMER == ENC_1_CONFIG) */

    #if (ENC_1__PWM_SEL == ENC_1_CONFIG)
        ENC_1_CONTROL_REG = ENC_1_CTRL_PWM_BASE_CONFIG;

        #if (ENC_1__PWM_PR == ENC_1_PWM_MODE)
            ENC_1_CONTROL_REG |= ENC_1_CTRL_PWM_RUN_MODE;
            ENC_1_WriteCounter(ENC_1_PWM_PR_INIT_VALUE);
        #else
            ENC_1_CONTROL_REG |= ENC_1_CTRL_PWM_ALIGN | ENC_1_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (ENC_1_CY_TCPWM_V2 && ENC_1_PWM_UPDOWN_CNT_USED && !ENC_1_CY_TCPWM_4000)
                ENC_1_WriteCounter(1u);
            #elif (ENC_1__RIGHT == ENC_1_PWM_ALIGN)
                ENC_1_WriteCounter(ENC_1_PWM_PERIOD_VALUE);
            #else 
                ENC_1_WriteCounter(0u);
            #endif  /* (ENC_1_CY_TCPWM_V2 && ENC_1_PWM_UPDOWN_CNT_USED && !ENC_1_CY_TCPWM_4000) */
        #endif  /* (ENC_1__PWM_PR == ENC_1_PWM_MODE) */

        #if (ENC_1__PWM_DT == ENC_1_PWM_MODE)
            ENC_1_CONTROL_REG |= ENC_1_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (ENC_1__PWM_DT == ENC_1_PWM_MODE) */

        #if (ENC_1__PWM == ENC_1_PWM_MODE)
            ENC_1_CONTROL_REG |= ENC_1_CTRL_PWM_PRESCALER;
        #endif  /* (ENC_1__PWM == ENC_1_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        ENC_1_TRIG_CONTROL1_REG  = ENC_1_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        ENC_1_SetInterruptMode(ENC_1_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (ENC_1__PWM_PR == ENC_1_PWM_MODE)
            ENC_1_TRIG_CONTROL2_REG =
                    (ENC_1_CC_MATCH_NO_CHANGE    |
                    ENC_1_OVERLOW_NO_CHANGE      |
                    ENC_1_UNDERFLOW_NO_CHANGE);
        #else
            #if (ENC_1__LEFT == ENC_1_PWM_ALIGN)
                ENC_1_TRIG_CONTROL2_REG = ENC_1_PWM_MODE_LEFT;
            #endif  /* ( ENC_1_PWM_LEFT == ENC_1_PWM_ALIGN) */

            #if (ENC_1__RIGHT == ENC_1_PWM_ALIGN)
                ENC_1_TRIG_CONTROL2_REG = ENC_1_PWM_MODE_RIGHT;
            #endif  /* ( ENC_1_PWM_RIGHT == ENC_1_PWM_ALIGN) */

            #if (ENC_1__CENTER == ENC_1_PWM_ALIGN)
                ENC_1_TRIG_CONTROL2_REG = ENC_1_PWM_MODE_CENTER;
            #endif  /* ( ENC_1_PWM_CENTER == ENC_1_PWM_ALIGN) */

            #if (ENC_1__ASYMMETRIC == ENC_1_PWM_ALIGN)
                ENC_1_TRIG_CONTROL2_REG = ENC_1_PWM_MODE_ASYM;
            #endif  /* (ENC_1__ASYMMETRIC == ENC_1_PWM_ALIGN) */
        #endif  /* (ENC_1__PWM_PR == ENC_1_PWM_MODE) */

        /* Set other values from customizer */
        ENC_1_WritePeriod(ENC_1_PWM_PERIOD_VALUE );
        ENC_1_WriteCompare(ENC_1_PWM_COMPARE_VALUE);

        #if (1u == ENC_1_PWM_COMPARE_SWAP)
            ENC_1_SetCompareSwap(1u);
            ENC_1_WriteCompareBuf(ENC_1_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == ENC_1_PWM_COMPARE_SWAP) */

        #if (1u == ENC_1_PWM_PERIOD_SWAP)
            ENC_1_SetPeriodSwap(1u);
            ENC_1_WritePeriodBuf(ENC_1_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == ENC_1_PWM_PERIOD_SWAP) */
    #endif  /* (ENC_1__PWM_SEL == ENC_1_CONFIG) */
    
}


/*******************************************************************************
* Function Name: ENC_1_Enable
********************************************************************************
*
* Summary:
*  Enables the ENC_1.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    ENC_1_BLOCK_CONTROL_REG |= ENC_1_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (ENC_1__PWM_SEL == ENC_1_CONFIG)
        #if (0u == ENC_1_PWM_START_SIGNAL_PRESENT)
            ENC_1_TriggerCommand(ENC_1_MASK, ENC_1_CMD_START);
        #endif /* (0u == ENC_1_PWM_START_SIGNAL_PRESENT) */
    #endif /* (ENC_1__PWM_SEL == ENC_1_CONFIG) */

    #if (ENC_1__TIMER == ENC_1_CONFIG)
        #if (0u == ENC_1_TC_START_SIGNAL_PRESENT)
            ENC_1_TriggerCommand(ENC_1_MASK, ENC_1_CMD_START);
        #endif /* (0u == ENC_1_TC_START_SIGNAL_PRESENT) */
    #endif /* (ENC_1__TIMER == ENC_1_CONFIG) */
    
    #if (ENC_1__QUAD == ENC_1_CONFIG)
        #if (0u != ENC_1_QUAD_AUTO_START)
            ENC_1_TriggerCommand(ENC_1_MASK, ENC_1_CMD_RELOAD);
        #endif /* (0u != ENC_1_QUAD_AUTO_START) */
    #endif  /* (ENC_1__QUAD == ENC_1_CONFIG) */
}


/*******************************************************************************
* Function Name: ENC_1_Start
********************************************************************************
*
* Summary:
*  Initializes the ENC_1 with default customizer
*  values when called the first time and enables the ENC_1.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ENC_1_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time ENC_1_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the ENC_1_Start() routine.
*
*******************************************************************************/
void ENC_1_Start(void)
{
    if (0u == ENC_1_initVar)
    {
        ENC_1_Init();
        ENC_1_initVar = 1u;
    }

    ENC_1_Enable();
}


/*******************************************************************************
* Function Name: ENC_1_Stop
********************************************************************************
*
* Summary:
*  Disables the ENC_1.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_BLOCK_CONTROL_REG &= (uint32)~ENC_1_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the ENC_1. This function is used when
*  configured as a generic ENC_1 and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the ENC_1 to operate in
*   Values:
*   - ENC_1_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - ENC_1_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - ENC_1_MODE_QUAD - Quadrature decoder
*         - ENC_1_MODE_PWM - PWM
*         - ENC_1_MODE_PWM_DT - PWM with dead time
*         - ENC_1_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_MODE_MASK;
    ENC_1_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - ENC_1_MODE_X1 - Counts on phi 1 rising
*         - ENC_1_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - ENC_1_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_QUAD_MODE_MASK;
    ENC_1_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - ENC_1_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - ENC_1_PRESCALE_DIVBY2    - Divide by 2
*         - ENC_1_PRESCALE_DIVBY4    - Divide by 4
*         - ENC_1_PRESCALE_DIVBY8    - Divide by 8
*         - ENC_1_PRESCALE_DIVBY16   - Divide by 16
*         - ENC_1_PRESCALE_DIVBY32   - Divide by 32
*         - ENC_1_PRESCALE_DIVBY64   - Divide by 64
*         - ENC_1_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_PRESCALER_MASK;
    ENC_1_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the ENC_1 runs
*  continuously or stops when terminal count is reached.  By default the
*  ENC_1 operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_ONESHOT_MASK;
    ENC_1_CONTROL_REG |= ((uint32)((oneShotEnable & ENC_1_1BIT_MASK) <<
                                                               ENC_1_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPWMMode(uint32 modeMask)
{
    ENC_1_TRIG_CONTROL2_REG = (modeMask & ENC_1_6BIT_MASK);
}



/*******************************************************************************
* Function Name: ENC_1_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_PWM_SYNC_KILL_MASK;
    ENC_1_CONTROL_REG |= ((uint32)((syncKillEnable & ENC_1_1BIT_MASK)  <<
                                               ENC_1_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_PWM_STOP_KILL_MASK;
    ENC_1_CONTROL_REG |= ((uint32)((stopOnKillEnable & ENC_1_1BIT_MASK)  <<
                                                         ENC_1_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_PRESCALER_MASK;
    ENC_1_CONTROL_REG |= ((uint32)((deadTime & ENC_1_8BIT_MASK) <<
                                                          ENC_1_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - ENC_1_INVERT_LINE   - Inverts the line output
*         - ENC_1_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_INV_OUT_MASK;
    ENC_1_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: ENC_1_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_WriteCounter(uint32 count)
{
    ENC_1_COUNTER_REG = (count & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 ENC_1_ReadCounter(void)
{
    return (ENC_1_COUNTER_REG & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - ENC_1_COUNT_UP       - Counts up
*     - ENC_1_COUNT_DOWN     - Counts down
*     - ENC_1_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - ENC_1_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_UPDOWN_MASK;
    ENC_1_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_WritePeriod(uint32 period)
{
    ENC_1_PERIOD_REG = (period & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ENC_1_ReadPeriod(void)
{
    return (ENC_1_PERIOD_REG & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_RELOAD_CC_MASK;
    ENC_1_CONTROL_REG |= (swapEnable & ENC_1_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_WritePeriodBuf(uint32 periodBuf)
{
    ENC_1_PERIOD_BUF_REG = (periodBuf & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 ENC_1_ReadPeriodBuf(void)
{
    return (ENC_1_PERIOD_BUF_REG & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_CONTROL_REG &= (uint32)~ENC_1_RELOAD_PERIOD_MASK;
    ENC_1_CONTROL_REG |= ((uint32)((swapEnable & ENC_1_1BIT_MASK) <<
                                                            ENC_1_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void ENC_1_WriteCompare(uint32 compare)
{
    #if (ENC_1_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ENC_1_CY_TCPWM_4000) */

    #if (ENC_1_CY_TCPWM_4000)
        currentMode = ((ENC_1_CONTROL_REG & ENC_1_UPDOWN_MASK) >> ENC_1_UPDOWN_SHIFT);

        if (((uint32)ENC_1__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)ENC_1__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (ENC_1_CY_TCPWM_4000) */
    
    ENC_1_COMP_CAP_REG = (compare & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 ENC_1_ReadCompare(void)
{
    #if (ENC_1_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ENC_1_CY_TCPWM_4000) */

    #if (ENC_1_CY_TCPWM_4000)
        currentMode = ((ENC_1_CONTROL_REG & ENC_1_UPDOWN_MASK) >> ENC_1_UPDOWN_SHIFT);
        
        regVal = ENC_1_COMP_CAP_REG;
        
        if (((uint32)ENC_1__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ENC_1__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ENC_1_16BIT_MASK);
    #else
        return (ENC_1_COMP_CAP_REG & ENC_1_16BIT_MASK);
    #endif /* (ENC_1_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ENC_1_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void ENC_1_WriteCompareBuf(uint32 compareBuf)
{
    #if (ENC_1_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (ENC_1_CY_TCPWM_4000) */

    #if (ENC_1_CY_TCPWM_4000)
        currentMode = ((ENC_1_CONTROL_REG & ENC_1_UPDOWN_MASK) >> ENC_1_UPDOWN_SHIFT);

        if (((uint32)ENC_1__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)ENC_1__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (ENC_1_CY_TCPWM_4000) */
    
    ENC_1_COMP_CAP_BUF_REG = (compareBuf & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 ENC_1_ReadCompareBuf(void)
{
    #if (ENC_1_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (ENC_1_CY_TCPWM_4000) */

    #if (ENC_1_CY_TCPWM_4000)
        currentMode = ((ENC_1_CONTROL_REG & ENC_1_UPDOWN_MASK) >> ENC_1_UPDOWN_SHIFT);

        regVal = ENC_1_COMP_CAP_BUF_REG;
        
        if (((uint32)ENC_1__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)ENC_1__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & ENC_1_16BIT_MASK);
    #else
        return (ENC_1_COMP_CAP_BUF_REG & ENC_1_16BIT_MASK);
    #endif /* (ENC_1_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: ENC_1_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 ENC_1_ReadCapture(void)
{
    return (ENC_1_COMP_CAP_REG & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 ENC_1_ReadCaptureBuf(void)
{
    return (ENC_1_COMP_CAP_BUF_REG & ENC_1_16BIT_MASK);
}


/*******************************************************************************
* Function Name: ENC_1_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ENC_1_TRIG_LEVEL     - Level
*     - ENC_1_TRIG_RISING    - Rising edge
*     - ENC_1_TRIG_FALLING   - Falling edge
*     - ENC_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_TRIG_CONTROL1_REG &= (uint32)~ENC_1_CAPTURE_MASK;
    ENC_1_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ENC_1_TRIG_LEVEL     - Level
*     - ENC_1_TRIG_RISING    - Rising edge
*     - ENC_1_TRIG_FALLING   - Falling edge
*     - ENC_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_TRIG_CONTROL1_REG &= (uint32)~ENC_1_RELOAD_MASK;
    ENC_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ENC_1_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ENC_1_TRIG_LEVEL     - Level
*     - ENC_1_TRIG_RISING    - Rising edge
*     - ENC_1_TRIG_FALLING   - Falling edge
*     - ENC_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_TRIG_CONTROL1_REG &= (uint32)~ENC_1_START_MASK;
    ENC_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ENC_1_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ENC_1_TRIG_LEVEL     - Level
*     - ENC_1_TRIG_RISING    - Rising edge
*     - ENC_1_TRIG_FALLING   - Falling edge
*     - ENC_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_TRIG_CONTROL1_REG &= (uint32)~ENC_1_STOP_MASK;
    ENC_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ENC_1_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - ENC_1_TRIG_LEVEL     - Level
*     - ENC_1_TRIG_RISING    - Rising edge
*     - ENC_1_TRIG_FALLING   - Falling edge
*     - ENC_1_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_TRIG_CONTROL1_REG &= (uint32)~ENC_1_COUNT_MASK;
    ENC_1_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << ENC_1_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - ENC_1_CMD_CAPTURE    - Trigger Capture/Switch command
*     - ENC_1_CMD_RELOAD     - Trigger Reload/Index command
*     - ENC_1_CMD_STOP       - Trigger Stop/Kill command
*     - ENC_1_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    ENC_1_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: ENC_1_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the ENC_1.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - ENC_1_STATUS_DOWN    - Set if counting down
*     - ENC_1_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 ENC_1_ReadStatus(void)
{
    return ((ENC_1_STATUS_REG >> ENC_1_RUNNING_STATUS_SHIFT) |
            (ENC_1_STATUS_REG & ENC_1_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: ENC_1_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - ENC_1_INTR_MASK_TC       - Terminal count mask
*     - ENC_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetInterruptMode(uint32 interruptMask)
{
    ENC_1_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: ENC_1_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - ENC_1_INTR_MASK_TC       - Terminal count mask
*     - ENC_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ENC_1_GetInterruptSourceMasked(void)
{
    return (ENC_1_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: ENC_1_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - ENC_1_INTR_MASK_TC       - Terminal count mask
*     - ENC_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 ENC_1_GetInterruptSource(void)
{
    return (ENC_1_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: ENC_1_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - ENC_1_INTR_MASK_TC       - Terminal count mask
*     - ENC_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_ClearInterrupt(uint32 interruptMask)
{
    ENC_1_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: ENC_1_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - ENC_1_INTR_MASK_TC       - Terminal count mask
*     - ENC_1_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SetInterrupt(uint32 interruptMask)
{
    ENC_1_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
