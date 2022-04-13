/*******************************************************************************
* File Name: ENC_1.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the ENC_1
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

#if !defined(CY_TCPWM_ENC_1_H)
#define CY_TCPWM_ENC_1_H


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
} ENC_1_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  ENC_1_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ENC_1_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define ENC_1_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define ENC_1_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define ENC_1_QUAD_ENCODING_MODES            (0lu)
#define ENC_1_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define ENC_1_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define ENC_1_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define ENC_1_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define ENC_1_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define ENC_1_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define ENC_1_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define ENC_1_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define ENC_1_TC_RUN_MODE                    (0lu)
#define ENC_1_TC_COUNTER_MODE                (0lu)
#define ENC_1_TC_COMP_CAP_MODE               (2lu)
#define ENC_1_TC_PRESCALER                   (0lu)

/* Signal modes */
#define ENC_1_TC_RELOAD_SIGNAL_MODE          (0lu)
#define ENC_1_TC_COUNT_SIGNAL_MODE           (3lu)
#define ENC_1_TC_START_SIGNAL_MODE           (0lu)
#define ENC_1_TC_STOP_SIGNAL_MODE            (0lu)
#define ENC_1_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define ENC_1_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define ENC_1_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define ENC_1_TC_START_SIGNAL_PRESENT        (0lu)
#define ENC_1_TC_STOP_SIGNAL_PRESENT         (0lu)
#define ENC_1_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ENC_1_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define ENC_1_PWM_KILL_EVENT                 (0lu)
#define ENC_1_PWM_STOP_EVENT                 (0lu)
#define ENC_1_PWM_MODE                       (4lu)
#define ENC_1_PWM_OUT_N_INVERT               (0lu)
#define ENC_1_PWM_OUT_INVERT                 (0lu)
#define ENC_1_PWM_ALIGN                      (0lu)
#define ENC_1_PWM_RUN_MODE                   (0lu)
#define ENC_1_PWM_DEAD_TIME_CYCLE            (0lu)
#define ENC_1_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define ENC_1_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define ENC_1_PWM_COUNT_SIGNAL_MODE          (3lu)
#define ENC_1_PWM_START_SIGNAL_MODE          (0lu)
#define ENC_1_PWM_STOP_SIGNAL_MODE           (0lu)
#define ENC_1_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define ENC_1_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define ENC_1_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define ENC_1_PWM_START_SIGNAL_PRESENT       (0lu)
#define ENC_1_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define ENC_1_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ENC_1_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define ENC_1_TC_PERIOD_VALUE                (65535lu)
#define ENC_1_TC_COMPARE_VALUE               (65535lu)
#define ENC_1_TC_COMPARE_BUF_VALUE           (65535lu)
#define ENC_1_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define ENC_1_PWM_PERIOD_VALUE               (65535lu)
#define ENC_1_PWM_PERIOD_BUF_VALUE           (65535lu)
#define ENC_1_PWM_PERIOD_SWAP                (0lu)
#define ENC_1_PWM_COMPARE_VALUE              (65535lu)
#define ENC_1_PWM_COMPARE_BUF_VALUE          (65535lu)
#define ENC_1_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ENC_1__LEFT 0
#define ENC_1__RIGHT 1
#define ENC_1__CENTER 2
#define ENC_1__ASYMMETRIC 3

#define ENC_1__X1 0
#define ENC_1__X2 1
#define ENC_1__X4 2

#define ENC_1__PWM 4
#define ENC_1__PWM_DT 5
#define ENC_1__PWM_PR 6

#define ENC_1__INVERSE 1
#define ENC_1__DIRECT 0

#define ENC_1__CAPTURE 2
#define ENC_1__COMPARE 0

#define ENC_1__TRIG_LEVEL 3
#define ENC_1__TRIG_RISING 0
#define ENC_1__TRIG_FALLING 1
#define ENC_1__TRIG_BOTH 2

#define ENC_1__INTR_MASK_TC 1
#define ENC_1__INTR_MASK_CC_MATCH 2
#define ENC_1__INTR_MASK_NONE 0
#define ENC_1__INTR_MASK_TC_CC 3

#define ENC_1__UNCONFIG 8
#define ENC_1__TIMER 1
#define ENC_1__QUAD 3
#define ENC_1__PWM_SEL 7

#define ENC_1__COUNT_UP 0
#define ENC_1__COUNT_DOWN 1
#define ENC_1__COUNT_UPDOWN0 2
#define ENC_1__COUNT_UPDOWN1 3


/* Prescaler */
#define ENC_1_PRESCALE_DIVBY1                ((uint32)(0u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY2                ((uint32)(1u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY4                ((uint32)(2u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY8                ((uint32)(3u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY16               ((uint32)(4u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY32               ((uint32)(5u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY64               ((uint32)(6u << ENC_1_PRESCALER_SHIFT))
#define ENC_1_PRESCALE_DIVBY128              ((uint32)(7u << ENC_1_PRESCALER_SHIFT))

/* TCPWM set modes */
#define ENC_1_MODE_TIMER_COMPARE             ((uint32)(ENC_1__COMPARE         <<  \
                                                                  ENC_1_MODE_SHIFT))
#define ENC_1_MODE_TIMER_CAPTURE             ((uint32)(ENC_1__CAPTURE         <<  \
                                                                  ENC_1_MODE_SHIFT))
#define ENC_1_MODE_QUAD                      ((uint32)(ENC_1__QUAD            <<  \
                                                                  ENC_1_MODE_SHIFT))
#define ENC_1_MODE_PWM                       ((uint32)(ENC_1__PWM             <<  \
                                                                  ENC_1_MODE_SHIFT))
#define ENC_1_MODE_PWM_DT                    ((uint32)(ENC_1__PWM_DT          <<  \
                                                                  ENC_1_MODE_SHIFT))
#define ENC_1_MODE_PWM_PR                    ((uint32)(ENC_1__PWM_PR          <<  \
                                                                  ENC_1_MODE_SHIFT))

/* Quad Modes */
#define ENC_1_MODE_X1                        ((uint32)(ENC_1__X1              <<  \
                                                                  ENC_1_QUAD_MODE_SHIFT))
#define ENC_1_MODE_X2                        ((uint32)(ENC_1__X2              <<  \
                                                                  ENC_1_QUAD_MODE_SHIFT))
#define ENC_1_MODE_X4                        ((uint32)(ENC_1__X4              <<  \
                                                                  ENC_1_QUAD_MODE_SHIFT))

/* Counter modes */
#define ENC_1_COUNT_UP                       ((uint32)(ENC_1__COUNT_UP        <<  \
                                                                  ENC_1_UPDOWN_SHIFT))
#define ENC_1_COUNT_DOWN                     ((uint32)(ENC_1__COUNT_DOWN      <<  \
                                                                  ENC_1_UPDOWN_SHIFT))
#define ENC_1_COUNT_UPDOWN0                  ((uint32)(ENC_1__COUNT_UPDOWN0   <<  \
                                                                  ENC_1_UPDOWN_SHIFT))
#define ENC_1_COUNT_UPDOWN1                  ((uint32)(ENC_1__COUNT_UPDOWN1   <<  \
                                                                  ENC_1_UPDOWN_SHIFT))

/* PWM output invert */
#define ENC_1_INVERT_LINE                    ((uint32)(ENC_1__INVERSE         <<  \
                                                                  ENC_1_INV_OUT_SHIFT))
#define ENC_1_INVERT_LINE_N                  ((uint32)(ENC_1__INVERSE         <<  \
                                                                  ENC_1_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define ENC_1_TRIG_RISING                    ((uint32)ENC_1__TRIG_RISING)
#define ENC_1_TRIG_FALLING                   ((uint32)ENC_1__TRIG_FALLING)
#define ENC_1_TRIG_BOTH                      ((uint32)ENC_1__TRIG_BOTH)
#define ENC_1_TRIG_LEVEL                     ((uint32)ENC_1__TRIG_LEVEL)

/* Interrupt mask */
#define ENC_1_INTR_MASK_TC                   ((uint32)ENC_1__INTR_MASK_TC)
#define ENC_1_INTR_MASK_CC_MATCH             ((uint32)ENC_1__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define ENC_1_CC_MATCH_SET                   (0x00u)
#define ENC_1_CC_MATCH_CLEAR                 (0x01u)
#define ENC_1_CC_MATCH_INVERT                (0x02u)
#define ENC_1_CC_MATCH_NO_CHANGE             (0x03u)
#define ENC_1_OVERLOW_SET                    (0x00u)
#define ENC_1_OVERLOW_CLEAR                  (0x04u)
#define ENC_1_OVERLOW_INVERT                 (0x08u)
#define ENC_1_OVERLOW_NO_CHANGE              (0x0Cu)
#define ENC_1_UNDERFLOW_SET                  (0x00u)
#define ENC_1_UNDERFLOW_CLEAR                (0x10u)
#define ENC_1_UNDERFLOW_INVERT               (0x20u)
#define ENC_1_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define ENC_1_PWM_MODE_LEFT                  (ENC_1_CC_MATCH_CLEAR        |   \
                                                         ENC_1_OVERLOW_SET           |   \
                                                         ENC_1_UNDERFLOW_NO_CHANGE)
#define ENC_1_PWM_MODE_RIGHT                 (ENC_1_CC_MATCH_SET          |   \
                                                         ENC_1_OVERLOW_NO_CHANGE     |   \
                                                         ENC_1_UNDERFLOW_CLEAR)
#define ENC_1_PWM_MODE_ASYM                  (ENC_1_CC_MATCH_INVERT       |   \
                                                         ENC_1_OVERLOW_SET           |   \
                                                         ENC_1_UNDERFLOW_CLEAR)

#if (ENC_1_CY_TCPWM_V2)
    #if(ENC_1_CY_TCPWM_4000)
        #define ENC_1_PWM_MODE_CENTER                (ENC_1_CC_MATCH_INVERT       |   \
                                                                 ENC_1_OVERLOW_NO_CHANGE     |   \
                                                                 ENC_1_UNDERFLOW_CLEAR)
    #else
        #define ENC_1_PWM_MODE_CENTER                (ENC_1_CC_MATCH_INVERT       |   \
                                                                 ENC_1_OVERLOW_SET           |   \
                                                                 ENC_1_UNDERFLOW_CLEAR)
    #endif /* (ENC_1_CY_TCPWM_4000) */
#else
    #define ENC_1_PWM_MODE_CENTER                (ENC_1_CC_MATCH_INVERT       |   \
                                                             ENC_1_OVERLOW_NO_CHANGE     |   \
                                                             ENC_1_UNDERFLOW_CLEAR)
#endif /* (ENC_1_CY_TCPWM_NEW) */

/* Command operations without condition */
#define ENC_1_CMD_CAPTURE                    (0u)
#define ENC_1_CMD_RELOAD                     (8u)
#define ENC_1_CMD_STOP                       (16u)
#define ENC_1_CMD_START                      (24u)

/* Status */
#define ENC_1_STATUS_DOWN                    (1u)
#define ENC_1_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   ENC_1_Init(void);
void   ENC_1_Enable(void);
void   ENC_1_Start(void);
void   ENC_1_Stop(void);

void   ENC_1_SetMode(uint32 mode);
void   ENC_1_SetCounterMode(uint32 counterMode);
void   ENC_1_SetPWMMode(uint32 modeMask);
void   ENC_1_SetQDMode(uint32 qdMode);

void   ENC_1_SetPrescaler(uint32 prescaler);
void   ENC_1_TriggerCommand(uint32 mask, uint32 command);
void   ENC_1_SetOneShot(uint32 oneShotEnable);
uint32 ENC_1_ReadStatus(void);

void   ENC_1_SetPWMSyncKill(uint32 syncKillEnable);
void   ENC_1_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   ENC_1_SetPWMDeadTime(uint32 deadTime);
void   ENC_1_SetPWMInvert(uint32 mask);

void   ENC_1_SetInterruptMode(uint32 interruptMask);
uint32 ENC_1_GetInterruptSourceMasked(void);
uint32 ENC_1_GetInterruptSource(void);
void   ENC_1_ClearInterrupt(uint32 interruptMask);
void   ENC_1_SetInterrupt(uint32 interruptMask);

void   ENC_1_WriteCounter(uint32 count);
uint32 ENC_1_ReadCounter(void);

uint32 ENC_1_ReadCapture(void);
uint32 ENC_1_ReadCaptureBuf(void);

void   ENC_1_WritePeriod(uint32 period);
uint32 ENC_1_ReadPeriod(void);
void   ENC_1_WritePeriodBuf(uint32 periodBuf);
uint32 ENC_1_ReadPeriodBuf(void);

void   ENC_1_WriteCompare(uint32 compare);
uint32 ENC_1_ReadCompare(void);
void   ENC_1_WriteCompareBuf(uint32 compareBuf);
uint32 ENC_1_ReadCompareBuf(void);

void   ENC_1_SetPeriodSwap(uint32 swapEnable);
void   ENC_1_SetCompareSwap(uint32 swapEnable);

void   ENC_1_SetCaptureMode(uint32 triggerMode);
void   ENC_1_SetReloadMode(uint32 triggerMode);
void   ENC_1_SetStartMode(uint32 triggerMode);
void   ENC_1_SetStopMode(uint32 triggerMode);
void   ENC_1_SetCountMode(uint32 triggerMode);

void   ENC_1_SaveConfig(void);
void   ENC_1_RestoreConfig(void);
void   ENC_1_Sleep(void);
void   ENC_1_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define ENC_1_BLOCK_CONTROL_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ENC_1_BLOCK_CONTROL_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ENC_1_COMMAND_REG                    (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ENC_1_COMMAND_PTR                    ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ENC_1_INTRRUPT_CAUSE_REG             (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ENC_1_INTRRUPT_CAUSE_PTR             ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ENC_1_CONTROL_REG                    (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__CTRL )
#define ENC_1_CONTROL_PTR                    ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__CTRL )
#define ENC_1_STATUS_REG                     (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__STATUS )
#define ENC_1_STATUS_PTR                     ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__STATUS )
#define ENC_1_COUNTER_REG                    (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__COUNTER )
#define ENC_1_COUNTER_PTR                    ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__COUNTER )
#define ENC_1_COMP_CAP_REG                   (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__CC )
#define ENC_1_COMP_CAP_PTR                   ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__CC )
#define ENC_1_COMP_CAP_BUF_REG               (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define ENC_1_COMP_CAP_BUF_PTR               ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__CC_BUFF )
#define ENC_1_PERIOD_REG                     (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__PERIOD )
#define ENC_1_PERIOD_PTR                     ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__PERIOD )
#define ENC_1_PERIOD_BUF_REG                 (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ENC_1_PERIOD_BUF_PTR                 ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ENC_1_TRIG_CONTROL0_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ENC_1_TRIG_CONTROL0_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ENC_1_TRIG_CONTROL1_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ENC_1_TRIG_CONTROL1_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ENC_1_TRIG_CONTROL2_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ENC_1_TRIG_CONTROL2_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ENC_1_INTERRUPT_REQ_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR )
#define ENC_1_INTERRUPT_REQ_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR )
#define ENC_1_INTERRUPT_SET_REG              (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_SET )
#define ENC_1_INTERRUPT_SET_PTR              ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_SET )
#define ENC_1_INTERRUPT_MASK_REG             (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define ENC_1_INTERRUPT_MASK_PTR             ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_MASK )
#define ENC_1_INTERRUPT_MASKED_REG           (*(reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_MASKED )
#define ENC_1_INTERRUPT_MASKED_PTR           ( (reg32 *) ENC_1_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define ENC_1_MASK                           ((uint32)ENC_1_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define ENC_1_RELOAD_CC_SHIFT                (0u)
#define ENC_1_RELOAD_PERIOD_SHIFT            (1u)
#define ENC_1_PWM_SYNC_KILL_SHIFT            (2u)
#define ENC_1_PWM_STOP_KILL_SHIFT            (3u)
#define ENC_1_PRESCALER_SHIFT                (8u)
#define ENC_1_UPDOWN_SHIFT                   (16u)
#define ENC_1_ONESHOT_SHIFT                  (18u)
#define ENC_1_QUAD_MODE_SHIFT                (20u)
#define ENC_1_INV_OUT_SHIFT                  (20u)
#define ENC_1_INV_COMPL_OUT_SHIFT            (21u)
#define ENC_1_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define ENC_1_RELOAD_CC_MASK                 ((uint32)(ENC_1_1BIT_MASK        <<  \
                                                                            ENC_1_RELOAD_CC_SHIFT))
#define ENC_1_RELOAD_PERIOD_MASK             ((uint32)(ENC_1_1BIT_MASK        <<  \
                                                                            ENC_1_RELOAD_PERIOD_SHIFT))
#define ENC_1_PWM_SYNC_KILL_MASK             ((uint32)(ENC_1_1BIT_MASK        <<  \
                                                                            ENC_1_PWM_SYNC_KILL_SHIFT))
#define ENC_1_PWM_STOP_KILL_MASK             ((uint32)(ENC_1_1BIT_MASK        <<  \
                                                                            ENC_1_PWM_STOP_KILL_SHIFT))
#define ENC_1_PRESCALER_MASK                 ((uint32)(ENC_1_8BIT_MASK        <<  \
                                                                            ENC_1_PRESCALER_SHIFT))
#define ENC_1_UPDOWN_MASK                    ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                            ENC_1_UPDOWN_SHIFT))
#define ENC_1_ONESHOT_MASK                   ((uint32)(ENC_1_1BIT_MASK        <<  \
                                                                            ENC_1_ONESHOT_SHIFT))
#define ENC_1_QUAD_MODE_MASK                 ((uint32)(ENC_1_3BIT_MASK        <<  \
                                                                            ENC_1_QUAD_MODE_SHIFT))
#define ENC_1_INV_OUT_MASK                   ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                            ENC_1_INV_OUT_SHIFT))
#define ENC_1_MODE_MASK                      ((uint32)(ENC_1_3BIT_MASK        <<  \
                                                                            ENC_1_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define ENC_1_CAPTURE_SHIFT                  (0u)
#define ENC_1_COUNT_SHIFT                    (2u)
#define ENC_1_RELOAD_SHIFT                   (4u)
#define ENC_1_STOP_SHIFT                     (6u)
#define ENC_1_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define ENC_1_CAPTURE_MASK                   ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                  ENC_1_CAPTURE_SHIFT))
#define ENC_1_COUNT_MASK                     ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                  ENC_1_COUNT_SHIFT))
#define ENC_1_RELOAD_MASK                    ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                  ENC_1_RELOAD_SHIFT))
#define ENC_1_STOP_MASK                      ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                  ENC_1_STOP_SHIFT))
#define ENC_1_START_MASK                     ((uint32)(ENC_1_2BIT_MASK        <<  \
                                                                  ENC_1_START_SHIFT))

/* MASK */
#define ENC_1_1BIT_MASK                      ((uint32)0x01u)
#define ENC_1_2BIT_MASK                      ((uint32)0x03u)
#define ENC_1_3BIT_MASK                      ((uint32)0x07u)
#define ENC_1_6BIT_MASK                      ((uint32)0x3Fu)
#define ENC_1_8BIT_MASK                      ((uint32)0xFFu)
#define ENC_1_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define ENC_1_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define ENC_1_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(ENC_1_QUAD_ENCODING_MODES     << ENC_1_QUAD_MODE_SHIFT))       |\
         ((uint32)(ENC_1_CONFIG                  << ENC_1_MODE_SHIFT)))

#define ENC_1_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(ENC_1_PWM_STOP_EVENT          << ENC_1_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(ENC_1_PWM_OUT_INVERT          << ENC_1_INV_OUT_SHIFT))         |\
         ((uint32)(ENC_1_PWM_OUT_N_INVERT        << ENC_1_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(ENC_1_PWM_MODE                << ENC_1_MODE_SHIFT)))

#define ENC_1_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(ENC_1_PWM_RUN_MODE         << ENC_1_ONESHOT_SHIFT))
            
#define ENC_1_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(ENC_1_PWM_ALIGN            << ENC_1_UPDOWN_SHIFT))

#define ENC_1_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(ENC_1_PWM_KILL_EVENT      << ENC_1_PWM_SYNC_KILL_SHIFT))

#define ENC_1_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(ENC_1_PWM_DEAD_TIME_CYCLE  << ENC_1_PRESCALER_SHIFT))

#define ENC_1_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(ENC_1_PWM_PRESCALER        << ENC_1_PRESCALER_SHIFT))

#define ENC_1_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(ENC_1_TC_PRESCALER            << ENC_1_PRESCALER_SHIFT))       |\
         ((uint32)(ENC_1_TC_COUNTER_MODE         << ENC_1_UPDOWN_SHIFT))          |\
         ((uint32)(ENC_1_TC_RUN_MODE             << ENC_1_ONESHOT_SHIFT))         |\
         ((uint32)(ENC_1_TC_COMP_CAP_MODE        << ENC_1_MODE_SHIFT)))
        
#define ENC_1_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(ENC_1_QUAD_PHIA_SIGNAL_MODE   << ENC_1_COUNT_SHIFT))           |\
         ((uint32)(ENC_1_QUAD_INDEX_SIGNAL_MODE  << ENC_1_RELOAD_SHIFT))          |\
         ((uint32)(ENC_1_QUAD_STOP_SIGNAL_MODE   << ENC_1_STOP_SHIFT))            |\
         ((uint32)(ENC_1_QUAD_PHIB_SIGNAL_MODE   << ENC_1_START_SHIFT)))

#define ENC_1_PWM_SIGNALS_MODES                                                              \
        (((uint32)(ENC_1_PWM_SWITCH_SIGNAL_MODE  << ENC_1_CAPTURE_SHIFT))         |\
         ((uint32)(ENC_1_PWM_COUNT_SIGNAL_MODE   << ENC_1_COUNT_SHIFT))           |\
         ((uint32)(ENC_1_PWM_RELOAD_SIGNAL_MODE  << ENC_1_RELOAD_SHIFT))          |\
         ((uint32)(ENC_1_PWM_STOP_SIGNAL_MODE    << ENC_1_STOP_SHIFT))            |\
         ((uint32)(ENC_1_PWM_START_SIGNAL_MODE   << ENC_1_START_SHIFT)))

#define ENC_1_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(ENC_1_TC_CAPTURE_SIGNAL_MODE  << ENC_1_CAPTURE_SHIFT))         |\
         ((uint32)(ENC_1_TC_COUNT_SIGNAL_MODE    << ENC_1_COUNT_SHIFT))           |\
         ((uint32)(ENC_1_TC_RELOAD_SIGNAL_MODE   << ENC_1_RELOAD_SHIFT))          |\
         ((uint32)(ENC_1_TC_STOP_SIGNAL_MODE     << ENC_1_STOP_SHIFT))            |\
         ((uint32)(ENC_1_TC_START_SIGNAL_MODE    << ENC_1_START_SHIFT)))
        
#define ENC_1_TIMER_UPDOWN_CNT_USED                                                          \
                ((ENC_1__COUNT_UPDOWN0 == ENC_1_TC_COUNTER_MODE)                  ||\
                 (ENC_1__COUNT_UPDOWN1 == ENC_1_TC_COUNTER_MODE))

#define ENC_1_PWM_UPDOWN_CNT_USED                                                            \
                ((ENC_1__CENTER == ENC_1_PWM_ALIGN)                               ||\
                 (ENC_1__ASYMMETRIC == ENC_1_PWM_ALIGN))               
        
#define ENC_1_PWM_PR_INIT_VALUE              (1u)
#define ENC_1_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_ENC_1_H */

/* [] END OF FILE */
