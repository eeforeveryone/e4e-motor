/*******************************************************************************
* File Name: Clock_pwm.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_pwm_H)
#define CY_CLOCK_Clock_pwm_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock_pwm_StartEx(uint32 alignClkDiv);
#define Clock_pwm_Start() \
    Clock_pwm_StartEx(Clock_pwm__PA_DIV_ID)

#else

void Clock_pwm_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock_pwm_Stop(void);

void Clock_pwm_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_pwm_GetDividerRegister(void);
uint8  Clock_pwm_GetFractionalDividerRegister(void);

#define Clock_pwm_Enable()                         Clock_pwm_Start()
#define Clock_pwm_Disable()                        Clock_pwm_Stop()
#define Clock_pwm_SetDividerRegister(clkDivider, reset)  \
    Clock_pwm_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_pwm_SetDivider(clkDivider)           Clock_pwm_SetDividerRegister((clkDivider), 1u)
#define Clock_pwm_SetDividerValue(clkDivider)      Clock_pwm_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock_pwm_DIV_ID     Clock_pwm__DIV_ID

#define Clock_pwm_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock_pwm_CTRL_REG   (*(reg32 *)Clock_pwm__CTRL_REGISTER)
#define Clock_pwm_DIV_REG    (*(reg32 *)Clock_pwm__DIV_REGISTER)

#define Clock_pwm_CMD_DIV_SHIFT          (0u)
#define Clock_pwm_CMD_PA_DIV_SHIFT       (8u)
#define Clock_pwm_CMD_DISABLE_SHIFT      (30u)
#define Clock_pwm_CMD_ENABLE_SHIFT       (31u)

#define Clock_pwm_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock_pwm_CMD_DISABLE_SHIFT))
#define Clock_pwm_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock_pwm_CMD_ENABLE_SHIFT))

#define Clock_pwm_DIV_FRAC_MASK  (0x000000F8u)
#define Clock_pwm_DIV_FRAC_SHIFT (3u)
#define Clock_pwm_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock_pwm_DIV_INT_SHIFT  (8u)

#else 

#define Clock_pwm_DIV_REG        (*(reg32 *)Clock_pwm__REGISTER)
#define Clock_pwm_ENABLE_REG     Clock_pwm_DIV_REG
#define Clock_pwm_DIV_FRAC_MASK  Clock_pwm__FRAC_MASK
#define Clock_pwm_DIV_FRAC_SHIFT (16u)
#define Clock_pwm_DIV_INT_MASK   Clock_pwm__DIVIDER_MASK
#define Clock_pwm_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock_pwm_H) */

/* [] END OF FILE */
