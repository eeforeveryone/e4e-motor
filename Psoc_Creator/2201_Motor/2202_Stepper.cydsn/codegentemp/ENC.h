/*******************************************************************************
* File Name: ENC.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the ENC
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

#if !defined(CY_TCPWM_ENC_H)
#define CY_TCPWM_ENC_H


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
} ENC_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  ENC_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ENC_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define ENC_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define ENC_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define ENC_QUAD_ENCODING_MODES            (0lu)
#define ENC_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define ENC_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define ENC_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define ENC_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define ENC_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define ENC_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define ENC_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define ENC_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define ENC_TC_RUN_MODE                    (0lu)
#define ENC_TC_COUNTER_MODE                (0lu)
#define ENC_TC_COMP_CAP_MODE               (2lu)
#define ENC_TC_PRESCALER                   (0lu)

/* Signal modes */
#define ENC_TC_RELOAD_SIGNAL_MODE          (0lu)
#define ENC_TC_COUNT_SIGNAL_MODE           (3lu)
#define ENC_TC_START_SIGNAL_MODE           (0lu)
#define ENC_TC_STOP_SIGNAL_MODE            (0lu)
#define ENC_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define ENC_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define ENC_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define ENC_TC_START_SIGNAL_PRESENT        (0lu)
#define ENC_TC_STOP_SIGNAL_PRESENT         (0lu)
#define ENC_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ENC_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define ENC_PWM_KILL_EVENT                 (0lu)
#define ENC_PWM_STOP_EVENT                 (0lu)
#define ENC_PWM_MODE                       (4lu)
#define ENC_PWM_OUT_N_INVERT               (0lu)
#define ENC_PWM_OUT_INVERT                 (0lu)
#define ENC_PWM_ALIGN                      (0lu)
#define ENC_PWM_RUN_MODE                   (0lu)
#define ENC_PWM_DEAD_TIME_CYCLE            (0lu)
#define ENC_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define ENC_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define ENC_PWM_COUNT_SIGNAL_MODE          (3lu)
#define ENC_PWM_START_SIGNAL_MODE          (0lu)
#define ENC_PWM_STOP_SIGNAL_MODE           (0lu)
#define ENC_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define ENC_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define ENC_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define ENC_PWM_START_SIGNAL_PRESENT       (0lu)
#define ENC_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define ENC_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ENC_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define ENC_TC_PERIOD_VALUE                (65535lu)
#define ENC_TC_COMPARE_VALUE               (65535lu)
#define ENC_TC_COMPARE_BUF_VALUE           (65535lu)
#define ENC_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define ENC_PWM_PERIOD_VALUE               (65535lu)
#define ENC_PWM_PERIOD_BUF_VALUE           (65535lu)
#define ENC_PWM_PERIOD_SWAP                (0lu)
#define ENC_PWM_COMPARE_VALUE              (65535lu)
#define ENC_PWM_COMPARE_BUF_VALUE          (65535lu)
#define ENC_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ENC__LEFT 0
#define ENC__RIGHT 1
#define ENC__CENTER 2
#define ENC__ASYMMETRIC 3

#define ENC__X1 0
#define ENC__X2 1
#define ENC__X4 2

#define ENC__PWM 4
#define ENC__PWM_DT 5
#define ENC__PWM_PR 6

#define ENC__INVERSE 1
#define ENC__DIRECT 0

#define ENC__CAPTURE 2
#define ENC__COMPARE 0

#define ENC__TRIG_LEVEL 3
#define ENC__TRIG_RISING 0
#define ENC__TRIG_FALLING 1
#define ENC__TRIG_BOTH 2

#define ENC__INTR_MASK_TC 1
#define ENC__INTR_MASK_CC_MATCH 2
#define ENC__INTR_MASK_NONE 0
#define ENC__INTR_MASK_TC_CC 3

#define ENC__UNCONFIG 8
#define ENC__TIMER 1
#define ENC__QUAD 3
#define ENC__PWM_SEL 7

#define ENC__COUNT_UP 0
#define ENC__COUNT_DOWN 1
#define ENC__COUNT_UPDOWN0 2
#define ENC__COUNT_UPDOWN1 3


/* Prescaler */
#define ENC_PRESCALE_DIVBY1                ((uint32)(0u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY2                ((uint32)(1u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY4                ((uint32)(2u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY8                ((uint32)(3u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY16               ((uint32)(4u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY32               ((uint32)(5u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY64               ((uint32)(6u << ENC_PRESCALER_SHIFT))
#define ENC_PRESCALE_DIVBY128              ((uint32)(7u << ENC_PRESCALER_SHIFT))

/* TCPWM set modes */
#define ENC_MODE_TIMER_COMPARE             ((uint32)(ENC__COMPARE         <<  \
                                                                  ENC_MODE_SHIFT))
#define ENC_MODE_TIMER_CAPTURE             ((uint32)(ENC__CAPTURE         <<  \
                                                                  ENC_MODE_SHIFT))
#define ENC_MODE_QUAD                      ((uint32)(ENC__QUAD            <<  \
                                                                  ENC_MODE_SHIFT))
#define ENC_MODE_PWM                       ((uint32)(ENC__PWM             <<  \
                                                                  ENC_MODE_SHIFT))
#define ENC_MODE_PWM_DT                    ((uint32)(ENC__PWM_DT          <<  \
                                                                  ENC_MODE_SHIFT))
#define ENC_MODE_PWM_PR                    ((uint32)(ENC__PWM_PR          <<  \
                                                                  ENC_MODE_SHIFT))

/* Quad Modes */
#define ENC_MODE_X1                        ((uint32)(ENC__X1              <<  \
                                                                  ENC_QUAD_MODE_SHIFT))
#define ENC_MODE_X2                        ((uint32)(ENC__X2              <<  \
                                                                  ENC_QUAD_MODE_SHIFT))
#define ENC_MODE_X4                        ((uint32)(ENC__X4              <<  \
                                                                  ENC_QUAD_MODE_SHIFT))

/* Counter modes */
#define ENC_COUNT_UP                       ((uint32)(ENC__COUNT_UP        <<  \
                                                                  ENC_UPDOWN_SHIFT))
#define ENC_COUNT_DOWN                     ((uint32)(ENC__COUNT_DOWN      <<  \
                                                                  ENC_UPDOWN_SHIFT))
#define ENC_COUNT_UPDOWN0                  ((uint32)(ENC__COUNT_UPDOWN0   <<  \
                                                                  ENC_UPDOWN_SHIFT))
#define ENC_COUNT_UPDOWN1                  ((uint32)(ENC__COUNT_UPDOWN1   <<  \
                                                                  ENC_UPDOWN_SHIFT))

/* PWM output invert */
#define ENC_INVERT_LINE                    ((uint32)(ENC__INVERSE         <<  \
                                                                  ENC_INV_OUT_SHIFT))
#define ENC_INVERT_LINE_N                  ((uint32)(ENC__INVERSE         <<  \
                                                                  ENC_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define ENC_TRIG_RISING                    ((uint32)ENC__TRIG_RISING)
#define ENC_TRIG_FALLING                   ((uint32)ENC__TRIG_FALLING)
#define ENC_TRIG_BOTH                      ((uint32)ENC__TRIG_BOTH)
#define ENC_TRIG_LEVEL                     ((uint32)ENC__TRIG_LEVEL)

/* Interrupt mask */
#define ENC_INTR_MASK_TC                   ((uint32)ENC__INTR_MASK_TC)
#define ENC_INTR_MASK_CC_MATCH             ((uint32)ENC__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define ENC_CC_MATCH_SET                   (0x00u)
#define ENC_CC_MATCH_CLEAR                 (0x01u)
#define ENC_CC_MATCH_INVERT                (0x02u)
#define ENC_CC_MATCH_NO_CHANGE             (0x03u)
#define ENC_OVERLOW_SET                    (0x00u)
#define ENC_OVERLOW_CLEAR                  (0x04u)
#define ENC_OVERLOW_INVERT                 (0x08u)
#define ENC_OVERLOW_NO_CHANGE              (0x0Cu)
#define ENC_UNDERFLOW_SET                  (0x00u)
#define ENC_UNDERFLOW_CLEAR                (0x10u)
#define ENC_UNDERFLOW_INVERT               (0x20u)
#define ENC_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define ENC_PWM_MODE_LEFT                  (ENC_CC_MATCH_CLEAR        |   \
                                                         ENC_OVERLOW_SET           |   \
                                                         ENC_UNDERFLOW_NO_CHANGE)
#define ENC_PWM_MODE_RIGHT                 (ENC_CC_MATCH_SET          |   \
                                                         ENC_OVERLOW_NO_CHANGE     |   \
                                                         ENC_UNDERFLOW_CLEAR)
#define ENC_PWM_MODE_ASYM                  (ENC_CC_MATCH_INVERT       |   \
                                                         ENC_OVERLOW_SET           |   \
                                                         ENC_UNDERFLOW_CLEAR)

#if (ENC_CY_TCPWM_V2)
    #if(ENC_CY_TCPWM_4000)
        #define ENC_PWM_MODE_CENTER                (ENC_CC_MATCH_INVERT       |   \
                                                                 ENC_OVERLOW_NO_CHANGE     |   \
                                                                 ENC_UNDERFLOW_CLEAR)
    #else
        #define ENC_PWM_MODE_CENTER                (ENC_CC_MATCH_INVERT       |   \
                                                                 ENC_OVERLOW_SET           |   \
                                                                 ENC_UNDERFLOW_CLEAR)
    #endif /* (ENC_CY_TCPWM_4000) */
#else
    #define ENC_PWM_MODE_CENTER                (ENC_CC_MATCH_INVERT       |   \
                                                             ENC_OVERLOW_NO_CHANGE     |   \
                                                             ENC_UNDERFLOW_CLEAR)
#endif /* (ENC_CY_TCPWM_NEW) */

/* Command operations without condition */
#define ENC_CMD_CAPTURE                    (0u)
#define ENC_CMD_RELOAD                     (8u)
#define ENC_CMD_STOP                       (16u)
#define ENC_CMD_START                      (24u)

/* Status */
#define ENC_STATUS_DOWN                    (1u)
#define ENC_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   ENC_Init(void);
void   ENC_Enable(void);
void   ENC_Start(void);
void   ENC_Stop(void);

void   ENC_SetMode(uint32 mode);
void   ENC_SetCounterMode(uint32 counterMode);
void   ENC_SetPWMMode(uint32 modeMask);
void   ENC_SetQDMode(uint32 qdMode);

void   ENC_SetPrescaler(uint32 prescaler);
void   ENC_TriggerCommand(uint32 mask, uint32 command);
void   ENC_SetOneShot(uint32 oneShotEnable);
uint32 ENC_ReadStatus(void);

void   ENC_SetPWMSyncKill(uint32 syncKillEnable);
void   ENC_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   ENC_SetPWMDeadTime(uint32 deadTime);
void   ENC_SetPWMInvert(uint32 mask);

void   ENC_SetInterruptMode(uint32 interruptMask);
uint32 ENC_GetInterruptSourceMasked(void);
uint32 ENC_GetInterruptSource(void);
void   ENC_ClearInterrupt(uint32 interruptMask);
void   ENC_SetInterrupt(uint32 interruptMask);

void   ENC_WriteCounter(uint32 count);
uint32 ENC_ReadCounter(void);

uint32 ENC_ReadCapture(void);
uint32 ENC_ReadCaptureBuf(void);

void   ENC_WritePeriod(uint32 period);
uint32 ENC_ReadPeriod(void);
void   ENC_WritePeriodBuf(uint32 periodBuf);
uint32 ENC_ReadPeriodBuf(void);

void   ENC_WriteCompare(uint32 compare);
uint32 ENC_ReadCompare(void);
void   ENC_WriteCompareBuf(uint32 compareBuf);
uint32 ENC_ReadCompareBuf(void);

void   ENC_SetPeriodSwap(uint32 swapEnable);
void   ENC_SetCompareSwap(uint32 swapEnable);

void   ENC_SetCaptureMode(uint32 triggerMode);
void   ENC_SetReloadMode(uint32 triggerMode);
void   ENC_SetStartMode(uint32 triggerMode);
void   ENC_SetStopMode(uint32 triggerMode);
void   ENC_SetCountMode(uint32 triggerMode);

void   ENC_SaveConfig(void);
void   ENC_RestoreConfig(void);
void   ENC_Sleep(void);
void   ENC_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define ENC_BLOCK_CONTROL_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ENC_BLOCK_CONTROL_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ENC_COMMAND_REG                    (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ENC_COMMAND_PTR                    ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ENC_INTRRUPT_CAUSE_REG             (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ENC_INTRRUPT_CAUSE_PTR             ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ENC_CONTROL_REG                    (*(reg32 *) ENC_cy_m0s8_tcpwm_1__CTRL )
#define ENC_CONTROL_PTR                    ( (reg32 *) ENC_cy_m0s8_tcpwm_1__CTRL )
#define ENC_STATUS_REG                     (*(reg32 *) ENC_cy_m0s8_tcpwm_1__STATUS )
#define ENC_STATUS_PTR                     ( (reg32 *) ENC_cy_m0s8_tcpwm_1__STATUS )
#define ENC_COUNTER_REG                    (*(reg32 *) ENC_cy_m0s8_tcpwm_1__COUNTER )
#define ENC_COUNTER_PTR                    ( (reg32 *) ENC_cy_m0s8_tcpwm_1__COUNTER )
#define ENC_COMP_CAP_REG                   (*(reg32 *) ENC_cy_m0s8_tcpwm_1__CC )
#define ENC_COMP_CAP_PTR                   ( (reg32 *) ENC_cy_m0s8_tcpwm_1__CC )
#define ENC_COMP_CAP_BUF_REG               (*(reg32 *) ENC_cy_m0s8_tcpwm_1__CC_BUFF )
#define ENC_COMP_CAP_BUF_PTR               ( (reg32 *) ENC_cy_m0s8_tcpwm_1__CC_BUFF )
#define ENC_PERIOD_REG                     (*(reg32 *) ENC_cy_m0s8_tcpwm_1__PERIOD )
#define ENC_PERIOD_PTR                     ( (reg32 *) ENC_cy_m0s8_tcpwm_1__PERIOD )
#define ENC_PERIOD_BUF_REG                 (*(reg32 *) ENC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ENC_PERIOD_BUF_PTR                 ( (reg32 *) ENC_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ENC_TRIG_CONTROL0_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ENC_TRIG_CONTROL0_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ENC_TRIG_CONTROL1_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ENC_TRIG_CONTROL1_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ENC_TRIG_CONTROL2_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ENC_TRIG_CONTROL2_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ENC_INTERRUPT_REQ_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__INTR )
#define ENC_INTERRUPT_REQ_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__INTR )
#define ENC_INTERRUPT_SET_REG              (*(reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_SET )
#define ENC_INTERRUPT_SET_PTR              ( (reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_SET )
#define ENC_INTERRUPT_MASK_REG             (*(reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_MASK )
#define ENC_INTERRUPT_MASK_PTR             ( (reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_MASK )
#define ENC_INTERRUPT_MASKED_REG           (*(reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_MASKED )
#define ENC_INTERRUPT_MASKED_PTR           ( (reg32 *) ENC_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define ENC_MASK                           ((uint32)ENC_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define ENC_RELOAD_CC_SHIFT                (0u)
#define ENC_RELOAD_PERIOD_SHIFT            (1u)
#define ENC_PWM_SYNC_KILL_SHIFT            (2u)
#define ENC_PWM_STOP_KILL_SHIFT            (3u)
#define ENC_PRESCALER_SHIFT                (8u)
#define ENC_UPDOWN_SHIFT                   (16u)
#define ENC_ONESHOT_SHIFT                  (18u)
#define ENC_QUAD_MODE_SHIFT                (20u)
#define ENC_INV_OUT_SHIFT                  (20u)
#define ENC_INV_COMPL_OUT_SHIFT            (21u)
#define ENC_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define ENC_RELOAD_CC_MASK                 ((uint32)(ENC_1BIT_MASK        <<  \
                                                                            ENC_RELOAD_CC_SHIFT))
#define ENC_RELOAD_PERIOD_MASK             ((uint32)(ENC_1BIT_MASK        <<  \
                                                                            ENC_RELOAD_PERIOD_SHIFT))
#define ENC_PWM_SYNC_KILL_MASK             ((uint32)(ENC_1BIT_MASK        <<  \
                                                                            ENC_PWM_SYNC_KILL_SHIFT))
#define ENC_PWM_STOP_KILL_MASK             ((uint32)(ENC_1BIT_MASK        <<  \
                                                                            ENC_PWM_STOP_KILL_SHIFT))
#define ENC_PRESCALER_MASK                 ((uint32)(ENC_8BIT_MASK        <<  \
                                                                            ENC_PRESCALER_SHIFT))
#define ENC_UPDOWN_MASK                    ((uint32)(ENC_2BIT_MASK        <<  \
                                                                            ENC_UPDOWN_SHIFT))
#define ENC_ONESHOT_MASK                   ((uint32)(ENC_1BIT_MASK        <<  \
                                                                            ENC_ONESHOT_SHIFT))
#define ENC_QUAD_MODE_MASK                 ((uint32)(ENC_3BIT_MASK        <<  \
                                                                            ENC_QUAD_MODE_SHIFT))
#define ENC_INV_OUT_MASK                   ((uint32)(ENC_2BIT_MASK        <<  \
                                                                            ENC_INV_OUT_SHIFT))
#define ENC_MODE_MASK                      ((uint32)(ENC_3BIT_MASK        <<  \
                                                                            ENC_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define ENC_CAPTURE_SHIFT                  (0u)
#define ENC_COUNT_SHIFT                    (2u)
#define ENC_RELOAD_SHIFT                   (4u)
#define ENC_STOP_SHIFT                     (6u)
#define ENC_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define ENC_CAPTURE_MASK                   ((uint32)(ENC_2BIT_MASK        <<  \
                                                                  ENC_CAPTURE_SHIFT))
#define ENC_COUNT_MASK                     ((uint32)(ENC_2BIT_MASK        <<  \
                                                                  ENC_COUNT_SHIFT))
#define ENC_RELOAD_MASK                    ((uint32)(ENC_2BIT_MASK        <<  \
                                                                  ENC_RELOAD_SHIFT))
#define ENC_STOP_MASK                      ((uint32)(ENC_2BIT_MASK        <<  \
                                                                  ENC_STOP_SHIFT))
#define ENC_START_MASK                     ((uint32)(ENC_2BIT_MASK        <<  \
                                                                  ENC_START_SHIFT))

/* MASK */
#define ENC_1BIT_MASK                      ((uint32)0x01u)
#define ENC_2BIT_MASK                      ((uint32)0x03u)
#define ENC_3BIT_MASK                      ((uint32)0x07u)
#define ENC_6BIT_MASK                      ((uint32)0x3Fu)
#define ENC_8BIT_MASK                      ((uint32)0xFFu)
#define ENC_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define ENC_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define ENC_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(ENC_QUAD_ENCODING_MODES     << ENC_QUAD_MODE_SHIFT))       |\
         ((uint32)(ENC_CONFIG                  << ENC_MODE_SHIFT)))

#define ENC_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(ENC_PWM_STOP_EVENT          << ENC_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(ENC_PWM_OUT_INVERT          << ENC_INV_OUT_SHIFT))         |\
         ((uint32)(ENC_PWM_OUT_N_INVERT        << ENC_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(ENC_PWM_MODE                << ENC_MODE_SHIFT)))

#define ENC_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(ENC_PWM_RUN_MODE         << ENC_ONESHOT_SHIFT))
            
#define ENC_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(ENC_PWM_ALIGN            << ENC_UPDOWN_SHIFT))

#define ENC_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(ENC_PWM_KILL_EVENT      << ENC_PWM_SYNC_KILL_SHIFT))

#define ENC_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(ENC_PWM_DEAD_TIME_CYCLE  << ENC_PRESCALER_SHIFT))

#define ENC_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(ENC_PWM_PRESCALER        << ENC_PRESCALER_SHIFT))

#define ENC_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(ENC_TC_PRESCALER            << ENC_PRESCALER_SHIFT))       |\
         ((uint32)(ENC_TC_COUNTER_MODE         << ENC_UPDOWN_SHIFT))          |\
         ((uint32)(ENC_TC_RUN_MODE             << ENC_ONESHOT_SHIFT))         |\
         ((uint32)(ENC_TC_COMP_CAP_MODE        << ENC_MODE_SHIFT)))
        
#define ENC_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(ENC_QUAD_PHIA_SIGNAL_MODE   << ENC_COUNT_SHIFT))           |\
         ((uint32)(ENC_QUAD_INDEX_SIGNAL_MODE  << ENC_RELOAD_SHIFT))          |\
         ((uint32)(ENC_QUAD_STOP_SIGNAL_MODE   << ENC_STOP_SHIFT))            |\
         ((uint32)(ENC_QUAD_PHIB_SIGNAL_MODE   << ENC_START_SHIFT)))

#define ENC_PWM_SIGNALS_MODES                                                              \
        (((uint32)(ENC_PWM_SWITCH_SIGNAL_MODE  << ENC_CAPTURE_SHIFT))         |\
         ((uint32)(ENC_PWM_COUNT_SIGNAL_MODE   << ENC_COUNT_SHIFT))           |\
         ((uint32)(ENC_PWM_RELOAD_SIGNAL_MODE  << ENC_RELOAD_SHIFT))          |\
         ((uint32)(ENC_PWM_STOP_SIGNAL_MODE    << ENC_STOP_SHIFT))            |\
         ((uint32)(ENC_PWM_START_SIGNAL_MODE   << ENC_START_SHIFT)))

#define ENC_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(ENC_TC_CAPTURE_SIGNAL_MODE  << ENC_CAPTURE_SHIFT))         |\
         ((uint32)(ENC_TC_COUNT_SIGNAL_MODE    << ENC_COUNT_SHIFT))           |\
         ((uint32)(ENC_TC_RELOAD_SIGNAL_MODE   << ENC_RELOAD_SHIFT))          |\
         ((uint32)(ENC_TC_STOP_SIGNAL_MODE     << ENC_STOP_SHIFT))            |\
         ((uint32)(ENC_TC_START_SIGNAL_MODE    << ENC_START_SHIFT)))
        
#define ENC_TIMER_UPDOWN_CNT_USED                                                          \
                ((ENC__COUNT_UPDOWN0 == ENC_TC_COUNTER_MODE)                  ||\
                 (ENC__COUNT_UPDOWN1 == ENC_TC_COUNTER_MODE))

#define ENC_PWM_UPDOWN_CNT_USED                                                            \
                ((ENC__CENTER == ENC_PWM_ALIGN)                               ||\
                 (ENC__ASYMMETRIC == ENC_PWM_ALIGN))               
        
#define ENC_PWM_PR_INIT_VALUE              (1u)
#define ENC_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_ENC_H */

/* [] END OF FILE */
