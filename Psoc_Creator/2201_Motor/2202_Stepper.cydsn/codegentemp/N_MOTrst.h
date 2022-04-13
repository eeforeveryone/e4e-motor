/*******************************************************************************
* File Name: N_MOTrst.h  
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

#if !defined(CY_PINS_N_MOTrst_H) /* Pins N_MOTrst_H */
#define CY_PINS_N_MOTrst_H

#include "cytypes.h"
#include "cyfitter.h"
#include "N_MOTrst_aliases.h"


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
} N_MOTrst_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   N_MOTrst_Read(void);
void    N_MOTrst_Write(uint8 value);
uint8   N_MOTrst_ReadDataReg(void);
#if defined(N_MOTrst__PC) || (CY_PSOC4_4200L) 
    void    N_MOTrst_SetDriveMode(uint8 mode);
#endif
void    N_MOTrst_SetInterruptMode(uint16 position, uint16 mode);
uint8   N_MOTrst_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void N_MOTrst_Sleep(void); 
void N_MOTrst_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(N_MOTrst__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define N_MOTrst_DRIVE_MODE_BITS        (3)
    #define N_MOTrst_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - N_MOTrst_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the N_MOTrst_SetDriveMode() function.
         *  @{
         */
        #define N_MOTrst_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define N_MOTrst_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define N_MOTrst_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define N_MOTrst_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define N_MOTrst_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define N_MOTrst_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define N_MOTrst_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define N_MOTrst_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define N_MOTrst_MASK               N_MOTrst__MASK
#define N_MOTrst_SHIFT              N_MOTrst__SHIFT
#define N_MOTrst_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in N_MOTrst_SetInterruptMode() function.
     *  @{
     */
        #define N_MOTrst_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define N_MOTrst_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define N_MOTrst_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define N_MOTrst_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(N_MOTrst__SIO)
    #define N_MOTrst_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(N_MOTrst__PC) && (CY_PSOC4_4200L)
    #define N_MOTrst_USBIO_ENABLE               ((uint32)0x80000000u)
    #define N_MOTrst_USBIO_DISABLE              ((uint32)(~N_MOTrst_USBIO_ENABLE))
    #define N_MOTrst_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define N_MOTrst_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define N_MOTrst_USBIO_ENTER_SLEEP          ((uint32)((1u << N_MOTrst_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << N_MOTrst_USBIO_SUSPEND_DEL_SHIFT)))
    #define N_MOTrst_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << N_MOTrst_USBIO_SUSPEND_SHIFT)))
    #define N_MOTrst_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << N_MOTrst_USBIO_SUSPEND_DEL_SHIFT)))
    #define N_MOTrst_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(N_MOTrst__PC)
    /* Port Configuration */
    #define N_MOTrst_PC                 (* (reg32 *) N_MOTrst__PC)
#endif
/* Pin State */
#define N_MOTrst_PS                     (* (reg32 *) N_MOTrst__PS)
/* Data Register */
#define N_MOTrst_DR                     (* (reg32 *) N_MOTrst__DR)
/* Input Buffer Disable Override */
#define N_MOTrst_INP_DIS                (* (reg32 *) N_MOTrst__PC2)

/* Interrupt configuration Registers */
#define N_MOTrst_INTCFG                 (* (reg32 *) N_MOTrst__INTCFG)
#define N_MOTrst_INTSTAT                (* (reg32 *) N_MOTrst__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define N_MOTrst_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(N_MOTrst__SIO)
    #define N_MOTrst_SIO_REG            (* (reg32 *) N_MOTrst__SIO)
#endif /* (N_MOTrst__SIO_CFG) */

/* USBIO registers */
#if !defined(N_MOTrst__PC) && (CY_PSOC4_4200L)
    #define N_MOTrst_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define N_MOTrst_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define N_MOTrst_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define N_MOTrst_DRIVE_MODE_SHIFT       (0x00u)
#define N_MOTrst_DRIVE_MODE_MASK        (0x07u << N_MOTrst_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins N_MOTrst_H */


/* [] END OF FILE */
