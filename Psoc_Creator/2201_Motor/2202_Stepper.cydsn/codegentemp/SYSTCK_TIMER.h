/*******************************************************************************
* File Name: SYSTCK_TIMER.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SYSTCK_TIMER
*  component.
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

#if !defined(CY_TCPWM_SYSTCK_TIMER_H)
#define CY_TCPWM_SYSTCK_TIMER_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} SYSTCK_TIMER_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SYSTCK_TIMER_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SYSTCK_TIMER_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SYSTCK_TIMER_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SYSTCK_TIMER_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SYSTCK_TIMER_QUAD_ENCODING_MODES            (0lu)
#define SYSTCK_TIMER_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SYSTCK_TIMER_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SYSTCK_TIMER_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SYSTCK_TIMER_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SYSTCK_TIMER_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SYSTCK_TIMER_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SYSTCK_TIMER_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SYSTCK_TIMER_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SYSTCK_TIMER_TC_RUN_MODE                    (0lu)
#define SYSTCK_TIMER_TC_COUNTER_MODE                (0lu)
#define SYSTCK_TIMER_TC_COMP_CAP_MODE               (2lu)
#define SYSTCK_TIMER_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SYSTCK_TIMER_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SYSTCK_TIMER_TC_COUNT_SIGNAL_MODE           (3lu)
#define SYSTCK_TIMER_TC_START_SIGNAL_MODE           (0lu)
#define SYSTCK_TIMER_TC_STOP_SIGNAL_MODE            (0lu)
#define SYSTCK_TIMER_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SYSTCK_TIMER_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SYSTCK_TIMER_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SYSTCK_TIMER_TC_START_SIGNAL_PRESENT        (0lu)
#define SYSTCK_TIMER_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SYSTCK_TIMER_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SYSTCK_TIMER_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SYSTCK_TIMER_PWM_KILL_EVENT                 (0lu)
#define SYSTCK_TIMER_PWM_STOP_EVENT                 (0lu)
#define SYSTCK_TIMER_PWM_MODE                       (4lu)
#define SYSTCK_TIMER_PWM_OUT_N_INVERT               (0lu)
#define SYSTCK_TIMER_PWM_OUT_INVERT                 (0lu)
#define SYSTCK_TIMER_PWM_ALIGN                      (0lu)
#define SYSTCK_TIMER_PWM_RUN_MODE                   (0lu)
#define SYSTCK_TIMER_PWM_DEAD_TIME_CYCLE            (0lu)
#define SYSTCK_TIMER_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SYSTCK_TIMER_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SYSTCK_TIMER_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SYSTCK_TIMER_PWM_START_SIGNAL_MODE          (0lu)
#define SYSTCK_TIMER_PWM_STOP_SIGNAL_MODE           (0lu)
#define SYSTCK_TIMER_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SYSTCK_TIMER_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SYSTCK_TIMER_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SYSTCK_TIMER_PWM_START_SIGNAL_PRESENT       (0lu)
#define SYSTCK_TIMER_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SYSTCK_TIMER_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SYSTCK_TIMER_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SYSTCK_TIMER_TC_PERIOD_VALUE                (11999lu)
#define SYSTCK_TIMER_TC_COMPARE_VALUE               (65535lu)
#define SYSTCK_TIMER_TC_COMPARE_BUF_VALUE           (65535lu)
#define SYSTCK_TIMER_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SYSTCK_TIMER_PWM_PERIOD_VALUE               (65535lu)
#define SYSTCK_TIMER_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SYSTCK_TIMER_PWM_PERIOD_SWAP                (0lu)
#define SYSTCK_TIMER_PWM_COMPARE_VALUE              (65535lu)
#define SYSTCK_TIMER_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SYSTCK_TIMER_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SYSTCK_TIMER__LEFT 0
#define SYSTCK_TIMER__RIGHT 1
#define SYSTCK_TIMER__CENTER 2
#define SYSTCK_TIMER__ASYMMETRIC 3

#define SYSTCK_TIMER__X1 0
#define SYSTCK_TIMER__X2 1
#define SYSTCK_TIMER__X4 2

#define SYSTCK_TIMER__PWM 4
#define SYSTCK_TIMER__PWM_DT 5
#define SYSTCK_TIMER__PWM_PR 6

#define SYSTCK_TIMER__INVERSE 1
#define SYSTCK_TIMER__DIRECT 0

#define SYSTCK_TIMER__CAPTURE 2
#define SYSTCK_TIMER__COMPARE 0

#define SYSTCK_TIMER__TRIG_LEVEL 3
#define SYSTCK_TIMER__TRIG_RISING 0
#define SYSTCK_TIMER__TRIG_FALLING 1
#define SYSTCK_TIMER__TRIG_BOTH 2

#define SYSTCK_TIMER__INTR_MASK_TC 1
#define SYSTCK_TIMER__INTR_MASK_CC_MATCH 2
#define SYSTCK_TIMER__INTR_MASK_NONE 0
#define SYSTCK_TIMER__INTR_MASK_TC_CC 3

#define SYSTCK_TIMER__UNCONFIG 8
#define SYSTCK_TIMER__TIMER 1
#define SYSTCK_TIMER__QUAD 3
#define SYSTCK_TIMER__PWM_SEL 7

#define SYSTCK_TIMER__COUNT_UP 0
#define SYSTCK_TIMER__COUNT_DOWN 1
#define SYSTCK_TIMER__COUNT_UPDOWN0 2
#define SYSTCK_TIMER__COUNT_UPDOWN1 3


/* Prescaler */
#define SYSTCK_TIMER_PRESCALE_DIVBY1                ((uint32)(0u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY2                ((uint32)(1u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY4                ((uint32)(2u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY8                ((uint32)(3u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY16               ((uint32)(4u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY32               ((uint32)(5u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY64               ((uint32)(6u << SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_PRESCALE_DIVBY128              ((uint32)(7u << SYSTCK_TIMER_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SYSTCK_TIMER_MODE_TIMER_COMPARE             ((uint32)(SYSTCK_TIMER__COMPARE         <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_TIMER_CAPTURE             ((uint32)(SYSTCK_TIMER__CAPTURE         <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_QUAD                      ((uint32)(SYSTCK_TIMER__QUAD            <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_PWM                       ((uint32)(SYSTCK_TIMER__PWM             <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_PWM_DT                    ((uint32)(SYSTCK_TIMER__PWM_DT          <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_PWM_PR                    ((uint32)(SYSTCK_TIMER__PWM_PR          <<  \
                                                                  SYSTCK_TIMER_MODE_SHIFT))

/* Quad Modes */
#define SYSTCK_TIMER_MODE_X1                        ((uint32)(SYSTCK_TIMER__X1              <<  \
                                                                  SYSTCK_TIMER_QUAD_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_X2                        ((uint32)(SYSTCK_TIMER__X2              <<  \
                                                                  SYSTCK_TIMER_QUAD_MODE_SHIFT))
#define SYSTCK_TIMER_MODE_X4                        ((uint32)(SYSTCK_TIMER__X4              <<  \
                                                                  SYSTCK_TIMER_QUAD_MODE_SHIFT))

/* Counter modes */
#define SYSTCK_TIMER_COUNT_UP                       ((uint32)(SYSTCK_TIMER__COUNT_UP        <<  \
                                                                  SYSTCK_TIMER_UPDOWN_SHIFT))
#define SYSTCK_TIMER_COUNT_DOWN                     ((uint32)(SYSTCK_TIMER__COUNT_DOWN      <<  \
                                                                  SYSTCK_TIMER_UPDOWN_SHIFT))
#define SYSTCK_TIMER_COUNT_UPDOWN0                  ((uint32)(SYSTCK_TIMER__COUNT_UPDOWN0   <<  \
                                                                  SYSTCK_TIMER_UPDOWN_SHIFT))
#define SYSTCK_TIMER_COUNT_UPDOWN1                  ((uint32)(SYSTCK_TIMER__COUNT_UPDOWN1   <<  \
                                                                  SYSTCK_TIMER_UPDOWN_SHIFT))

/* PWM output invert */
#define SYSTCK_TIMER_INVERT_LINE                    ((uint32)(SYSTCK_TIMER__INVERSE         <<  \
                                                                  SYSTCK_TIMER_INV_OUT_SHIFT))
#define SYSTCK_TIMER_INVERT_LINE_N                  ((uint32)(SYSTCK_TIMER__INVERSE         <<  \
                                                                  SYSTCK_TIMER_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SYSTCK_TIMER_TRIG_RISING                    ((uint32)SYSTCK_TIMER__TRIG_RISING)
#define SYSTCK_TIMER_TRIG_FALLING                   ((uint32)SYSTCK_TIMER__TRIG_FALLING)
#define SYSTCK_TIMER_TRIG_BOTH                      ((uint32)SYSTCK_TIMER__TRIG_BOTH)
#define SYSTCK_TIMER_TRIG_LEVEL                     ((uint32)SYSTCK_TIMER__TRIG_LEVEL)

/* Interrupt mask */
#define SYSTCK_TIMER_INTR_MASK_TC                   ((uint32)SYSTCK_TIMER__INTR_MASK_TC)
#define SYSTCK_TIMER_INTR_MASK_CC_MATCH             ((uint32)SYSTCK_TIMER__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SYSTCK_TIMER_CC_MATCH_SET                   (0x00u)
#define SYSTCK_TIMER_CC_MATCH_CLEAR                 (0x01u)
#define SYSTCK_TIMER_CC_MATCH_INVERT                (0x02u)
#define SYSTCK_TIMER_CC_MATCH_NO_CHANGE             (0x03u)
#define SYSTCK_TIMER_OVERLOW_SET                    (0x00u)
#define SYSTCK_TIMER_OVERLOW_CLEAR                  (0x04u)
#define SYSTCK_TIMER_OVERLOW_INVERT                 (0x08u)
#define SYSTCK_TIMER_OVERLOW_NO_CHANGE              (0x0Cu)
#define SYSTCK_TIMER_UNDERFLOW_SET                  (0x00u)
#define SYSTCK_TIMER_UNDERFLOW_CLEAR                (0x10u)
#define SYSTCK_TIMER_UNDERFLOW_INVERT               (0x20u)
#define SYSTCK_TIMER_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SYSTCK_TIMER_PWM_MODE_LEFT                  (SYSTCK_TIMER_CC_MATCH_CLEAR        |   \
                                                         SYSTCK_TIMER_OVERLOW_SET           |   \
                                                         SYSTCK_TIMER_UNDERFLOW_NO_CHANGE)
#define SYSTCK_TIMER_PWM_MODE_RIGHT                 (SYSTCK_TIMER_CC_MATCH_SET          |   \
                                                         SYSTCK_TIMER_OVERLOW_NO_CHANGE     |   \
                                                         SYSTCK_TIMER_UNDERFLOW_CLEAR)
#define SYSTCK_TIMER_PWM_MODE_ASYM                  (SYSTCK_TIMER_CC_MATCH_INVERT       |   \
                                                         SYSTCK_TIMER_OVERLOW_SET           |   \
                                                         SYSTCK_TIMER_UNDERFLOW_CLEAR)

#if (SYSTCK_TIMER_CY_TCPWM_V2)
    #if(SYSTCK_TIMER_CY_TCPWM_4000)
        #define SYSTCK_TIMER_PWM_MODE_CENTER                (SYSTCK_TIMER_CC_MATCH_INVERT       |   \
                                                                 SYSTCK_TIMER_OVERLOW_NO_CHANGE     |   \
                                                                 SYSTCK_TIMER_UNDERFLOW_CLEAR)
    #else
        #define SYSTCK_TIMER_PWM_MODE_CENTER                (SYSTCK_TIMER_CC_MATCH_INVERT       |   \
                                                                 SYSTCK_TIMER_OVERLOW_SET           |   \
                                                                 SYSTCK_TIMER_UNDERFLOW_CLEAR)
    #endif /* (SYSTCK_TIMER_CY_TCPWM_4000) */
#else
    #define SYSTCK_TIMER_PWM_MODE_CENTER                (SYSTCK_TIMER_CC_MATCH_INVERT       |   \
                                                             SYSTCK_TIMER_OVERLOW_NO_CHANGE     |   \
                                                             SYSTCK_TIMER_UNDERFLOW_CLEAR)
#endif /* (SYSTCK_TIMER_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SYSTCK_TIMER_CMD_CAPTURE                    (0u)
#define SYSTCK_TIMER_CMD_RELOAD                     (8u)
#define SYSTCK_TIMER_CMD_STOP                       (16u)
#define SYSTCK_TIMER_CMD_START                      (24u)

/* Status */
#define SYSTCK_TIMER_STATUS_DOWN                    (1u)
#define SYSTCK_TIMER_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SYSTCK_TIMER_Init(void);
void   SYSTCK_TIMER_Enable(void);
void   SYSTCK_TIMER_Start(void);
void   SYSTCK_TIMER_Stop(void);

void   SYSTCK_TIMER_SetMode(uint32 mode);
void   SYSTCK_TIMER_SetCounterMode(uint32 counterMode);
void   SYSTCK_TIMER_SetPWMMode(uint32 modeMask);
void   SYSTCK_TIMER_SetQDMode(uint32 qdMode);

void   SYSTCK_TIMER_SetPrescaler(uint32 prescaler);
void   SYSTCK_TIMER_TriggerCommand(uint32 mask, uint32 command);
void   SYSTCK_TIMER_SetOneShot(uint32 oneShotEnable);
uint32 SYSTCK_TIMER_ReadStatus(void);

void   SYSTCK_TIMER_SetPWMSyncKill(uint32 syncKillEnable);
void   SYSTCK_TIMER_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SYSTCK_TIMER_SetPWMDeadTime(uint32 deadTime);
void   SYSTCK_TIMER_SetPWMInvert(uint32 mask);

void   SYSTCK_TIMER_SetInterruptMode(uint32 interruptMask);
uint32 SYSTCK_TIMER_GetInterruptSourceMasked(void);
uint32 SYSTCK_TIMER_GetInterruptSource(void);
void   SYSTCK_TIMER_ClearInterrupt(uint32 interruptMask);
void   SYSTCK_TIMER_SetInterrupt(uint32 interruptMask);

void   SYSTCK_TIMER_WriteCounter(uint32 count);
uint32 SYSTCK_TIMER_ReadCounter(void);

uint32 SYSTCK_TIMER_ReadCapture(void);
uint32 SYSTCK_TIMER_ReadCaptureBuf(void);

void   SYSTCK_TIMER_WritePeriod(uint32 period);
uint32 SYSTCK_TIMER_ReadPeriod(void);
void   SYSTCK_TIMER_WritePeriodBuf(uint32 periodBuf);
uint32 SYSTCK_TIMER_ReadPeriodBuf(void);

void   SYSTCK_TIMER_WriteCompare(uint32 compare);
uint32 SYSTCK_TIMER_ReadCompare(void);
void   SYSTCK_TIMER_WriteCompareBuf(uint32 compareBuf);
uint32 SYSTCK_TIMER_ReadCompareBuf(void);

void   SYSTCK_TIMER_SetPeriodSwap(uint32 swapEnable);
void   SYSTCK_TIMER_SetCompareSwap(uint32 swapEnable);

void   SYSTCK_TIMER_SetCaptureMode(uint32 triggerMode);
void   SYSTCK_TIMER_SetReloadMode(uint32 triggerMode);
void   SYSTCK_TIMER_SetStartMode(uint32 triggerMode);
void   SYSTCK_TIMER_SetStopMode(uint32 triggerMode);
void   SYSTCK_TIMER_SetCountMode(uint32 triggerMode);

void   SYSTCK_TIMER_SaveConfig(void);
void   SYSTCK_TIMER_RestoreConfig(void);
void   SYSTCK_TIMER_Sleep(void);
void   SYSTCK_TIMER_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SYSTCK_TIMER_BLOCK_CONTROL_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SYSTCK_TIMER_BLOCK_CONTROL_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SYSTCK_TIMER_COMMAND_REG                    (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SYSTCK_TIMER_COMMAND_PTR                    ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SYSTCK_TIMER_INTRRUPT_CAUSE_REG             (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SYSTCK_TIMER_INTRRUPT_CAUSE_PTR             ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SYSTCK_TIMER_CONTROL_REG                    (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CTRL )
#define SYSTCK_TIMER_CONTROL_PTR                    ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CTRL )
#define SYSTCK_TIMER_STATUS_REG                     (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__STATUS )
#define SYSTCK_TIMER_STATUS_PTR                     ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__STATUS )
#define SYSTCK_TIMER_COUNTER_REG                    (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__COUNTER )
#define SYSTCK_TIMER_COUNTER_PTR                    ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__COUNTER )
#define SYSTCK_TIMER_COMP_CAP_REG                   (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CC )
#define SYSTCK_TIMER_COMP_CAP_PTR                   ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CC )
#define SYSTCK_TIMER_COMP_CAP_BUF_REG               (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CC_BUFF )
#define SYSTCK_TIMER_COMP_CAP_BUF_PTR               ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__CC_BUFF )
#define SYSTCK_TIMER_PERIOD_REG                     (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__PERIOD )
#define SYSTCK_TIMER_PERIOD_PTR                     ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__PERIOD )
#define SYSTCK_TIMER_PERIOD_BUF_REG                 (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SYSTCK_TIMER_PERIOD_BUF_PTR                 ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SYSTCK_TIMER_TRIG_CONTROL0_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SYSTCK_TIMER_TRIG_CONTROL0_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SYSTCK_TIMER_TRIG_CONTROL1_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SYSTCK_TIMER_TRIG_CONTROL1_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SYSTCK_TIMER_TRIG_CONTROL2_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SYSTCK_TIMER_TRIG_CONTROL2_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SYSTCK_TIMER_INTERRUPT_REQ_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR )
#define SYSTCK_TIMER_INTERRUPT_REQ_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR )
#define SYSTCK_TIMER_INTERRUPT_SET_REG              (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_SET )
#define SYSTCK_TIMER_INTERRUPT_SET_PTR              ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_SET )
#define SYSTCK_TIMER_INTERRUPT_MASK_REG             (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_MASK )
#define SYSTCK_TIMER_INTERRUPT_MASK_PTR             ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_MASK )
#define SYSTCK_TIMER_INTERRUPT_MASKED_REG           (*(reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SYSTCK_TIMER_INTERRUPT_MASKED_PTR           ( (reg32 *) SYSTCK_TIMER_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SYSTCK_TIMER_MASK                           ((uint32)SYSTCK_TIMER_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SYSTCK_TIMER_RELOAD_CC_SHIFT                (0u)
#define SYSTCK_TIMER_RELOAD_PERIOD_SHIFT            (1u)
#define SYSTCK_TIMER_PWM_SYNC_KILL_SHIFT            (2u)
#define SYSTCK_TIMER_PWM_STOP_KILL_SHIFT            (3u)
#define SYSTCK_TIMER_PRESCALER_SHIFT                (8u)
#define SYSTCK_TIMER_UPDOWN_SHIFT                   (16u)
#define SYSTCK_TIMER_ONESHOT_SHIFT                  (18u)
#define SYSTCK_TIMER_QUAD_MODE_SHIFT                (20u)
#define SYSTCK_TIMER_INV_OUT_SHIFT                  (20u)
#define SYSTCK_TIMER_INV_COMPL_OUT_SHIFT            (21u)
#define SYSTCK_TIMER_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SYSTCK_TIMER_RELOAD_CC_MASK                 ((uint32)(SYSTCK_TIMER_1BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_RELOAD_CC_SHIFT))
#define SYSTCK_TIMER_RELOAD_PERIOD_MASK             ((uint32)(SYSTCK_TIMER_1BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_RELOAD_PERIOD_SHIFT))
#define SYSTCK_TIMER_PWM_SYNC_KILL_MASK             ((uint32)(SYSTCK_TIMER_1BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_PWM_SYNC_KILL_SHIFT))
#define SYSTCK_TIMER_PWM_STOP_KILL_MASK             ((uint32)(SYSTCK_TIMER_1BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_PWM_STOP_KILL_SHIFT))
#define SYSTCK_TIMER_PRESCALER_MASK                 ((uint32)(SYSTCK_TIMER_8BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_PRESCALER_SHIFT))
#define SYSTCK_TIMER_UPDOWN_MASK                    ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_UPDOWN_SHIFT))
#define SYSTCK_TIMER_ONESHOT_MASK                   ((uint32)(SYSTCK_TIMER_1BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_ONESHOT_SHIFT))
#define SYSTCK_TIMER_QUAD_MODE_MASK                 ((uint32)(SYSTCK_TIMER_3BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_QUAD_MODE_SHIFT))
#define SYSTCK_TIMER_INV_OUT_MASK                   ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_INV_OUT_SHIFT))
#define SYSTCK_TIMER_MODE_MASK                      ((uint32)(SYSTCK_TIMER_3BIT_MASK        <<  \
                                                                            SYSTCK_TIMER_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SYSTCK_TIMER_CAPTURE_SHIFT                  (0u)
#define SYSTCK_TIMER_COUNT_SHIFT                    (2u)
#define SYSTCK_TIMER_RELOAD_SHIFT                   (4u)
#define SYSTCK_TIMER_STOP_SHIFT                     (6u)
#define SYSTCK_TIMER_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SYSTCK_TIMER_CAPTURE_MASK                   ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                  SYSTCK_TIMER_CAPTURE_SHIFT))
#define SYSTCK_TIMER_COUNT_MASK                     ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                  SYSTCK_TIMER_COUNT_SHIFT))
#define SYSTCK_TIMER_RELOAD_MASK                    ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                  SYSTCK_TIMER_RELOAD_SHIFT))
#define SYSTCK_TIMER_STOP_MASK                      ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                  SYSTCK_TIMER_STOP_SHIFT))
#define SYSTCK_TIMER_START_MASK                     ((uint32)(SYSTCK_TIMER_2BIT_MASK        <<  \
                                                                  SYSTCK_TIMER_START_SHIFT))

/* MASK */
#define SYSTCK_TIMER_1BIT_MASK                      ((uint32)0x01u)
#define SYSTCK_TIMER_2BIT_MASK                      ((uint32)0x03u)
#define SYSTCK_TIMER_3BIT_MASK                      ((uint32)0x07u)
#define SYSTCK_TIMER_6BIT_MASK                      ((uint32)0x3Fu)
#define SYSTCK_TIMER_8BIT_MASK                      ((uint32)0xFFu)
#define SYSTCK_TIMER_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SYSTCK_TIMER_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SYSTCK_TIMER_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SYSTCK_TIMER_QUAD_ENCODING_MODES     << SYSTCK_TIMER_QUAD_MODE_SHIFT))       |\
         ((uint32)(SYSTCK_TIMER_CONFIG                  << SYSTCK_TIMER_MODE_SHIFT)))

#define SYSTCK_TIMER_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SYSTCK_TIMER_PWM_STOP_EVENT          << SYSTCK_TIMER_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SYSTCK_TIMER_PWM_OUT_INVERT          << SYSTCK_TIMER_INV_OUT_SHIFT))         |\
         ((uint32)(SYSTCK_TIMER_PWM_OUT_N_INVERT        << SYSTCK_TIMER_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SYSTCK_TIMER_PWM_MODE                << SYSTCK_TIMER_MODE_SHIFT)))

#define SYSTCK_TIMER_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SYSTCK_TIMER_PWM_RUN_MODE         << SYSTCK_TIMER_ONESHOT_SHIFT))
            
#define SYSTCK_TIMER_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SYSTCK_TIMER_PWM_ALIGN            << SYSTCK_TIMER_UPDOWN_SHIFT))

#define SYSTCK_TIMER_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SYSTCK_TIMER_PWM_KILL_EVENT      << SYSTCK_TIMER_PWM_SYNC_KILL_SHIFT))

#define SYSTCK_TIMER_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SYSTCK_TIMER_PWM_DEAD_TIME_CYCLE  << SYSTCK_TIMER_PRESCALER_SHIFT))

#define SYSTCK_TIMER_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SYSTCK_TIMER_PWM_PRESCALER        << SYSTCK_TIMER_PRESCALER_SHIFT))

#define SYSTCK_TIMER_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SYSTCK_TIMER_TC_PRESCALER            << SYSTCK_TIMER_PRESCALER_SHIFT))       |\
         ((uint32)(SYSTCK_TIMER_TC_COUNTER_MODE         << SYSTCK_TIMER_UPDOWN_SHIFT))          |\
         ((uint32)(SYSTCK_TIMER_TC_RUN_MODE             << SYSTCK_TIMER_ONESHOT_SHIFT))         |\
         ((uint32)(SYSTCK_TIMER_TC_COMP_CAP_MODE        << SYSTCK_TIMER_MODE_SHIFT)))
        
#define SYSTCK_TIMER_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SYSTCK_TIMER_QUAD_PHIA_SIGNAL_MODE   << SYSTCK_TIMER_COUNT_SHIFT))           |\
         ((uint32)(SYSTCK_TIMER_QUAD_INDEX_SIGNAL_MODE  << SYSTCK_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(SYSTCK_TIMER_QUAD_STOP_SIGNAL_MODE   << SYSTCK_TIMER_STOP_SHIFT))            |\
         ((uint32)(SYSTCK_TIMER_QUAD_PHIB_SIGNAL_MODE   << SYSTCK_TIMER_START_SHIFT)))

#define SYSTCK_TIMER_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SYSTCK_TIMER_PWM_SWITCH_SIGNAL_MODE  << SYSTCK_TIMER_CAPTURE_SHIFT))         |\
         ((uint32)(SYSTCK_TIMER_PWM_COUNT_SIGNAL_MODE   << SYSTCK_TIMER_COUNT_SHIFT))           |\
         ((uint32)(SYSTCK_TIMER_PWM_RELOAD_SIGNAL_MODE  << SYSTCK_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(SYSTCK_TIMER_PWM_STOP_SIGNAL_MODE    << SYSTCK_TIMER_STOP_SHIFT))            |\
         ((uint32)(SYSTCK_TIMER_PWM_START_SIGNAL_MODE   << SYSTCK_TIMER_START_SHIFT)))

#define SYSTCK_TIMER_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SYSTCK_TIMER_TC_CAPTURE_SIGNAL_MODE  << SYSTCK_TIMER_CAPTURE_SHIFT))         |\
         ((uint32)(SYSTCK_TIMER_TC_COUNT_SIGNAL_MODE    << SYSTCK_TIMER_COUNT_SHIFT))           |\
         ((uint32)(SYSTCK_TIMER_TC_RELOAD_SIGNAL_MODE   << SYSTCK_TIMER_RELOAD_SHIFT))          |\
         ((uint32)(SYSTCK_TIMER_TC_STOP_SIGNAL_MODE     << SYSTCK_TIMER_STOP_SHIFT))            |\
         ((uint32)(SYSTCK_TIMER_TC_START_SIGNAL_MODE    << SYSTCK_TIMER_START_SHIFT)))
        
#define SYSTCK_TIMER_TIMER_UPDOWN_CNT_USED                                                          \
                ((SYSTCK_TIMER__COUNT_UPDOWN0 == SYSTCK_TIMER_TC_COUNTER_MODE)                  ||\
                 (SYSTCK_TIMER__COUNT_UPDOWN1 == SYSTCK_TIMER_TC_COUNTER_MODE))

#define SYSTCK_TIMER_PWM_UPDOWN_CNT_USED                                                            \
                ((SYSTCK_TIMER__CENTER == SYSTCK_TIMER_PWM_ALIGN)                               ||\
                 (SYSTCK_TIMER__ASYMMETRIC == SYSTCK_TIMER_PWM_ALIGN))               
        
#define SYSTCK_TIMER_PWM_PR_INIT_VALUE              (1u)
#define SYSTCK_TIMER_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SYSTCK_TIMER_H */

/* [] END OF FILE */
