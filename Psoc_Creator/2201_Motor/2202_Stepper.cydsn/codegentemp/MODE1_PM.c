/*******************************************************************************
* File Name: MODE1.c  
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
#include "MODE1.h"

static MODE1_BACKUP_STRUCT  MODE1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: MODE1_Sleep
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
*  \snippet MODE1_SUT.c usage_MODE1_Sleep_Wakeup
*******************************************************************************/
void MODE1_Sleep(void)
{
    #if defined(MODE1__PC)
        MODE1_backup.pcState = MODE1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            MODE1_backup.usbState = MODE1_CR1_REG;
            MODE1_USB_POWER_REG |= MODE1_USBIO_ENTER_SLEEP;
            MODE1_CR1_REG &= MODE1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MODE1__SIO)
        MODE1_backup.sioState = MODE1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        MODE1_SIO_REG &= (uint32)(~MODE1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: MODE1_Wakeup
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
*  Refer to MODE1_Sleep() for an example usage.
*******************************************************************************/
void MODE1_Wakeup(void)
{
    #if defined(MODE1__PC)
        MODE1_PC = MODE1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            MODE1_USB_POWER_REG &= MODE1_USBIO_EXIT_SLEEP_PH1;
            MODE1_CR1_REG = MODE1_backup.usbState;
            MODE1_USB_POWER_REG &= MODE1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MODE1__SIO)
        MODE1_SIO_REG = MODE1_backup.sioState;
    #endif
}


/* [] END OF FILE */
