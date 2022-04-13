/*******************************************************************************
* \file ADC_Configuration.h
* \version 7.0
*
* \brief
*   This file provides the customizer parameters definitions.
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

#if !defined(CY_SENSE_ADC_CONFIGURATION_H)
#define CY_SENSE_ADC_CONFIGURATION_H

#include <cytypes.h>
#include <cyfitter.h>

/*******************************************************************************
* Customizer-generated defines
*******************************************************************************/
#define ADC_ENABLE                             (1u)
#define ADC_DISABLE                            (0u)

#define ADC_THIRD_GENERATION_BLOCK             (1u)
#define ADC_FOURTH_GENERATION_BLOCK            (2u)

#define ADC_GENERATION_BLOCK_VERSION           (2u)

/*******************************************************************************
* HW IP block global defines
*******************************************************************************/

#if (ADC_GENERATION_BLOCK_VERSION == ADC_THIRD_GENERATION_BLOCK)
    #define ADC_CSDV1                          (ADC_ENABLE)

    #ifdef CYIPBLOCK_m0s8csd_VERSION
        #if (0u == CYIPBLOCK_m0s8csd_VERSION)
            #define ADC_CSDV1_VER1             (ADC_ENABLE)
            #define ADC_CSDV1_VER2             (ADC_DISABLE)
        #else
            #define ADC_CSDV1_VER1             (ADC_DISABLE)
            #define ADC_CSDV1_VER2             (ADC_ENABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define ADC_CSDV1                          (ADC_DISABLE)
    #define ADC_CSDV1_VER1                     (ADC_DISABLE)
    #define ADC_CSDV1_VER2                     (ADC_DISABLE)
#endif

#if (ADC_GENERATION_BLOCK_VERSION == ADC_FOURTH_GENERATION_BLOCK)
    #define ADC_CSDV2                          (ADC_ENABLE)

    #ifdef CYIPBLOCK_m0s8csdv2_VERSION
        #if (1u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define ADC_CSDV2_VER1             (ADC_ENABLE)
        #else
            #define ADC_CSDV2_VER1             (ADC_DISABLE)
        #endif
        #if (2u == CYIPBLOCK_m0s8csdv2_VERSION)
            #define ADC_CSDV2_VER2             (ADC_ENABLE)
        #else
            #define ADC_CSDV2_VER2             (ADC_DISABLE)
        #endif
    #else
        #error "HW IP block version is not specified"
    #endif
#else
    #define ADC_CSDV2                          (ADC_DISABLE)
    #define ADC_CSDV2_VER1                     (ADC_DISABLE)
    #define ADC_CSDV2_VER2                     (ADC_DISABLE)
#endif

/*******************************************************************************
* Project-global defines
*******************************************************************************/

#define ADC_2000_MV                            (2000u)

#ifdef CYDEV_VDDA_MV
    #define ADC_CYDEV_VDDA_MV                  (CYDEV_VDDA_MV)
#else
    #ifdef CYDEV_VDD_MV
        #define ADC_CYDEV_VDDA_MV              (CYDEV_VDD_MV)
    #endif
#endif

#define ADC_BAD_CONVERSIONS_NUM                (1u)
#define ADC_RESAMPLING_CYCLES_MAX_NUMBER       (1u)


/*******************************************************************************
* Enabled Scan Methods
*******************************************************************************/
#define ADC_CSD_EN                             (0u)
#define ADC_CSX_EN                             (0u)
#define ADC_ISX_EN                             (0u)
#define ADC_CSD_CSX_EN                         (ADC_CSD_EN && ADC_CSX_EN)

#define ADC_MANY_SENSE_MODES_EN                ((ADC_CSD_EN && ADC_CSX_EN) || \
                                                             (ADC_CSD_EN && ADC_ISX_EN) || \
                                                             (ADC_CSX_EN && ADC_ISX_EN) || \
                                                             (ADC_SELF_TEST_EN))

#define ADC_MANY_WIDGET_METHODS_EN             ((ADC_CSD_EN && ADC_CSX_EN) || \
                                                             (ADC_CSD_EN && ADC_ISX_EN) || \
                                                             (ADC_CSX_EN && ADC_ISX_EN))

#define ADC_CSD2X_EN                           (0u)
#define ADC_CSX2X_EN                           (0u)

/*******************************************************************************
* Definitions for number of widgets and sensors
*******************************************************************************/
#define ADC_TOTAL_WIDGETS                      (0u)
#define ADC_TOTAL_CSD_WIDGETS                  (0u)
#define ADC_TOTAL_CSD_SENSORS                  (0u)
#define ADC_TOTAL_CSX_WIDGETS                  (0u)
#define ADC_TOTAL_ISX_WIDGETS                  (0u)
#define ADC_TOTAL_CSX_NODES                    (0u)
#define ADC_TOTAL_ISX_NODES                    (0u)

/*******************************************************************************
* Total number of CSD sensors + CSX nodes
*******************************************************************************/
#define ADC_TOTAL_SENSORS            (ADC_TOTAL_CSD_SENSORS + \
                                                   ADC_TOTAL_CSX_NODES+ \
                                                   ADC_TOTAL_ISX_NODES)

/*******************************************************************************
* Total number of scan slots (used only when dual-channel scan is enabled)
*******************************************************************************/
#define ADC_TOTAL_SCAN_SLOTS         (0u)

/*******************************************************************************
* Defines widget IDs
*******************************************************************************/

/*******************************************************************************
* Defines sensor IDs
*******************************************************************************/


/*******************************************************************************
* Defines ADC channel IDs
*******************************************************************************/
#define ADC_CHANNEL_0                           (0u)
#define ADC_CHANNEL_1                           (1u)
#define ADC_CHANNEL_2                           (2u)
#define ADC_CHANNEL_3                           (3u)


/*******************************************************************************
* Enabled widget types
*******************************************************************************/
#define ADC_BUTTON_WIDGET_EN         (0u)
#define ADC_SLIDER_WIDGET_EN         (0u)
#define ADC_MATRIX_WIDGET_EN         (0u)
#define ADC_PROXIMITY_WIDGET_EN      (0u)
#define ADC_TOUCHPAD_WIDGET_EN       (0u)
#define ADC_ENCODERDIAL_WIDGET_EN    (0u)

#define ADC_CSD_MATRIX_WIDGET_EN     (0u)
#define ADC_CSD_TOUCHPAD_WIDGET_EN   (0u)

#define ADC_CSX_MATRIX_WIDGET_EN     (0u)
#define ADC_CSX_TOUCHPAD_WIDGET_EN   (0u)

/*******************************************************************************
* Centroid APIs
*******************************************************************************/
#define ADC_CENTROID_EN              (0u)
#define ADC_TOTAL_DIPLEXED_SLIDERS   (0u)
#define ADC_TOTAL_LINEAR_SLIDERS     (0u)
#define ADC_TOTAL_RADIAL_SLIDERS     (0u)
#define ADC_TOTAL_TOUCHPADS          (0u)
#define ADC_MAX_CENTROID_LENGTH      (0u)
#define ADC_SLIDER_MULT_METHOD       (0u)
#define ADC_TOUCHPAD_MULT_METHOD     (0u)

/*******************************************************************************
* Enabled sensor types
*******************************************************************************/
#define ADC_REGULAR_SENSOR_EN        (0u)
#define ADC_PROXIMITY_SENSOR_EN      (0u)

/*******************************************************************************
* Sensor ganging
*******************************************************************************/
#define ADC_GANGED_SNS_EN            (0u)
#define ADC_CSD_GANGED_SNS_EN        (0u)
#define ADC_CSX_GANGED_SNS_EN        (0u)

/*******************************************************************************
* Max number of sensors used among all the widgets
*******************************************************************************/
#define ADC_MAX_SENSORS_PER_WIDGET   (0u)
#define ADC_MAX_SENSORS_PER_5X5_TOUCHPAD (1u)

/*******************************************************************************
* Total number of all used electrodes (NOT unique)
*******************************************************************************/
#define ADC_TOTAL_ELECTRODES         (0u)
/* Obsolete */
#define ADC_TOTAL_SENSOR_IOS         ADC_TOTAL_ELECTRODES

/*******************************************************************************
* Total number of used physical IOs (unique)
*******************************************************************************/
#define ADC_TOTAL_IO_CNT             (0u)

/*******************************************************************************
* Array length for widget status registers
*******************************************************************************/
#define ADC_WDGT_STATUS_WORDS        \
                        (((uint8)((ADC_TOTAL_WIDGETS - 1u) / 32u)) + 1u)


/*******************************************************************************
* Auto-tuning mode selection
*******************************************************************************/
#define ADC_CSD_SS_DIS         (0x00ul)
#define ADC_CSD_SS_HW_EN       (0x01ul)
#define ADC_CSD_SS_TH_EN       (0x02ul)
#define ADC_CSD_SS_HWTH_EN     (ADC_CSD_SS_HW_EN | \
                                             ADC_CSD_SS_TH_EN)

#define ADC_CSD_AUTOTUNE       ADC_CSD_SS_DIS


/*******************************************************************************
* General settings
*******************************************************************************/

#define ADC_AUTO_RESET_METHOD_LEGACY (0u)
#define ADC_AUTO_RESET_METHOD_SAMPLE (1u)

#define ADC_MULTI_FREQ_SCAN_EN       (0u)
#define ADC_SENSOR_AUTO_RESET_EN     (0u)
#define ADC_SENSOR_AUTO_RESET_METHOD (0u)
#define ADC_NUM_CENTROIDS            (1u)
#define ADC_4PTS_LOCAL_MAX_EN        (0u)
#define ADC_OFF_DEBOUNCE_EN          (0u)
#define ADC_CUSTOM_DS_RAM_SIZE       (0u)

/* Defines power status of HW block after scanning */
#define ADC_BLOCK_OFF_AFTER_SCAN_EN  (0u)

/* Defines number of scan frequencies */
#if (ADC_DISABLE != ADC_MULTI_FREQ_SCAN_EN)
    #define ADC_NUM_SCAN_FREQS       (3u)
#else
    #define ADC_NUM_SCAN_FREQS       (1u)
#endif /* #if (ADC_DISABLE != ADC_MULTI_FREQ_SCAN_EN) */

/* Data size for thresholds / low baseline reset */
#define ADC_SIZE_8BITS               (8u)
#define ADC_SIZE_16BITS              (16u)

#define ADC_THRESHOLD_SIZE           ADC_SIZE_16BITS
typedef uint16 ADC_THRESHOLD_TYPE;

#if (ADC_AUTO_RESET_METHOD_LEGACY == ADC_SENSOR_AUTO_RESET_METHOD)
    #define ADC_LOW_BSLN_RST_SIZE        ADC_SIZE_8BITS
    typedef uint8 ADC_LOW_BSLN_RST_TYPE;
#else
    #define ADC_LOW_BSLN_RST_SIZE    (16u)
    typedef uint16 ADC_LOW_BSLN_RST_TYPE;
#endif /* #if (ADC_AUTO_RESET_METHOD_LEGACY == ADC_SENSOR_AUTO_RESET_METHOD) */

/* Coefficient to define touch threshold for proximity sensors */
#define ADC_PROX_TOUCH_COEFF         (300u)

/*******************************************************************************
* General Filter Constants
*******************************************************************************/

/* Baseline algorithm options */
#define ADC_IIR_BASELINE                 (0u)
#define ADC_BUCKET_BASELINE              (1u)

#define ADC_BASELINE_TYPE                ADC_IIR_BASELINE

/* IIR baseline filter algorithm for regular sensors*/
#define ADC_REGULAR_IIR_BL_TYPE          ADC_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for regular sensors */
#define ADC_REGULAR_IIR_BL_N             (1u)
#define ADC_REGULAR_IIR_BL_SHIFT         (8u)

/* IIR baseline filter algorithm for proximity sensors*/
#define ADC_PROX_IIR_BL_TYPE             ADC_IIR_FILTER_PERFORMANCE

/* IIR baseline coefficients for proximity sensors */
#define ADC_PROX_IIR_BL_N                (1u)
#define ADC_PROX_IIR_BL_SHIFT            (8u)


/* IIR filter constants */
#define ADC_IIR_COEFFICIENT_K            (256u)

/* IIR filter type */
#define ADC_IIR_FILTER_STANDARD          (1u)
#define ADC_IIR_FILTER_PERFORMANCE       (2u)
#define ADC_IIR_FILTER_MEMORY            (3u)

/* Regular sensor raw count filters */
#define ADC_REGULAR_RC_FILTER_EN         (0u)
#define ADC_REGULAR_RC_IIR_FILTER_EN     (0u)
#define ADC_REGULAR_RC_MEDIAN_FILTER_EN  (0u)
#define ADC_REGULAR_RC_AVERAGE_FILTER_EN (0u)
#define ADC_REGULAR_RC_CUSTOM_FILTER_EN  (0u)
#define ADC_REGULAR_RC_ALP_FILTER_EN     (0u)

/* Proximity sensor raw count filters */
#define ADC_PROX_RC_FILTER_EN            (0u)
#define ADC_PROX_RC_IIR_FILTER_EN        (0u)
#define ADC_PROX_RC_MEDIAN_FILTER_EN     (0u)
#define ADC_PROX_RC_AVERAGE_FILTER_EN    (0u)
#define ADC_PROX_RC_CUSTOM_FILTER_EN     (0u)
#define ADC_PROX_RC_ALP_FILTER_EN        (0u)

#define ADC_ALP_FILTER_EN                (0u)
#define ADC_REGULAR_RC_ALP_FILTER_COEFF  (2u)
#define ADC_PROX_RC_ALP_FILTER_COEFF     (2u)

/* Raw count filters */
#define ADC_RC_FILTER_EN                 (ADC_REGULAR_RC_FILTER_EN || ADC_PROX_RC_FILTER_EN)

/* IIR raw count filter algorithm for regular sensors */
#define ADC_REGULAR_IIR_RC_TYPE          (ADC_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for regular sensors */
#define ADC_REGULAR_IIR_RC_N             (128u)
#define ADC_REGULAR_IIR_RC_SHIFT         (0u)

/* IIR raw count filter algorithm for proximity sensors*/
#define ADC_PROX_IIR_RC_TYPE             (ADC_IIR_FILTER_STANDARD)

/* IIR raw count filter coefficients for proximity sensors */
#define ADC_PROX_IIR_RC_N                (128u)
#define ADC_PROX_IIR_RC_SHIFT            (0u)

/* Median filter constants */

/* Order of regular sensor median filter */
#define ADC_REGULAR_MEDIAN_LEN           (2u)

/* Order of proximity sensor median filter */
#define ADC_PROX_MEDIAN_LEN              (2u)

/* Average filter constants*/
#define ADC_AVERAGE_FILTER_LEN_2         (1u)
#define ADC_AVERAGE_FILTER_LEN_4         (3u)

/* Order of regular sensor average filter */
#define ADC_REGULAR_AVERAGE_LEN          (ADC_AVERAGE_FILTER_LEN_4)

/* Order of proximity sensor average filter */
#define ADC_PROX_AVERAGE_LEN             (ADC_AVERAGE_FILTER_LEN_4)

/* Widget baseline coefficient enable */
#define ADC_WD_BSLN_COEFF_EN             (0u)

/* Centroid position filters */
#define ADC_POSITION_FILTER_EN           (0u)
#define ADC_POS_MEDIAN_FILTER_EN         (0u)
#define ADC_POS_IIR_FILTER_EN            (0u)
#define ADC_POS_ADAPTIVE_IIR_FILTER_EN   (0u)
#define ADC_POS_AVERAGE_FILTER_EN        (0u)
#define ADC_POS_JITTER_FILTER_EN         (0u)
#define ADC_BALLISTIC_MULTIPLIER_EN      (0u)
#define ADC_CENTROID_3X3_CSD_EN          (0u)
#define ADC_CENTROID_5X5_CSD_EN          (0u)
#define ADC_CSD_5X5_MAX_FINGERS          (1u)

#define ADC_POS_IIR_COEFF                (128u)
#define ADC_POS_IIR_RESET_RADIAL_SLIDER  (35u)

#define ADC_CSX_TOUCHPAD_UNDEFINED       (40u)

/* IDAC options */

/* Third-generation HW block IDAC gain */
#define ADC_IDAC_GAIN_4X                 (4u)
#define ADC_IDAC_GAIN_8X                 (8u)

/* Fourth-generation HW block IDAC gain */
#define ADC_IDAC_GAIN_LOW                (0uL)
#define ADC_IDAC_GAIN_MEDIUM             (1uL)
#define ADC_IDAC_GAIN_HIGH               (2uL)

#define ADC_IDAC_SOURCING                (0u)
#define ADC_IDAC_SINKING                 (1u)

/* Shield tank capacitor precharge source */
#define ADC_CSH_PRECHARGE_VREF           (0u)
#define ADC_CSH_PRECHARGE_IO_BUF         (1u)

/* Shield electrode delay */
#define ADC_NO_DELAY                     (0u)

#if(ADC_ENABLE == ADC_CSDV2)
    #define ADC_SH_DELAY_5NS             (1u)
    #define ADC_SH_DELAY_10NS            (2u)
    #define ADC_SH_DELAY_20NS            (3u)
#else
    #if(ADC_ENABLE == ADC_CSDV1_VER2)
        #define ADC_SH_DELAY_10NS        (3u)
        #define ADC_SH_DELAY_50NS        (2u)
    #else
        #define ADC_SH_DELAY_1CYCLES     (1u)
        #define ADC_SH_DELAY_2CYCLES     (2u)
    #endif /* (ADC_ENABLE == ADC_CSDV1_VER2) */
#endif /* (ADC_ENABLE == ADC_CSDV2) */

/* Inactive sensor connection options */
#define ADC_SNS_CONNECTION_GROUND        (0x00000000u)
#define ADC_SNS_CONNECTION_HIGHZ         (0x00000001u)
#define ADC_SNS_CONNECTION_SHIELD        (0x00000002u)
#define ADC_SNS_CONNECTION_UNDEFINED     (0x00000003u)

/* Sense clock selection options */
#if defined(ADC_TAPEOUT_STAR_USED)
    #define ADC_CSDV2_REF9P6UA_EN            (0u)
#else
    #define ADC_CSDV2_REF9P6UA_EN            (1u)
#endif /* defined(ADC_TAPEOUT_STAR_USED) */

#define ADC_CLK_SOURCE_DIRECT            (0x00000000Lu)

#define ADC_CLK_SOURCE_SSC1              (0x01u)
#define ADC_CLK_SOURCE_SSC2              (0x02u)
#define ADC_CLK_SOURCE_SSC3              (0x03u)
#define ADC_CLK_SOURCE_SSC4              (0x04u)

#define ADC_CLK_SOURCE_PRS8              (0x05u)
#define ADC_CLK_SOURCE_PRS12             (0x06u)
#define ADC_CLK_SOURCE_PRSAUTO           (0xFFu)

#define ADC_MFS_IMO                      (0u)
#define ADC_MFS_SNS_CLK                  (1u)

/* Defines scan resolutions */
#define ADC_RES6BIT                      (6u)
#define ADC_RES7BIT                      (7u)
#define ADC_RES8BIT                      (8u)
#define ADC_RES9BIT                      (9u)
#define ADC_RES10BIT                     (10u)
#define ADC_RES11BIT                     (11u)
#define ADC_RES12BIT                     (12u)
#define ADC_RES13BIT                     (13u)
#define ADC_RES14BIT                     (14u)
#define ADC_RES15BIT                     (15u)
#define ADC_RES16BIT                     (16u)

/* Fourth-generation HW block: Initialization switch resistance */
#define ADC_INIT_SW_RES_LOW              (0x00000000Lu)
#define ADC_INIT_SW_RES_MEDIUM           (0x00000001Lu)
#define ADC_INIT_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: Initialization switch resistance */
#define ADC_SCAN_SW_RES_LOW              (0x00000000Lu)
#define ADC_SCAN_SW_RES_MEDIUM           (0x00000001Lu)
#define ADC_SCAN_SW_RES_HIGH             (0x00000002Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define ADC_SHIELD_SW_RES_LOW            (0x00000000Lu)
#define ADC_SHIELD_SW_RES_MEDIUM         (0x00000001Lu)
#define ADC_SHIELD_SW_RES_HIGH           (0x00000002Lu)
#define ADC_SHIELD_SW_RES_LOW_EMI        (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define ADC_INIT_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define ADC_INIT_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define ADC_INIT_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define ADC_INIT_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Fourth-generation HW block: CSD shield switch resistance */
#define ADC_SCAN_SHIELD_SW_RES_LOW       (0x00000000Lu)
#define ADC_SCAN_SHIELD_SW_RES_MEDIUM    (0x00000001Lu)
#define ADC_SCAN_SHIELD_SW_RES_HIGH      (0x00000002Lu)
#define ADC_SCAN_SHIELD_SW_RES_LOW_EMI   (0x00000003Lu)

/* Sensing method */
#define ADC_SENSING_LEGACY               (0x00000000Lu)
#define ADC_SENSING_LOW_EMI              (0x00000001Lu)
#define ADC_SENSING_FULL_WAVE            (0x00000002Lu)


/*******************************************************************************
* CSD/CSX Common Settings
*******************************************************************************/

#define ADC_BLOCK_ANALOG_WAKEUP_DELAY_US (0u)

#define ADC_MFS_METHOD                   (0u)
#define ADC_IMO_FREQUENCY_OFFSET_F1      (20u)
#define ADC_IMO_FREQUENCY_OFFSET_F2      (20u)

/*******************************************************************************
* CSD Specific Settings
*******************************************************************************/

/* CSD scan method settings */
#define ADC_CSD_IDAC_AUTOCAL_EN          (0u)
#define ADC_CSD_IDAC_GAIN                (ADC_IDAC_GAIN_HIGH)
#define ADC_CSD_SHIELD_EN                (0u)
#define ADC_CSD_SHIELD_TANK_EN           (0u)
#define ADC_CSD_CSH_PRECHARGE_SRC        (ADC_CSH_PRECHARGE_VREF)
#define ADC_CSD_SHIELD_DELAY             (ADC_NO_DELAY)
#define ADC_CSD_TOTAL_SHIELD_COUNT       (0u)
#define ADC_CSD_SCANSPEED_DIVIDER        (2u)
#define ADC_CSD_COMMON_SNS_CLK_EN        (0u)
#define ADC_CSD_SNS_CLK_SOURCE           (ADC_CLK_SOURCE_PRSAUTO)
#define ADC_CSD_SNS_CLK_DIVIDER          (4u)
#define ADC_CSD_INACTIVE_SNS_CONNECTION  (ADC_SNS_CONNECTION_GROUND)
#define ADC_CSD_IDAC_COMP_EN             (0u)
#define ADC_CSD_IDAC_CONFIG              (ADC_IDAC_SOURCING)
#define ADC_CSD_RAWCOUNT_CAL_LEVEL       (85u)
#define ADC_CSD_DUALIDAC_LEVEL           (50u)
#define ADC_CSD_PRESCAN_SETTLING_TIME    (5u)
#define ADC_CSD_SNSCLK_R_CONST           (1000u)
#define ADC_CSD_VREF_MV                  (2743u)

#define ADC_CSD_CALIBRATION_ERROR        (10u)
#define ADC_CSD_IDAC_AUTO_GAIN_EN        (1u)
#define ADC_CSD_IDAC_GAIN_INDEX_DEFAULT  (4u)
#define ADC_CSD_IDAC_MIN                 (20u)
#define ADC_CSD_COL_ROW_IDAC_ALIGNMENT_EN      (1u)

/* The macro is obsolete and should not be used */
#define ADC_CSD_DEDICATED_IDAC_COMP_EN   (1u)
/* CSD settings - Fourth-generation HW block */
#define ADC_CSD_ANALOG_STARTUP_DELAY_US  (10u)
#define ADC_CSD_FINE_INIT_TIME           (10u)
#define ADC_CSD_AUTO_ZERO_EN             (0u)
#define ADC_CSD_AUTO_ZERO_TIME           (15Lu)
#define ADC_CSD_NOISE_METRIC_EN          (0u)
#define ADC_CSD_NOISE_METRIC_TH          (1Lu)
#define ADC_CSD_INIT_SWITCH_RES          (ADC_INIT_SW_RES_MEDIUM)
#define ADC_CSD_SENSING_METHOD           (0)
#define ADC_CSD_SHIELD_SWITCH_RES        (ADC_SHIELD_SW_RES_MEDIUM)
#define ADC_CSD_GAIN                     (13Lu)

#define ADC_CSD_MFS_DIVIDER_OFFSET_F1    (1u)
#define ADC_CSD_MFS_DIVIDER_OFFSET_F2    (2u)

/*******************************************************************************
* CSX Specific Settings
*******************************************************************************/

/* CSX scan method settings */
#define ADC_CSX_SCANSPEED_DIVIDER        (2u)
#define ADC_CSX_COMMON_TX_CLK_EN         (0u)
#define ADC_CSX_TX_CLK_SOURCE            (ADC_CLK_SOURCE_PRSAUTO)
#define ADC_CSX_TX_CLK_DIVIDER           (40u)
#define ADC_CSX_INACTIVE_SNS_CONNECTION  (ADC_SNS_CONNECTION_GROUND)
#define ADC_CSX_MAX_FINGERS              (1u)
#define ADC_CSX_MAX_LOCAL_PEAKS          (5u)
#define ADC_CSX_IDAC_AUTOCAL_EN          (0u)
#define ADC_CSX_IDAC_BITS_USED           (7u)
#define ADC_CSX_RAWCOUNT_CAL_LEVEL       (40u)
#define ADC_CSX_IDAC_GAIN                (ADC_IDAC_GAIN_MEDIUM)
#define ADC_CSX_CALIBRATION_ERROR        (20u)
#define ADC_CSX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define ADC_CSX_MULTIPHASE_TX_EN         (0u)
#define ADC_CSX_MAX_TX_PHASE_LENGTH      (0u)

/* CSX settings - Fourth-generation HW block */
#define ADC_CSX_ANALOG_STARTUP_DELAY_US  (10u)
#define ADC_CSX_AUTO_ZERO_EN             (0u)
#define ADC_CSX_AUTO_ZERO_TIME           (15u)
#define ADC_CSX_FINE_INIT_TIME           (4u)
#define ADC_CSX_NOISE_METRIC_EN          (0u)
#define ADC_CSX_NOISE_METRIC_TH          (1u)
#define ADC_CSX_INIT_SWITCH_RES          (ADC_INIT_SW_RES_MEDIUM)
#define ADC_CSX_SCAN_SWITCH_RES          (ADC_SCAN_SW_RES_LOW)
#define ADC_CSX_INIT_SHIELD_SWITCH_RES   (ADC_INIT_SHIELD_SW_RES_HIGH)
#define ADC_CSX_SCAN_SHIELD_SWITCH_RES   (ADC_SCAN_SHIELD_SW_RES_LOW)

#define ADC_CSX_MFS_DIVIDER_OFFSET_F1    (1u)
#define ADC_CSX_MFS_DIVIDER_OFFSET_F2    (2u)

/* Gesture parameters */
#define ADC_GES_GLOBAL_EN                (0u)

/*******************************************************************************
* ISX Specific Settings
*******************************************************************************/

/* ISX scan method settings */
#define ADC_ISX_SCANSPEED_DIVIDER        (1u)
#define ADC_ISX_LX_CLK_DIVIDER           (80u)
#define ADC_ISX_IDAC_AUTOCAL_EN          (0u)
#define ADC_ISX_IDAC_BITS_USED           (7u)
#define ADC_ISX_RAWCOUNT_CAL_LEVEL       (30u)
#define ADC_ISX_IDAC_GAIN                (ADC_IDAC_GAIN_MEDIUM)
#define ADC_ISX_SKIP_OVSMPL_SPECIFIC_NODES (0u)
#define ADC_ISX_MAX_TX_PHASE_LENGTH      (0u)
#define ADC_ISX_PIN_COUNT_LX             (u)
/* ISX settings - Fourth-generation HW block */
#define ADC_ISX_AUTO_ZERO_EN             (0u)
#define ADC_ISX_AUTO_ZERO_TIME           (15u)
#define ADC_ISX_FINE_INIT_TIME           (20u)
#define ADC_ISX_NOISE_METRIC_EN          (0u)
#define ADC_ISX_NOISE_METRIC_TH          (1u)
#define ADC_ISX_INIT_SWITCH_RES          (ADC_INIT_SW_RES_MEDIUM)
#define ADC_ISX_SCAN_SWITCH_RES          (ADC_SCAN_SW_RES_LOW)
#define ADC_ISX_INIT_SHIELD_SWITCH_RES   (ADC_INIT_SHIELD_SW_RES_HIGH)
#define ADC_ISX_SCAN_SHIELD_SWITCH_RES   (ADC_SCAN_SHIELD_SW_RES_LOW)
#define ADC_ISX_SAMPLE_PHASE_DEG         (30u)

/*******************************************************************************
* Global Parameter Definitions
*******************************************************************************/

/* Compound section definitions */
#define ADC_ANY_NONSS_AUTOCAL ((0u != ADC_CSX_IDAC_AUTOCAL_EN) || \
                                       (0u != ADC_ISX_IDAC_AUTOCAL_EN) || \
                                      ((ADC_CSD_AUTOTUNE == ADC_CSD_SS_DIS) && (0u != ADC_CSD_IDAC_AUTOCAL_EN)))
#define ADC_ANYMODE_AUTOCAL (((0u != ADC_CSX_IDAC_AUTOCAL_EN) \
                                       || (0u != ADC_ISX_IDAC_AUTOCAL_EN)) \
                                       || (0u != ADC_CSD_IDAC_AUTOCAL_EN))
/* RAM Global Parameters Definitions */


/* RAM Sensor Parameters Definitions */


/*******************************************************************************
* ADC Specific Macros
*******************************************************************************/
#define ADC_ADC_RES8BIT                  (8u)
#define ADC_ADC_RES10BIT                 (10u)

#define ADC_ADC_FULLRANGE_MODE           (0u)
#define ADC_ADC_VREF_MODE                (1u)

#define ADC_ADC_MIN_CHANNELS             (1u)
#define ADC_ADC_EN                       (1u)
#define ADC_ADC_STANDALONE_EN            (1u)
#define ADC_ADC_TOTAL_CHANNELS           (4u)
#define ADC_ADC_RESOLUTION               (ADC_ADC_RES10BIT)
#define ADC_ADC_AMUXB_INPUT_EN           (0u)
#define ADC_ADC_SELECT_AMUXB_CH          (0u)
#define ADC_ADC_AZ_EN                    (1Lu)
#define ADC_ADC_AZ_TIME                  (5u)
#define ADC_ADC_VREF_MV                  (3840u)
#define ADC_ADC_GAIN                     (9Lu)
#define ADC_ADC_IDAC_DEFAULT             (27u)
#define ADC_ADC_MODCLK_DIV_DEFAULT       (1u)
#define ADC_ADC_MEASURE_MODE             (ADC_ADC_FULLRANGE_MODE)
#define ADC_ADC_ANALOG_STARTUP_DELAY_US  (5u)
#define ADC_ADC_ACQUISITION_TIME_US      (10u)

/*******************************************************************************
* Built-In Self-Test Configuration
*******************************************************************************/
#define ADC_SELF_TEST_EN                   (0Lu)
#define ADC_TST_GLOBAL_CRC_EN              (0Lu)
#define ADC_TST_WDGT_CRC_EN                (0Lu)
#define ADC_TST_BSLN_DUPLICATION_EN        (0Lu)
#define ADC_TST_BSLN_RAW_OUT_RANGE_EN      (0Lu)
#define ADC_TST_SNS_SHORT_EN               (0Lu)
#define ADC_TST_SNS_CAP_EN                 (0Lu)
#define ADC_TST_SH_CAP_EN                  (0Lu)
#define ADC_TST_EXTERNAL_CAP_EN            (0Lu)
#define ADC_TST_VDDA_EN                    (0Lu)


#define ADC_GLOBAL_CRC_AREA_START          (0u)
#define ADC_GLOBAL_CRC_AREA_SIZE           (0u)
#define ADC_WIDGET_CRC_AREA_START          (0u)
#define ADC_WIDGET_CRC_AREA_SIZE           (0u)

/* The resolution for sensor capacity measurement */
#define ADC_TST_SNS_CAP_RESOLUTION         (12u)

/* VDDA measurement test configuration */
/* The resolution for VDDA measurement */
#define ADC_TST_VDDA_RESOLUTION            (10u)
/* The ModClk divider for external capacitor capacity measurement */
#define ADC_TST_VDDA_MOD_CLK_DIVIDER       (1u)

#define ADC_TST_VDDA_VREF_MV               (0u)
#define ADC_TST_VDDA_VREF_GAIN             (0u)
#define ADC_TST_VDDA_IDAC_DEFAULT          (0u)

#define ADC_TST_FINE_INIT_TIME             (10u)
#define ADC_TST_ANALOG_STARTUP_DELAY_US    (23u)

#define ADC_TST_IDAC_AUTO_GAIN_EN          (1u)
#define ADC_TST_SNS_CAP_RAW_ERROR          (10u)
#define ADC_TST_IDAC_GAIN_INDEX            (0xFFu)
#define ADC_TST_RAW_TARGET                 (85u)

#define ADC_TST_SNS_SHORT_TIME             (2u)

#define ADC_SNS_CAP_CSD_INACTIVE_CONNECTION        (ADC_SNS_CONNECTION_GROUND)
#define ADC_SNS_CAP_CSX_INACTIVE_CONNECTION        (ADC_SNS_CONNECTION_GROUND)
#define ADC_SHIELD_CAP_INACTIVE_CONNECTION         (ADC_SNS_CONNECTION_GROUND)


/*******************************************************************************
* Gesture Configuration
*******************************************************************************/
#define ADC_TIMESTAMP_INTERVAL             (1Lu)
#define ADC_GESTURE_EN_WIDGET_ID           (0Lu)
#define ADC_BALLISTIC_EN_WIDGET_ID         (0Lu)


#endif /* CY_SENSE_ADC_CONFIGURATION_H */


/* [] END OF FILE */
