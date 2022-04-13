/*******************************************************************************
* File Name: encA.h  
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

#if !defined(CY_PINS_encA_H) /* Pins encA_H */
#define CY_PINS_encA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "encA_aliases.h"


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
} encA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   encA_Read(void);
void    encA_Write(uint8 value);
uint8   encA_ReadDataReg(void);
#if defined(encA__PC) || (CY_PSOC4_4200L) 
    void    encA_SetDriveMode(uint8 mode);
#endif
void    encA_SetInterruptMode(uint16 position, uint16 mode);
uint8   encA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void encA_Sleep(void); 
void encA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(encA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define encA_DRIVE_MODE_BITS        (3)
    #define encA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - encA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the encA_SetDriveMode() function.
         *  @{
         */
        #define encA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define encA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define encA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define encA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define encA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define encA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define encA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define encA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define encA_MASK               encA__MASK
#define encA_SHIFT              encA__SHIFT
#define encA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in encA_SetInterruptMode() function.
     *  @{
     */
        #define encA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define encA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define encA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define encA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(encA__SIO)
    #define encA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(encA__PC) && (CY_PSOC4_4200L)
    #define encA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define encA_USBIO_DISABLE              ((uint32)(~encA_USBIO_ENABLE))
    #define encA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define encA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define encA_USBIO_ENTER_SLEEP          ((uint32)((1u << encA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << encA_USBIO_SUSPEND_DEL_SHIFT)))
    #define encA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << encA_USBIO_SUSPEND_SHIFT)))
    #define encA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << encA_USBIO_SUSPEND_DEL_SHIFT)))
    #define encA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(encA__PC)
    /* Port Configuration */
    #define encA_PC                 (* (reg32 *) encA__PC)
#endif
/* Pin State */
#define encA_PS                     (* (reg32 *) encA__PS)
/* Data Register */
#define encA_DR                     (* (reg32 *) encA__DR)
/* Input Buffer Disable Override */
#define encA_INP_DIS                (* (reg32 *) encA__PC2)

/* Interrupt configuration Registers */
#define encA_INTCFG                 (* (reg32 *) encA__INTCFG)
#define encA_INTSTAT                (* (reg32 *) encA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define encA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(encA__SIO)
    #define encA_SIO_REG            (* (reg32 *) encA__SIO)
#endif /* (encA__SIO_CFG) */

/* USBIO registers */
#if !defined(encA__PC) && (CY_PSOC4_4200L)
    #define encA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define encA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define encA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define encA_DRIVE_MODE_SHIFT       (0x00u)
#define encA_DRIVE_MODE_MASK        (0x07u << encA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins encA_H */


/* [] END OF FILE */
