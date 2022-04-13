/*******************************************************************************
* File Name: ENC_PM.c
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

#include "ENC.h"

static ENC_BACKUP_STRUCT ENC_backup;


/*******************************************************************************
* Function Name: ENC_SaveConfig
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
void ENC_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ENC_Sleep
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
void ENC_Sleep(void)
{
    if(0u != (ENC_BLOCK_CONTROL_REG & ENC_MASK))
    {
        ENC_backup.enableState = 1u;
    }
    else
    {
        ENC_backup.enableState = 0u;
    }

    ENC_Stop();
    ENC_SaveConfig();
}


/*******************************************************************************
* Function Name: ENC_RestoreConfig
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
void ENC_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ENC_Wakeup
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
void ENC_Wakeup(void)
{
    ENC_RestoreConfig();

    if(0u != ENC_backup.enableState)
    {
        ENC_Enable();
    }
}


/* [] END OF FILE */
