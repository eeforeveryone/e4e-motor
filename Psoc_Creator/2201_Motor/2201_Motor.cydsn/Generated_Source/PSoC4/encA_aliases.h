/*******************************************************************************
* File Name: encA.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_encA_ALIASES_H) /* Pins encA_ALIASES_H */
#define CY_PINS_encA_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define encA_0			(encA__0__PC)
#define encA_0_PS		(encA__0__PS)
#define encA_0_PC		(encA__0__PC)
#define encA_0_DR		(encA__0__DR)
#define encA_0_SHIFT	(encA__0__SHIFT)
#define encA_0_INTR	((uint16)((uint16)0x0003u << (encA__0__SHIFT*2u)))

#define encA_INTR_ALL	 ((uint16)(encA_0_INTR))


#endif /* End Pins encA_ALIASES_H */


/* [] END OF FILE */
