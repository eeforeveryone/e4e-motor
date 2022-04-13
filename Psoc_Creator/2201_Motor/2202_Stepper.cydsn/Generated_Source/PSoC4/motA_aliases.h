/*******************************************************************************
* File Name: motA.h  
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

#if !defined(CY_PINS_motA_ALIASES_H) /* Pins motA_ALIASES_H */
#define CY_PINS_motA_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define motA_0			(motA__0__PC)
#define motA_0_PS		(motA__0__PS)
#define motA_0_PC		(motA__0__PC)
#define motA_0_DR		(motA__0__DR)
#define motA_0_SHIFT	(motA__0__SHIFT)
#define motA_0_INTR	((uint16)((uint16)0x0003u << (motA__0__SHIFT*2u)))

#define motA_INTR_ALL	 ((uint16)(motA_0_INTR))


#endif /* End Pins motA_ALIASES_H */


/* [] END OF FILE */
