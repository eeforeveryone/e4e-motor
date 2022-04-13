/*******************************************************************************
* File Name: MOT_IN2.h  
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

#if !defined(CY_PINS_MOT_IN2_ALIASES_H) /* Pins MOT_IN2_ALIASES_H */
#define CY_PINS_MOT_IN2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MOT_IN2_0			(MOT_IN2__0__PC)
#define MOT_IN2_0_PS		(MOT_IN2__0__PS)
#define MOT_IN2_0_PC		(MOT_IN2__0__PC)
#define MOT_IN2_0_DR		(MOT_IN2__0__DR)
#define MOT_IN2_0_SHIFT	(MOT_IN2__0__SHIFT)
#define MOT_IN2_0_INTR	((uint16)((uint16)0x0003u << (MOT_IN2__0__SHIFT*2u)))

#define MOT_IN2_INTR_ALL	 ((uint16)(MOT_IN2_0_INTR))


#endif /* End Pins MOT_IN2_ALIASES_H */


/* [] END OF FILE */
