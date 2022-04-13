/*******************************************************************************
* File Name: N_MOTrst.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "N_MOTrst.h"

static N_MOTrst_BACKUP_STRUCT  N_MOTrst_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: N_MOTrst_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet N_MOTrst_SUT.c usage_N_MOTrst_Sleep_Wakeup
*******************************************************************************/
void N_MOTrst_Sleep(void)
{
    #if defined(N_MOTrst__PC)
        N_MOTrst_backup.pcState = N_MOTrst_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            N_MOTrst_backup.usbState = N_MOTrst_CR1_REG;
            N_MOTrst_USB_POWER_REG |= N_MOTrst_USBIO_ENTER_SLEEP;
            N_MOTrst_CR1_REG &= N_MOTrst_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(N_MOTrst__SIO)
        N_MOTrst_backup.sioState = N_MOTrst_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        N_MOTrst_SIO_REG &= (uint32)(~N_MOTrst_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: N_MOTrst_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to N_MOTrst_Sleep() for an example usage.
*******************************************************************************/
void N_MOTrst_Wakeup(void)
{
    #if defined(N_MOTrst__PC)
        N_MOTrst_PC = N_MOTrst_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            N_MOTrst_USB_POWER_REG &= N_MOTrst_USBIO_EXIT_SLEEP_PH1;
            N_MOTrst_CR1_REG = N_MOTrst_backup.usbState;
            N_MOTrst_USB_POWER_REG &= N_MOTrst_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(N_MOTrst__SIO)
        N_MOTrst_SIO_REG = N_MOTrst_backup.sioState;
    #endif
}


/* [] END OF FILE */
