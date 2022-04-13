/***************************************************************************//**
* \file ADC_Adc.c
* \version 7.0
*
* \brief
*   This file provides implementation for the ADC module of the ADC
*   Component.
*
* \see ADC v7.0 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2019), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/
#include <cytypes.h>
#include "CyLib.h"
#include "ADC_ISR.h"
#include "ADC_Configuration.h"
#include "ADC_Structure.h"
#include "ADC_Adc.h"
#include "ADC_Sensing.h"
#if (ADC_ENABLE == ADC_SELF_TEST_EN)
    #include "ADC_SelfTest.h"
#endif

#if (ADC_ADC_EN)

static uint8 ADC_initVar;
uint16 ADC_adcVrefMv = ADC_ADC_VREF_MV;


/*******************************************************************************
* Module local function declarations
*******************************************************************************/
/**
* \cond SECTION_ADC_INTERNAL
* \addtogroup group_adc_internal
* \{
*/

void ADC_SetModClkClockDivider(uint32 modClk);

/** \}
* \endcond */

/*******************************************************************************
* Local definition
*******************************************************************************/
#define ADC_INIT_DONE                    (1u)
#define ADC_INIT_NEEDED                  (0u)
#define ADC_CAL_WATCHDOG_CYCLES_NUM      (0x0000FFFFLu)

#if (ADC_ENABLE == ADC_ADC_STANDALONE_EN)
    /*******************************************************************************
    * Function Name: ADC_Start
    ****************************************************************************//**
    * \cond SECTION_STANDALONE_ADC
    * \brief
    *   Configures the hardware and performs calibration.
    *
    * \details
    *   Configures the hardware and performs calibration.
    * \endcond
    *
    *******************************************************************************/
    void ADC_Start(void)
    {
        ADC_ClearAdcChannels();

        if (ADC_INIT_DONE != ADC_initVar)
        {
            ADC_DsInitialize();
        }
        ADC_ConfigAdcResources();
        (void) ADC_Calibrate();
    }

    /*******************************************************************************
    * Function Name: ADC_Sleep
    ****************************************************************************//**
    * \cond SECTION_STANDALONE_ADC
    * \brief
    *  Prepares the Component for deep sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function will be used to prepare the Component to enter deep sleep.
    * \endcond
    *
    *******************************************************************************/
    void ADC_Sleep(void)
    {
    }


    /*******************************************************************************
    * Function Name: ADC_Wakeup
    ****************************************************************************//**
    * \cond SECTION_STANDALONE_ADC
    * \brief
    *  This function resumes the Component after sleep.
    *
    * \details
    *  Currently this function is empty and exists as a place for future updates,
    *  this function will be used to resume the Component after exiting deep sleep.
    * \endcond
    *
    *******************************************************************************/
    void ADC_Wakeup(void)
    {
    }
#endif  /* (ADC_ENABLE != ADC_ADC_STANDALONE_EN) */

/*******************************************************************************
* Function Name: ADC_SetNonDedicatedAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the non dedicated channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B. Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the non dedicated channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) ADC_CHAN_DISCONNECT
*         - (1) ADC_CHAN_CONNECT
*
*******************************************************************************/
void ADC_SetNonDedicatedAdcChannel(uint8 chId, uint32 state)
{
    ADC_FLASH_IO_STRUCT const *ptr2adcIO;
    uint32 newRegisterValue;
    uint8  interruptState;
    uint32 pinHSIOMShift;
    uint32 pinModeShift;
    uint32 tmpVal;

    ptr2adcIO = &ADC_adcIoList[chId];
    pinHSIOMShift = (uint32)ptr2adcIO->hsiomShift;
    pinModeShift = (uint32)ptr2adcIO->shift;

    /* Clear port connections. */
    tmpVal = CY_GET_REG32(ptr2adcIO->hsiomPtr);
    tmpVal &= ~(ADC_HSIOM_SEL_MASK << pinHSIOMShift);

    interruptState = CyEnterCriticalSection();

    switch (state)
    {
    case ADC_CHAN_CONNECT:
        /* Connect AMuxBusB to the selected port */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, (tmpVal | (ADC_HSIOM_SEL_AMUXB << pinHSIOMShift)));
        /* Update port configuration register (drive mode) to HiZ Analog */
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(ADC_GPIO_PC_MASK << pinModeShift);
        newRegisterValue |= (ADC_GPIO_PC_INPUT << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);

        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & ADC_SW_CMOD_PORT_MASK))
        {
            if (ADC_SW_CTANK_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(ADC_SW_DSI_SEL_PTR, ADC_SW_DSI_CTANK);
            }
            else if (ADC_SW_CMOD_PINSHIFT == pinModeShift)
            {
                CY_SET_REG32(ADC_SW_DSI_SEL_PTR, ADC_SW_DSI_CMOD);
            }
            else { /* No action */ }
        }
        break;

    /* Disconnection is a safe default state. Fall-through is intentional. */
    case ADC_CHAN_DISCONNECT:
    default:
        /* Disconnec AMuxBusB from the selected port */
        CY_SET_REG32(ptr2adcIO->hsiomPtr, tmpVal);

        /* Update port configuration register (drive mode) to HiZ input/output by clearing PC */
        newRegisterValue = CY_GET_REG32(ptr2adcIO->pcPtr);
        newRegisterValue &= ~(ADC_GPIO_PC_MASK << pinModeShift);
        CY_SET_REG32(ptr2adcIO->pcPtr, newRegisterValue);

        /* Cmod and Ctank are not typical GPIO, require CSD setting. */
        if (0u != ((uint32)(ptr2adcIO->hsiomPtr) & ADC_SW_CMOD_PORT_MASK))
        {
            if ((ADC_SW_CTANK_PINSHIFT == pinModeShift) ||
                (ADC_SW_CMOD_PINSHIFT == pinModeShift ))
            {
                CY_SET_REG32(ADC_SW_DSI_SEL_PTR, 0u);
            }
        }
        break;
    }

    /* Set logic 0 to port data register */
    tmpVal = CY_GET_REG32(ptr2adcIO->drPtr);
    tmpVal &= (uint32)~(uint32)((uint32)1u << ptr2adcIO->drShift);
    CY_SET_REG32(ptr2adcIO->drPtr, tmpVal);
    
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ADC_SetAdcChannel
****************************************************************************//**
*
* \brief
*   Sets the given channel to the given state.
*
* \details
*   Connects/disconnects the pin and the analog muxbus B.  Sets the drive mode
*   of the pin as well.
*
* \param chId  The ID of the channel to be set.
* \param state The state in which the channel is to be put:
*         - (0) ADC_CHAN_DISCONNECT
*         - (1) ADC_CHAN_CONNECT
*
*******************************************************************************/
void ADC_SetAdcChannel(uint8 chId, uint32 state)
{
    #if (0u != ADC_ADC_AMUXB_INPUT_EN)
        #if (ADC_ADC_MIN_CHANNELS < ADC_ADC_TOTAL_CHANNELS)
            if(ADC_ADC_SELECT_AMUXB_CH != chId)
            {
                ADC_SetNonDedicatedAdcChannel(chId, state);
            }
        #endif /* (0u != ADC_ADC_TOTAL_CHANNELS) */
    #else
        ADC_SetNonDedicatedAdcChannel(chId, state);
    #endif /* (0u != ADC_ADC_AMUXB_INPUT_EN) */
}


/*******************************************************************************
* Function Name: ADC_ConfigAdcResources
****************************************************************************//**
*
* \brief
*   Configures the CSD block to be used as an ADC.
*
* \details
*   Configures the IDACB, internal switches, REFGEN, HSCOMP, enables CSD
*   block interrupt and set interrupt vector to ADC sensing method.
*
*******************************************************************************/
void ADC_ConfigAdcResources(void)
{
    uint8  interruptState;
    uint32 newRegValue;

    /* Configure clocks */
    ADC_SetModClkClockDivider(ADC_ADC_MODCLK_DIV_DEFAULT);
    CY_SET_REG32(ADC_SENSE_PERIOD_PTR, (ADC_SENSE_DIV_DEFAULT - 1uL));

    /* Configure the IDAC */
    CY_SET_REG32(ADC_CONFIG_PTR, ADC_CONFIG_DEFAULT);
    CY_SET_REG32(ADC_CSD_IDACB_PTR, ADC_IDACB_CONFIG | ADC_dsRam.adcIdac);

    /* Configure AZ Time */
    CY_SET_REG32(ADC_SEQ_TIME_PTR, (ADC_SEQ_TIME_DEFAUL - 1uL));

    CY_SET_REG32(ADC_CSDCMP_PTR, 0uL);
    CY_SET_REG32(ADC_SW_DSI_SEL_PTR, 0uL);

    CY_SET_REG32(ADC_SENSE_DUTY_PTR, 0uL);
    CY_SET_REG32(ADC_SEQ_INIT_CNT_PTR, 1uL);
    CY_SET_REG32(ADC_SEQ_NORM_CNT_PTR, 2uL);

    /* Configure the block-level routing */
    CY_SET_REG32(ADC_SW_HS_P_SEL_PTR, ADC_SW_HSP_DEFAULT);
    CY_SET_REG32(ADC_SW_HS_N_SEL_PTR, ADC_SW_HSN_DEFAULT);
    CY_SET_REG32(ADC_SW_SHIELD_SEL_PTR, ADC_SW_SHIELD_DEFAULT);
    CY_SET_REG32(ADC_SW_CMP_P_SEL_PTR, ADC_SW_CMPP_DEFAULT);
    CY_SET_REG32(ADC_SW_CMP_N_SEL_PTR, ADC_SW_CMPN_DEFAULT);
    CY_SET_REG32(ADC_SW_FW_MOD_SEL_PTR, ADC_SW_FWMOD_DEFAULT);
    CY_SET_REG32(ADC_SW_FW_TANK_SEL_PTR, ADC_SW_FWTANK_DEFAULT);
    CY_SET_REG32(ADC_SW_REFGEN_SEL_PTR, ADC_SW_REFGEN_DEFAULT);

    interruptState = CyEnterCriticalSection();
    newRegValue = CY_GET_REG32(ADC_SW_BYP_SEL_PTR);
    newRegValue |= ADC_SW_BYP_DEFAULT;
    CY_SET_REG32(ADC_SW_BYP_SEL_PTR, newRegValue);
    CyExitCriticalSection(interruptState);

    /* Config RefGen */
    #if (ADC_CYDEV_VDDA_MV < ADC_LVTHRESH)
        /* The routing of the HS_N and AMUXBUF switches depend on RefGen */
        CY_SET_REG32(ADC_REFGEN_PTR, ADC_REFGEN_LV);
        CY_SET_REG32(ADC_SW_AMUXBUF_SEL_PTR, ADC_SW_AMUBUF_LV);
        CY_SET_REG32(ADC_AMBUF_PTR, ADC_AMBUF_LV);
    #else
        CY_SET_REG32(ADC_REFGEN_PTR, ADC_REFGEN_NORM);
        CY_SET_REG32(ADC_SW_AMUXBUF_SEL_PTR, ADC_SW_AMUBUF_NORM);
    #endif /* ADC__CYDEV_VDDA_MV < ADC_LVTHRESH */

    /* Configure HSCOMP */
    CY_SET_REG32(ADC_HSCMP_PTR, ADC_HSCMP_AZ_DEFAULT);

    /* Clear all pending interrupts of CSD block */
    CY_SET_REG32(ADC_INTR_PTR, ADC_INTR_ALL_MASK);

    /* Mask all CSD block interrupts (disable all interrupts) */
    CY_SET_REG32(ADC_INTR_MASK_PTR, ADC_INTR_MASK_CLEAR_MASK);

    /* Set the ISR vector */
    ADC_ISR_StartEx(&ADC_IntrHandler);

    /* Component is initialized */
    ADC_initVar = ADC_INIT_DONE;
}


/*******************************************************************************
* Function Name: ADC_StartAdcFSM
****************************************************************************//**
*
* \brief
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \details
*   Starts the CSD state machine with correct parameters to initialize an ADC
*   conversion.
*
* \param measureMode The FSM mode:
*        - (0) ADC_MEASMODE_OFF
*        - (1) ADC_MEASMODE_VREF
*        - (2) ADC_MEASMODE_VREFBY2
*        - (3) ADC_MEASMODE_VIN
*
*******************************************************************************/
void ADC_StartAdcFSM(uint32 measureMode)
{
    uint32 tmpStartVal;

    /* Set the mode and acquisition time */
    CY_SET_REG32(ADC_ADC_CTL_PTR, (measureMode | (ADC_ACQUISITION_BASE - 1u)));

    if(ADC_MEASMODE_VREF == measureMode)
    {
        tmpStartVal =
            ADC_FSMSETTING_AZSKIP_DEFAULT    |
            ADC_FSMSETTING_DSIIGNORE   |
            ADC_FSMSETTING_NOABORT     |
            ADC_FSMSETTING_SEQMODE     |
            ADC_FSMSETTING_START;
    }
    else if (ADC_MEASMODE_OFF == measureMode)
    {
        tmpStartVal = ADC_FSMSETTING_ABORT;
    }
    /* This setting is used for both MEASMODE_VREFBY2 and MEASMODE_VIN */
    else
    {
        tmpStartVal =
            ADC_FSMSETTING_AZSKIP_DEFAULT    |
            ADC_FSMSETTING_DSIIGNORE   |
            ADC_FSMSETTING_NOABORT     |
            ADC_FSMSETTING_SEQMODE     |
            ADC_FSMSETTING_START;
    }

    /* Enable HSComp */
    CY_SET_REG32(ADC_SEQ_START_PTR, tmpStartVal);
}

/*******************************************************************************
* Function Name: ADC_AdcCaptureResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from sensing mode, and sets it into ADC mode.
*
* \details
*   Releases CSD resources from sensing mode, and sets it into ADC mode.
*
* \return     The function returns cystatus of its operation.
*   - CYRET_LOCKED  - The sensing hardware is in-use and could not be released.
*   - CYRET_SUCCESS - Block is configured for ADC use.
*
*******************************************************************************/
cystatus ADC_AdcCaptureResources(void)
{
    cystatus tmpStatus = CYRET_SUCCESS;

    #if !(ADC_ENABLE == ADC_ADC_STANDALONE_EN)
        tmpStatus = ADC_SsReleaseResources();

        if (ADC_INIT_NEEDED == ADC_initVar)
        {
            if(CYRET_SUCCESS == tmpStatus)
            {
                ADC_ConfigAdcResources();
            }
            else
            {
                tmpStatus = CYRET_LOCKED;
            }
        }
    #else
        if (ADC_INIT_NEEDED == ADC_initVar)
        {
            ADC_ConfigAdcResources();
        }
    #endif /* !(ADC_ENABLE == ADC_ADC_STANDALONE_EN) */

    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_AdcReleaseResources
****************************************************************************//**
*
* \brief
*   Releases CSD resources from ADC mode.
*
* \details
*   Releases CSD resources from ADC mode.
*
* \return     The function returns cystatus of its operation.
*   CYRET_SUCCESS   Block resources no longer in use.
*
*******************************************************************************/
cystatus ADC_AdcReleaseResources(void)
{
    uint8  interruptState;
    uint32 newRegValue;

    if (ADC_INIT_DONE == ADC_initVar)
    {
        /* If the FSM is running, shut it down. */
        if(ADC_STATUS_IDLE != (ADC_dsRam.adcStatus
                            & ADC_STATUS_FSM_MASK))
        {
            ADC_StartAdcFSM(ADC_MEASMODE_OFF);
            ADC_SetAdcChannel((ADC_dsRam.adcStatus
                            & (uint8)(ADC_STATUS_LASTCHAN_MASK)),
                            ADC_CHAN_DISCONNECT);
            ADC_dsRam.adcStatus = ADC_STATUS_IDLE;
        }

        /* Disable the subblocks. */
        CY_SET_REG32(ADC_CSD_IDACB_PTR, 0u);
        CY_SET_REG32(ADC_REFGEN_PTR, 0u);
        CY_SET_REG32(ADC_AMBUF_PTR, 0u);
        CY_SET_REG32(ADC_HSCMP_PTR, 0u);

        /* Reset the block-level routing */
        CY_SET_REG32(ADC_SW_HS_P_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_HS_N_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_SHIELD_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_CMP_P_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_CMP_N_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_FW_MOD_SEL_PTR, 0u);
        CY_SET_REG32(ADC_SW_FW_TANK_SEL_PTR, 0u);

        interruptState = CyEnterCriticalSection();
        newRegValue = CY_GET_REG32(ADC_SW_BYP_SEL_PTR);
        newRegValue &= (uint32)(~ADC_SW_BYP_DEFAULT);
        CY_SET_REG32(ADC_SW_BYP_SEL_PTR, newRegValue);
        CyExitCriticalSection(interruptState);

         /* Disconnect all ADC channels */
        ADC_ClearAdcChannels();

        ADC_initVar = ADC_INIT_NEEDED;
    }

    return CYRET_SUCCESS;
}


/*******************************************************************************
* Function Name: ADC_StartConvert
****************************************************************************//**
*
* \brief
*  Initializes the hardware and initiates an analog-to-digital conversion on the
*  selected input channel.
*
* \details
*  Initializes the hardware and initiates an analog-to-digital conversion on the
*  selected input channel. This API only initiates a conversion and does not
*  wait for the conversion to be completed, therefore the
*  ADC_IsBusy() API must be used to check the
*  status and ensure that the conversion is complete prior to reading the result,
*  starting a new conversion with the same or a different channel, or reconfiguring
*  the hardware for different functionality.
*
* \param chId
*  The ID of the channel to be converted.
*
* \return
*  The function returns cystatus of its operation.
*    - CYRET_SUCCESS - A conversion has started.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized
*      conversion or other functionality. No new conversion is started by this API.
*    - CYRET_BAD_PARAM - An invalid channel Id. No conversion is started.
*
*******************************************************************************/
cystatus ADC_StartConvert(uint8 chId)
{
    uint32 tmpStatus = CYRET_SUCCESS;

    /* If non-standalone ADC, try to Capture resources */
    #if (ADC_ENABLE != ADC_ADC_STANDALONE_EN)
        tmpStatus = ADC_AdcCaptureResources();

        if (CYRET_SUCCESS == tmpStatus)
        {
    #else /* Otherwise, configure resources if needed. */
        if (ADC_INIT_NEEDED == ADC_initVar)
        {
            ADC_ConfigAdcResources();
        }
    #endif /* (ADC_ENABLE != ADC_ADC_STANDALONE_EN) */

    if(chId >= ADC_ADC_TOTAL_CHANNELS)
    {
        tmpStatus = CYRET_BAD_PARAM;
    }

    if (CYRET_SUCCESS == tmpStatus)
    {
        if(ADC_STATUS_IDLE != (ADC_dsRam.adcStatus & ADC_STATUS_FSM_MASK))
        {
            tmpStatus = CYRET_LOCKED;
        }

        if(CYRET_SUCCESS == tmpStatus)
        {
            #if(ADC_ADC_ANALOG_STARTUP_DELAY_US > 0uL)
                CyDelayUs(ADC_ADC_ANALOG_STARTUP_DELAY_US);
            #endif /* (ADC_ADC_ANALOG_STARTUP_DELAY_US > 0uL) */

            /* Set Component Status */
            ADC_dsRam.adcStatus = (ADC_STATUS_CONVERTING | chId);

            /* Configure a desired channel if needed */
            if (chId != ADC_dsRam.adcActiveCh)
            {
                if (ADC_NO_CHANNEL != ADC_dsRam.adcActiveCh)
                {
                    /* Disconnect existing channel */
                    ADC_SetAdcChannel(ADC_dsRam.adcActiveCh, ADC_CHAN_DISCONNECT);
                }
                /* Connect desired input */
                ADC_SetAdcChannel(chId, ADC_CHAN_CONNECT);
                ADC_dsRam.adcActiveCh = chId;
            }

            /* Un-mask ADC_RES interrupt (enable interrupt) */
            CY_SET_REG32(ADC_INTR_MASK_PTR, ADC_INTR_MASK_ADC_RES_MASK);
            ADC_StartAdcFSM(ADC_MEASMODE_VIN);
        }
    }

    #if (ADC_ENABLE != ADC_ADC_STANDALONE_EN)
        }
    #endif /* (ADC_ENABLE != ADC_ADC_STANDALONE_EN) */

    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_IsBusy
****************************************************************************//**
*
* \brief
*   The function returns the status of the ADC's operation.
*
* \details
*   The function returns the status of the ADC's operation. A new conversion or
*   calibration must not be started unless the ADC is in the IDLE state.
*
* \return
*  The function returns the status of the ADC's operation.
*    - ADC_STATUS_IDLE - The ADC is not busy,
*       a new conversion can be initiated.
*    - ADC_STATUS_CONVERTING - A previously
*       initiated conversion is in progress.
*    - ADC_STATUS_CALIBPH1 - The ADC is in the
*      first phase (of 3) of calibration.
*    - ADC_STATUS_CALIBPH2 - The ADC is in the
*      second phase (of 3) of calibration.
*    - ADC_STATUS_CALIBPH3 - The ADC is in the
*      third phase (of 3) of calibration.
*    - ADC_STATUS_OVERFLOW - The most recent
*      measurement caused an overflow. The root cause of the overflow may be
*      the previous calibration values being invalid or the VDDA setting in cydwr
*      and hardware do not match. Perform re-calibration or set the
*      appropriate VDDA value in cydwr to avoid this error condition.
*
*******************************************************************************/
uint8 ADC_IsBusy(void)
{
    uint8 tmpStatus;

    if (0u != (ADC_ADC_RES_REG & ADC_ADC_RES_OVERFLOW_MASK))
    {
        tmpStatus = ADC_STATUS_OVERFLOW;
    }
    else
    {
        tmpStatus = (uint8)((*(volatile uint8 *)&ADC_dsRam.adcStatus) & ADC_STATUS_FSM_MASK);
    }

    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_ReadResult_mVolts
****************************************************************************//**
*
* \brief
*  This is a blocking API. It initiates a conversion, waits for completion and
*  returns the result.
*
* \details
*  This is a blocking API. Internally, it starts a conversion using
*  ADC_StartConvert(), checks the status using
*  ADC_IsBusy(), waits until the conversion is
*  completed and returns the result.
*
* \param chId
*  The ID of the channel to be measured
*
* \return
*  The function returns voltage in millivolts or
*  ADC_VALUE_BAD_RESULT if:
*   - chId is invalid
*   - The ADC conversion is not started
*   - The ADC conversion watch-dog triggered.
*
*******************************************************************************/
uint16 ADC_ReadResult_mVolts(uint8 chId)
{
    cystatus convertStatus;
    uint16 tmpValue;
    uint32 watchdogAdcCounter;

    convertStatus = ADC_StartConvert(chId);
    if (CYRET_SUCCESS == convertStatus)
    {
        /* Initialize Watchdog Counter with time interval which is enough to ADC conversion is completed */
        watchdogAdcCounter = ADC_CAL_WATCHDOG_CYCLES_NUM;
        while ((ADC_IsBusy() != ADC_STATUS_IDLE) &&
               (0u != watchdogAdcCounter))
        {
            /* Wait until conversion complete and decrement Watchdog Counter to prevent unending loop */
            watchdogAdcCounter--;
        }
        if (0u != watchdogAdcCounter)
        {
            tmpValue = ADC_GetResult_mVolts(chId);
        }
        else
        {
            tmpValue = (uint16) ADC_VALUE_BAD_RESULT;
        }
    }
    else
    {
        tmpValue = (uint16) ADC_VALUE_BAD_RESULT;
    }

    return tmpValue;
}


/*******************************************************************************
* Function Name: ADC_GetResult_mVolts
****************************************************************************//**
*
* \brief
*  This API does not perform an ADC conversion and returns the last valid result
*  for the specified channel.
*
* \details
*  Returns the last valid result from the data structure for the specified channel.
*  This function can be used to read a previous result of any channel even if the
*  ADC is busy or a conversion is in progress. However, it is highly recommended
*  not to use this function with a channel that is in an active conversion.
*
* \param chId
*  The ID of the channel to be measured
*
* \return
*  The function returns a voltage in millivolts or
*  ADC_VALUE_BAD_CHAN_ID if chId is invalid.
*
*******************************************************************************/
uint16 ADC_GetResult_mVolts(uint8 chId)
{
    uint32 tmpRetVal = ADC_VALUE_BAD_CHAN_ID;

    if(chId < ADC_ADC_TOTAL_CHANNELS)
    {
        tmpRetVal = ADC_dsRam.adcResult[chId];
    }
    return (uint16)tmpRetVal;
}


/*******************************************************************************
* Function Name: ADC_Calibrate
****************************************************************************//**
*
* \brief
*  Performs calibration of the ADC module.
*
* \details
*  Performs calibration for the ADC to identify the appropriate hardware configuration
*  to produce accurate results. It is recommended to run the calibration
*  periodically (for example every 10 seconds) for accuracy and compensations.
*
* \return
*  The function returns cystatus of its operation.
*    - CYRET_SUCCESS - The block is configured for the ADC use.
*    - CYRET_LOCKED - The hardware is already in-use by a previously initialized
*      conversion or other functionality. No new conversion is started by this API.
*
*******************************************************************************/
cystatus ADC_Calibrate(void)
{
    uint32 tmpStatus;
    uint32 watchdogAdcCounter;
    uint32 tmpVrefCal;

    tmpStatus = ADC_AdcCaptureResources();

    if(ADC_STATUS_IDLE != (ADC_dsRam.adcStatus
        & ADC_STATUS_FSM_MASK))
    {
        tmpStatus = CYRET_LOCKED;
    }

    if (CYRET_SUCCESS == tmpStatus)
    {
        #if(ADC_ADC_ANALOG_STARTUP_DELAY_US > 0uL)
            CyDelayUs(ADC_ADC_ANALOG_STARTUP_DELAY_US);
        #endif /* (ADC_ADC_ANALOG_STARTUP_DELAY_US > 0uL) */

        /* Disconnect a channel if connected */
        if (ADC_NO_CHANNEL != ADC_dsRam.adcActiveCh)
        {
            ADC_SetAdcChannel(ADC_dsRam.adcActiveCh, ADC_CHAN_DISCONNECT);
            ADC_dsRam.adcActiveCh = ADC_NO_CHANNEL;
        }

        /* Get Vref trim-value */
        tmpVrefCal = (uint32)CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM1) |
            (((uint32)CY_GET_REG8(CYREG_SFLASH_CSDV2_CSD0_ADC_TRIM2)) << 8u);

        /* Update nominal Vref to real Vref */
        tmpVrefCal *= ADC_ADC_VREF_MV;
        tmpVrefCal /= ADC_VREFCALIB_BASE;

        ADC_adcVrefMv = (uint16)tmpVrefCal;

        ADC_dsRam.adcIdac = (uint8)ADC_ADC_IDAC_DEFAULT;
        CY_SET_REG32(ADC_CSD_IDACB_PTR, ADC_IDACB_CONFIG |
                                                     ADC_dsRam.adcIdac);

        ADC_dsRam.adcStatus = (ADC_STATUS_CALIBPH1);

        /* Un-mask ADC_RES interrupt (enable interrupt) */
        CY_SET_REG32(ADC_INTR_MASK_PTR, ADC_INTR_MASK_ADC_RES_MASK);
        ADC_StartAdcFSM(ADC_MEASMODE_VREF);

        /* Global CRC update */
        #if (ADC_ENABLE == ADC_SELF_TEST_EN)
            #if (ADC_ENABLE ==ADC_TST_GLOBAL_CRC_EN)
                ADC_DsUpdateGlobalCrc();
            #endif /* (ADC_ENABLE == ADC_TST_GLOBAL_CRC_EN) */
        #endif /* (ADC_ENABLE == ADC_SELF_TEST_EN) */

        /* Initialize Watchdog Counter with time interval which is enough to ADC calibration is completed */
        watchdogAdcCounter = ADC_CAL_WATCHDOG_CYCLES_NUM;
        while (((*(volatile uint8 *)&ADC_dsRam.adcStatus & ADC_STATUS_FSM_MASK)
                != 0u) &&  (0u != watchdogAdcCounter))
        {
            /* Wait until scan complete and decrement Watchdog Counter to prevent unending loop */
            watchdogAdcCounter--;
        }
    }

    return tmpStatus;
}


/*******************************************************************************
* Function Name: ADC_Initialize
****************************************************************************//**
*
* \brief
*   Configures the hardware to ADC mode and begins a calibration.
*
* \details
*   Configures the hardware to ADC mode and begins a calibration.
*
*******************************************************************************/
void ADC_Initialize(void)
{
    ADC_ConfigAdcResources();
    (void)ADC_Calibrate();
}


/*******************************************************************************
* Function Name: ADC_Stop
****************************************************************************//**
*
* \brief
*   Disables the hardware sub-blocks that are in use while in the ADC mode,
*   and frees the routing.
*
* \details
*   This function stops the Component operation. No ADC conversion can be
*   initiated when the Component is stopped. Once stopped, the hardware block
*   may be reconfigured by the application program for any other special usage.
*   The ADC operation can be resumed by calling the
*   ADC_Resume() function or the Component can
*   be reset by calling the ADC_Start() function.
*   This function is called when no ADC conversion is in progress.
*
*******************************************************************************/
void ADC_Stop(void)
{
    #if (ADC_ENABLE != ADC_ADC_STANDALONE_EN)
        (void)ADC_AdcReleaseResources();
    #endif /* (ADC_ENABLE != ADC_ADC_STANDALONE_EN) */
    ADC_initVar = ADC_INIT_NEEDED;
}


/*******************************************************************************
* Function Name: ADC_Resume
****************************************************************************//**
*
* \brief
*   Resumes the ADC operation after a stop call.
*
* \details
*   Resumes the ADC operation if the operation is stopped
*   previously by the ADC_Stop() API.
*
*******************************************************************************/
void ADC_Resume(void)
{
    ADC_Initialize();
}


/*******************************************************************************
* Function Name: ADC_ClearAdcChannels
****************************************************************************//**
*
* \brief
*  Resets all the ADC channels to disconnected state.
*
* \details
*   The function goes through all the ADC channels and disconnects the pin
*   and the analog muxbus B.  Sets the drive mode of the pin as well.
*
*******************************************************************************/
void ADC_ClearAdcChannels(void)
{
    uint32 chId;

    for (chId = 0u; chId < ADC_ADC_TOTAL_CHANNELS; chId++)
    {
        ADC_SetAdcChannel((uint8)chId, ADC_CHAN_DISCONNECT);
    }
    ADC_dsRam.adcActiveCh = ADC_NO_CHANNEL;
}

/*******************************************************************************
* Function Name: ADC_SetModClkClockDivider
****************************************************************************//**
*
* \brief
*   Sets the divider values for the modulator clock and then starts
*   the modulator clock.
*
* \details
*   It is not recommended to call this function directly by the application layer.
*   It is used by initialization to enable the clocks.
*
* \param
*   modClk The divider value for the modulator clock.
*
*******************************************************************************/
void ADC_SetModClkClockDivider(uint32 modClk)
{
    /* Stop modulator clock   */
    CY_SET_REG32(ADC_MODCLK_CMD_PTR,
                 ((uint32)ADC_ModClk__DIV_ID <<
                 ADC_MODCLK_CMD_DIV_SHIFT)|
                 ((uint32)ADC_MODCLK_CMD_DISABLE_MASK));

    /*
     * Set divider value for modClk.
     * 1u is subtracted from modClk because Divider register value 0 corresponds
     * to dividing by 1.
     */
    CY_SET_REG32(ADC_MODCLK_DIV_PTR, ((modClk - 1u) << 8u));

    /* Check whether previous modulator clock start command has finished. */
    while(0u != (CY_GET_REG32(ADC_MODCLK_CMD_PTR) & ADC_MODCLK_CMD_ENABLE_MASK))
    {
        /* Wait until previous modulator clock start command has finished. */
    }

    /* Start modulator clock, aligned to HFCLK */
    CY_SET_REG32(ADC_MODCLK_CMD_PTR,
                 (uint32)(((uint32)ADC_ModClk__DIV_ID << ADC_MODCLK_CMD_DIV_SHIFT) |
                  ((uint32)ADC_ModClk__PA_DIV_ID << ADC_MODCLK_CMD_PA_DIV_SHIFT) |
                  ADC_MODCLK_CMD_ENABLE_MASK));
}

#endif /* #if ADC_ADC_EN */


/* [] END OF FILE */
