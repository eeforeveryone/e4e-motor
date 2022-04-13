/*******************************************************************************
* File Name: encB.h  
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

#if !defined(CY_PINS_encB_ALIASES_H) /* Pins encB_ALIASES_H */
#define CY_PINS_encB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define encB_0			(encB__0__PC)
#define encB_0_PS		(encB__0__PS)
#define encB_0_PC		(encB__0__PC)
#define encB_0_DR		(encB__0__DR)
#define encB_0_SHIFT	(encB__0__SHIFT)
#define encB_0_INTR	((uint16)((uint16)0x0003u << (encB__0__SHIFT*2u)))

#define encB_INTR_ALL	 ((uint16)(encB_0_INTR))


#endif /* End Pins encB_ALIASES_H */


/* [] END OF FILE */
