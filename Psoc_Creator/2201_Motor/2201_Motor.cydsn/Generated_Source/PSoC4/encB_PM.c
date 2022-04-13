/*******************************************************************************
* File Name: encB.c  
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
#include "encB.h"

static encB_BACKUP_STRUCT  encB_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: encB_Sleep
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
*  \snippet encB_SUT.c usage_encB_Sleep_Wakeup
*******************************************************************************/
void encB_Sleep(void)
{
    #if defined(encB__PC)
        encB_backup.pcState = encB_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            encB_backup.usbState = encB_CR1_REG;
            encB_USB_POWER_REG |= encB_USBIO_ENTER_SLEEP;
            encB_CR1_REG &= encB_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(encB__SIO)
        encB_backup.sioState = encB_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        encB_SIO_REG &= (uint32)(~encB_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: encB_Wakeup
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
*  Refer to encB_Sleep() for an example usage.
*******************************************************************************/
void encB_Wakeup(void)
{
    #if defined(encB__PC)
        encB_PC = encB_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            encB_USB_POWER_REG &= encB_USBIO_EXIT_SLEEP_PH1;
            encB_CR1_REG = encB_backup.usbState;
            encB_USB_POWER_REG &= encB_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(encB__SIO)
        encB_SIO_REG = encB_backup.sioState;
    #endif
}


/* [] END OF FILE */
