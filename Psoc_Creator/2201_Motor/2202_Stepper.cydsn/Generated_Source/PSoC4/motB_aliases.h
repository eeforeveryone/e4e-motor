/*******************************************************************************
* File Name: motB.h  
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

#if !defined(CY_PINS_motB_ALIASES_H) /* Pins motB_ALIASES_H */
#define CY_PINS_motB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define motB_0			(motB__0__PC)
#define motB_0_PS		(motB__0__PS)
#define motB_0_PC		(motB__0__PC)
#define motB_0_DR		(motB__0__DR)
#define motB_0_SHIFT	(motB__0__SHIFT)
#define motB_0_INTR	((uint16)((uint16)0x0003u << (motB__0__SHIFT*2u)))

#define motB_INTR_ALL	 ((uint16)(motB_0_INTR))


#endif /* End Pins motB_ALIASES_H */


/* [] END OF FILE */
