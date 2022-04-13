/*******************************************************************************
* File Name: MODE1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MODE1_H) /* Pins MODE1_H */
#define CY_PINS_MODE1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MODE1_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} MODE1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MODE1_Read(void);
void    MODE1_Write(uint8 value);
uint8   MODE1_ReadDataReg(void);
#if defined(MODE1__PC) || (CY_PSOC4_4200L) 
    void    MODE1_SetDriveMode(uint8 mode);
#endif
void    MODE1_SetInterruptMode(uint16 position, uint16 mode);
uint8   MODE1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MODE1_Sleep(void); 
void MODE1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MODE1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MODE1_DRIVE_MODE_BITS        (3)
    #define MODE1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MODE1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MODE1_SetDriveMode() function.
         *  @{
         */
        #define MODE1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MODE1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MODE1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MODE1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MODE1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MODE1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MODE1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MODE1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MODE1_MASK               MODE1__MASK
#define MODE1_SHIFT              MODE1__SHIFT
#define MODE1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MODE1_SetInterruptMode() function.
     *  @{
     */
        #define MODE1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MODE1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MODE1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MODE1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MODE1__SIO)
    #define MODE1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MODE1__PC) && (CY_PSOC4_4200L)
    #define MODE1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MODE1_USBIO_DISABLE              ((uint32)(~MODE1_USBIO_ENABLE))
    #define MODE1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MODE1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MODE1_USBIO_ENTER_SLEEP          ((uint32)((1u << MODE1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MODE1_USBIO_SUSPEND_DEL_SHIFT)))
    #define MODE1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MODE1_USBIO_SUSPEND_SHIFT)))
    #define MODE1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MODE1_USBIO_SUSPEND_DEL_SHIFT)))
    #define MODE1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MODE1__PC)
    /* Port Configuration */
    #define MODE1_PC                 (* (reg32 *) MODE1__PC)
#endif
/* Pin State */
#define MODE1_PS                     (* (reg32 *) MODE1__PS)
/* Data Register */
#define MODE1_DR                     (* (reg32 *) MODE1__DR)
/* Input Buffer Disable Override */
#define MODE1_INP_DIS                (* (reg32 *) MODE1__PC2)

/* Interrupt configuration Registers */
#define MODE1_INTCFG                 (* (reg32 *) MODE1__INTCFG)
#define MODE1_INTSTAT                (* (reg32 *) MODE1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MODE1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MODE1__SIO)
    #define MODE1_SIO_REG            (* (reg32 *) MODE1__SIO)
#endif /* (MODE1__SIO_CFG) */

/* USBIO registers */
#if !defined(MODE1__PC) && (CY_PSOC4_4200L)
    #define MODE1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MODE1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MODE1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MODE1_DRIVE_MODE_SHIFT       (0x00u)
#define MODE1_DRIVE_MODE_MASK        (0x07u << MODE1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MODE1_H */


/* [] END OF FILE */
