/*******************************************************************************
* File Name: MOT_IN2.h  
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

#if !defined(CY_PINS_MOT_IN2_H) /* Pins MOT_IN2_H */
#define CY_PINS_MOT_IN2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MOT_IN2_aliases.h"


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
} MOT_IN2_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MOT_IN2_Read(void);
void    MOT_IN2_Write(uint8 value);
uint8   MOT_IN2_ReadDataReg(void);
#if defined(MOT_IN2__PC) || (CY_PSOC4_4200L) 
    void    MOT_IN2_SetDriveMode(uint8 mode);
#endif
void    MOT_IN2_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOT_IN2_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MOT_IN2_Sleep(void); 
void MOT_IN2_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MOT_IN2__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MOT_IN2_DRIVE_MODE_BITS        (3)
    #define MOT_IN2_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MOT_IN2_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MOT_IN2_SetDriveMode() function.
         *  @{
         */
        #define MOT_IN2_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MOT_IN2_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MOT_IN2_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MOT_IN2_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MOT_IN2_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MOT_IN2_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MOT_IN2_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MOT_IN2_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MOT_IN2_MASK               MOT_IN2__MASK
#define MOT_IN2_SHIFT              MOT_IN2__SHIFT
#define MOT_IN2_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOT_IN2_SetInterruptMode() function.
     *  @{
     */
        #define MOT_IN2_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MOT_IN2_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MOT_IN2_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MOT_IN2_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MOT_IN2__SIO)
    #define MOT_IN2_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MOT_IN2__PC) && (CY_PSOC4_4200L)
    #define MOT_IN2_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MOT_IN2_USBIO_DISABLE              ((uint32)(~MOT_IN2_USBIO_ENABLE))
    #define MOT_IN2_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MOT_IN2_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MOT_IN2_USBIO_ENTER_SLEEP          ((uint32)((1u << MOT_IN2_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MOT_IN2_USBIO_SUSPEND_DEL_SHIFT)))
    #define MOT_IN2_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MOT_IN2_USBIO_SUSPEND_SHIFT)))
    #define MOT_IN2_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MOT_IN2_USBIO_SUSPEND_DEL_SHIFT)))
    #define MOT_IN2_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MOT_IN2__PC)
    /* Port Configuration */
    #define MOT_IN2_PC                 (* (reg32 *) MOT_IN2__PC)
#endif
/* Pin State */
#define MOT_IN2_PS                     (* (reg32 *) MOT_IN2__PS)
/* Data Register */
#define MOT_IN2_DR                     (* (reg32 *) MOT_IN2__DR)
/* Input Buffer Disable Override */
#define MOT_IN2_INP_DIS                (* (reg32 *) MOT_IN2__PC2)

/* Interrupt configuration Registers */
#define MOT_IN2_INTCFG                 (* (reg32 *) MOT_IN2__INTCFG)
#define MOT_IN2_INTSTAT                (* (reg32 *) MOT_IN2__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MOT_IN2_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MOT_IN2__SIO)
    #define MOT_IN2_SIO_REG            (* (reg32 *) MOT_IN2__SIO)
#endif /* (MOT_IN2__SIO_CFG) */

/* USBIO registers */
#if !defined(MOT_IN2__PC) && (CY_PSOC4_4200L)
    #define MOT_IN2_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MOT_IN2_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MOT_IN2_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MOT_IN2_DRIVE_MODE_SHIFT       (0x00u)
#define MOT_IN2_DRIVE_MODE_MASK        (0x07u << MOT_IN2_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MOT_IN2_H */


/* [] END OF FILE */
