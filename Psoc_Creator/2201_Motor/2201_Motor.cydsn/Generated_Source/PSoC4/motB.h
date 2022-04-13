/*******************************************************************************
* File Name: motB.h  
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

#if !defined(CY_PINS_motB_H) /* Pins motB_H */
#define CY_PINS_motB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motB_aliases.h"


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
} motB_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   motB_Read(void);
void    motB_Write(uint8 value);
uint8   motB_ReadDataReg(void);
#if defined(motB__PC) || (CY_PSOC4_4200L) 
    void    motB_SetDriveMode(uint8 mode);
#endif
void    motB_SetInterruptMode(uint16 position, uint16 mode);
uint8   motB_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void motB_Sleep(void); 
void motB_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(motB__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define motB_DRIVE_MODE_BITS        (3)
    #define motB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motB_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the motB_SetDriveMode() function.
         *  @{
         */
        #define motB_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define motB_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define motB_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define motB_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define motB_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define motB_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define motB_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define motB_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define motB_MASK               motB__MASK
#define motB_SHIFT              motB__SHIFT
#define motB_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in motB_SetInterruptMode() function.
     *  @{
     */
        #define motB_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define motB_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define motB_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define motB_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(motB__SIO)
    #define motB_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(motB__PC) && (CY_PSOC4_4200L)
    #define motB_USBIO_ENABLE               ((uint32)0x80000000u)
    #define motB_USBIO_DISABLE              ((uint32)(~motB_USBIO_ENABLE))
    #define motB_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define motB_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define motB_USBIO_ENTER_SLEEP          ((uint32)((1u << motB_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << motB_USBIO_SUSPEND_DEL_SHIFT)))
    #define motB_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << motB_USBIO_SUSPEND_SHIFT)))
    #define motB_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << motB_USBIO_SUSPEND_DEL_SHIFT)))
    #define motB_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(motB__PC)
    /* Port Configuration */
    #define motB_PC                 (* (reg32 *) motB__PC)
#endif
/* Pin State */
#define motB_PS                     (* (reg32 *) motB__PS)
/* Data Register */
#define motB_DR                     (* (reg32 *) motB__DR)
/* Input Buffer Disable Override */
#define motB_INP_DIS                (* (reg32 *) motB__PC2)

/* Interrupt configuration Registers */
#define motB_INTCFG                 (* (reg32 *) motB__INTCFG)
#define motB_INTSTAT                (* (reg32 *) motB__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define motB_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(motB__SIO)
    #define motB_SIO_REG            (* (reg32 *) motB__SIO)
#endif /* (motB__SIO_CFG) */

/* USBIO registers */
#if !defined(motB__PC) && (CY_PSOC4_4200L)
    #define motB_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define motB_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define motB_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define motB_DRIVE_MODE_SHIFT       (0x00u)
#define motB_DRIVE_MODE_MASK        (0x07u << motB_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins motB_H */


/* [] END OF FILE */
