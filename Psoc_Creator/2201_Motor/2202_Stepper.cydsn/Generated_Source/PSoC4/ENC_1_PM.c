/*******************************************************************************
* File Name: ENC_1_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ENC_1.h"

static ENC_1_BACKUP_STRUCT ENC_1_backup;


/*******************************************************************************
* Function Name: ENC_1_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ENC_1_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_Sleep(void)
{
    if(0u != (ENC_1_BLOCK_CONTROL_REG & ENC_1_MASK))
    {
        ENC_1_backup.enableState = 1u;
    }
    else
    {
        ENC_1_backup.enableState = 0u;
    }

    ENC_1_Stop();
    ENC_1_SaveConfig();
}


/*******************************************************************************
* Function Name: ENC_1_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ENC_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENC_1_Wakeup(void)
{
    ENC_1_RestoreConfig();

    if(0u != ENC_1_backup.enableState)
    {
        ENC_1_Enable();
    }
}


/* [] END OF FILE */
