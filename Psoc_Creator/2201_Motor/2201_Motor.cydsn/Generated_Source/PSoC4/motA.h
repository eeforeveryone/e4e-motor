/*******************************************************************************
* File Name: motA.h  
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

#if !defined(CY_PINS_motA_H) /* Pins motA_H */
#define CY_PINS_motA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motA_aliases.h"


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
} motA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   motA_Read(void);
void    motA_Write(uint8 value);
uint8   motA_ReadDataReg(void);
#if defined(motA__PC) || (CY_PSOC4_4200L) 
    void    motA_SetDriveMode(uint8 mode);
#endif
void    motA_SetInterruptMode(uint16 position, uint16 mode);
uint8   motA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void motA_Sleep(void); 
void motA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(motA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define motA_DRIVE_MODE_BITS        (3)
    #define motA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the motA_SetDriveMode() function.
         *  @{
         */
        #define motA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define motA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define motA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define motA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define motA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define motA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define motA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define motA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define motA_MASK               motA__MASK
#define motA_SHIFT              motA__SHIFT
#define motA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in motA_SetInterruptMode() function.
     *  @{
     */
        #define motA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define motA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define motA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define motA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(motA__SIO)
    #define motA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(motA__PC) && (CY_PSOC4_4200L)
    #define motA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define motA_USBIO_DISABLE              ((uint32)(~motA_USBIO_ENABLE))
    #define motA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define motA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define motA_USBIO_ENTER_SLEEP          ((uint32)((1u << motA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << motA_USBIO_SUSPEND_DEL_SHIFT)))
    #define motA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << motA_USBIO_SUSPEND_SHIFT)))
    #define motA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << motA_USBIO_SUSPEND_DEL_SHIFT)))
    #define motA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(motA__PC)
    /* Port Configuration */
    #define motA_PC                 (* (reg32 *) motA__PC)
#endif
/* Pin State */
#define motA_PS                     (* (reg32 *) motA__PS)
/* Data Register */
#define motA_DR                     (* (reg32 *) motA__DR)
/* Input Buffer Disable Override */
#define motA_INP_DIS                (* (reg32 *) motA__PC2)

/* Interrupt configuration Registers */
#define motA_INTCFG                 (* (reg32 *) motA__INTCFG)
#define motA_INTSTAT                (* (reg32 *) motA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define motA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(motA__SIO)
    #define motA_SIO_REG            (* (reg32 *) motA__SIO)
#endif /* (motA__SIO_CFG) */

/* USBIO registers */
#if !defined(motA__PC) && (CY_PSOC4_4200L)
    #define motA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define motA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define motA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define motA_DRIVE_MODE_SHIFT       (0x00u)
#define motA_DRIVE_MODE_MASK        (0x07u << motA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins motA_H */


/* [] END OF FILE */
