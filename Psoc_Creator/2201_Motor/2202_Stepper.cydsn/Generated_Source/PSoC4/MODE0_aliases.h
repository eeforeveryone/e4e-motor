/*******************************************************************************
* File Name: MODE0.h  
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

#if !defined(CY_PINS_MODE0_ALIASES_H) /* Pins MODE0_ALIASES_H */
#define CY_PINS_MODE0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MODE0_0			(MODE0__0__PC)
#define MODE0_0_PS		(MODE0__0__PS)
#define MODE0_0_PC		(MODE0__0__PC)
#define MODE0_0_DR		(MODE0__0__DR)
#define MODE0_0_SHIFT	(MODE0__0__SHIFT)
#define MODE0_0_INTR	((uint16)((uint16)0x0003u << (MODE0__0__SHIFT*2u)))

#define MODE0_INTR_ALL	 ((uint16)(MODE0_0_INTR))


#endif /* End Pins MODE0_ALIASES_H */


/* [] END OF FILE */
