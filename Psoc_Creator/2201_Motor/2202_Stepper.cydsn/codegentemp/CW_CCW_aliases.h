/*******************************************************************************
* File Name: CW_CCW.h  
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

#if !defined(CY_PINS_CW_CCW_ALIASES_H) /* Pins CW_CCW_ALIASES_H */
#define CY_PINS_CW_CCW_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CW_CCW_0			(CW_CCW__0__PC)
#define CW_CCW_0_PS		(CW_CCW__0__PS)
#define CW_CCW_0_PC		(CW_CCW__0__PC)
#define CW_CCW_0_DR		(CW_CCW__0__DR)
#define CW_CCW_0_SHIFT	(CW_CCW__0__SHIFT)
#define CW_CCW_0_INTR	((uint16)((uint16)0x0003u << (CW_CCW__0__SHIFT*2u)))

#define CW_CCW_INTR_ALL	 ((uint16)(CW_CCW_0_INTR))


#endif /* End Pins CW_CCW_ALIASES_H */


/* [] END OF FILE */
