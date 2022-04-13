/*******************************************************************************
* File Name: motA.c  
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
#include "motA.h"

static motA_BACKUP_STRUCT  motA_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: motA_Sleep
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
*  \snippet motA_SUT.c usage_motA_Sleep_Wakeup
*******************************************************************************/
void motA_Sleep(void)
{
    #if defined(motA__PC)
        motA_backup.pcState = motA_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            motA_backup.usbState = motA_CR1_REG;
            motA_USB_POWER_REG |= motA_USBIO_ENTER_SLEEP;
            motA_CR1_REG &= motA_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(motA__SIO)
        motA_backup.sioState = motA_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        motA_SIO_REG &= (uint32)(~motA_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: motA_Wakeup
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
*  Refer to motA_Sleep() for an example usage.
*******************************************************************************/
void motA_Wakeup(void)
{
    #if defined(motA__PC)
        motA_PC = motA_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            motA_USB_POWER_REG &= motA_USBIO_EXIT_SLEEP_PH1;
            motA_CR1_REG = motA_backup.usbState;
            motA_USB_POWER_REG &= motA_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(motA__SIO)
        motA_SIO_REG = motA_backup.sioState;
    #endif
}


/* [] END OF FILE */
