/*******************************************************************************
* @file  sl_gpio_board.h
* @brief sl gpio board specific configuration
*******************************************************************************
* # License
* <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* The licensor of this software is Silicon Laboratories Inc. Your use of this
* software is governed by the terms of Silicon Labs Master Software License
* Agreement (MSLA) available at
* www.silabs.com/about-us/legal/master-software-license-agreement. This
* software is distributed to you in Source Code format and is governed by the
* sections of the MSLA applicable to Source Code.
*
******************************************************************************/

#ifndef __SL_SI91X_GPIO_BOARD_H__
#define __SL_SI91X_GPIO_BOARD_H__
/**
 * @defgroup  Board_Specific_Driver   Board specific drivers and support functions
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup  Board_Drivers BOARD: Common board components used with board drivers
 * @{
 */
#include "RTE_Device_917.h"

#define SL_SI91X_GPIO_6_PORT RTE_GPIO_6_PORT
#define SL_SI91X_GPIO_6_PAD  RTE_GPIO_6_PAD
#define SL_SI91X_GPIO_6_PIN  RTE_GPIO_6_PIN
#define SL_SI91X_GPIO_6_MODE RTE_GPIO_6_MODE

#define SL_SI91X_GPIO_7_PORT RTE_GPIO_7_PORT
#define SL_SI91X_GPIO_7_PAD  RTE_GPIO_7_PAD
#define SL_SI91X_GPIO_7_PIN  RTE_GPIO_7_PIN
#define SL_SI91X_GPIO_7_MODE RTE_GPIO_7_MODE

#define SL_SI91X_GPIO_8_PORT RTE_GPIO_8_PORT
#define SL_SI91X_GPIO_8_PAD  RTE_GPIO_8_PAD
#define SL_SI91X_GPIO_8_PIN  RTE_GPIO_8_PIN
#define SL_SI91X_GPIO_8_MODE RTE_GPIO_8_MODE

#define SL_SI91X_GPIO_9_PORT RTE_GPIO_9_PORT
#define SL_SI91X_GPIO_9_PAD  RTE_GPIO_9_PAD
#define SL_SI91X_GPIO_9_PIN  RTE_GPIO_9_PIN
#define SL_SI91X_GPIO_9_MODE RTE_GPIO_9_MODE

#define SL_SI91X_GPIO_10_PORT RTE_GPIO_10_PORT
#define SL_SI91X_GPIO_10_PAD  RTE_GPIO_10_PAD
#define SL_SI91X_GPIO_10_PIN  RTE_GPIO_10_PIN
#define SL_SI91X_GPIO_10_MODE RTE_GPIO_10_MODE

#define SL_SI91X_GPIO_11_PORT RTE_GPIO_11_PORT
#define SL_SI91X_GPIO_11_PAD  RTE_GPIO_11_PAD
#define SL_SI91X_GPIO_11_PIN  RTE_GPIO_11_PIN
#define SL_SI91X_GPIO_11_MODE RTE_GPIO_11_MODE

#define SL_SI91X_GPIO_12_PORT RTE_GPIO_12_PORT
#define SL_SI91X_GPIO_12_PAD  RTE_GPIO_12_PAD
#define SL_SI91X_GPIO_12_PIN  RTE_GPIO_12_PIN
#define SL_SI91X_GPIO_12_MODE RTE_GPIO_12_MODE

#define SL_SI91X_GPIO_15_PORT RTE_GPIO_15_PORT
#define SL_SI91X_GPIO_15_PAD  RTE_GPIO_15_PAD
#define SL_SI91X_GPIO_15_PIN  RTE_GPIO_15_PIN
#define SL_SI91X_GPIO_15_MODE RTE_GPIO_15_MODE

#define SL_SI91X_GPIO_25_PORT RTE_GPIO_25_PORT
#define SL_SI91X_GPIO_25_PIN  RTE_GPIO_25_PIN
#define SL_SI91X_GPIO_25_MODE RTE_GPIO_25_MODE

#define SL_SI91X_GPIO_26_PORT RTE_GPIO_26_PORT
#define SL_SI91X_GPIO_26_PIN  RTE_GPIO_26_PIN
#define SL_SI91X_GPIO_26_MODE RTE_GPIO_26_MODE

#define SL_SI91X_GPIO_27_PORT RTE_GPIO_27_PORT
#define SL_SI91X_GPIO_27_PIN  RTE_GPIO_27_PIN
#define SL_SI91X_GPIO_27_MODE RTE_GPIO_27_MODE

#define SL_SI91X_GPIO_28_PORT RTE_GPIO_28_PORT
#define SL_SI91X_GPIO_28_PIN  RTE_GPIO_28_PIN
#define SL_SI91X_GPIO_28_MODE RTE_GPIO_28_MODE

#define SL_SI91X_GPIO_29_PORT RTE_GPIO_29_PORT
#define SL_SI91X_GPIO_29_PIN  RTE_GPIO_29_PIN
#define SL_SI91X_GPIO_29_MODE RTE_GPIO_29_MODE

#define SL_SI91X_GPIO_30_PORT RTE_GPIO_30_PORT
#define SL_SI91X_GPIO_30_PIN  RTE_GPIO_30_PIN
#define SL_SI91X_GPIO_30_MODE RTE_GPIO_30_MODE

#define SL_SI91X_GPIO_31_PORT RTE_GPIO_31_PORT
#define SL_SI91X_GPIO_31_PAD  RTE_GPIO_31_PAD
#define SL_SI91X_GPIO_31_PIN  RTE_GPIO_31_PIN
#define SL_SI91X_GPIO_31_MODE RTE_GPIO_31_MODE

#define SL_SI91X_GPIO_32_PORT RTE_GPIO_32_PORT
#define SL_SI91X_GPIO_32_PAD  RTE_GPIO_32_PAD
#define SL_SI91X_GPIO_32_PIN  RTE_GPIO_32_PIN
#define SL_SI91X_GPIO_32_MODE RTE_GPIO_32_MODE

#define SL_SI91X_GPIO_33_PORT RTE_GPIO_33_PORT
#define SL_SI91X_GPIO_33_PAD  RTE_GPIO_33_PAD
#define SL_SI91X_GPIO_33_PIN  RTE_GPIO_33_PIN
#define SL_SI91X_GPIO_33_MODE RTE_GPIO_33_MODE

#define SL_SI91X_GPIO_34_PORT RTE_GPIO_34_PORT
#define SL_SI91X_GPIO_34_PAD  RTE_GPIO_34_PAD
#define SL_SI91X_GPIO_34_PIN  RTE_GPIO_34_PIN
#define SL_SI91X_GPIO_34_MODE RTE_GPIO_34_MODE

#define SL_SI91X_GPIO_46_PORT RTE_GPIO_46_PORT
#define SL_SI91X_GPIO_46_PAD  RTE_GPIO_46_PAD
#define SL_SI91X_GPIO_46_PIN  RTE_GPIO_46_PIN
#define SL_SI91X_GPIO_46_MODE RTE_GPIO_46_MODE

#define SL_SI91X_GPIO_47_PORT RTE_GPIO_47_PORT
#define SL_SI91X_GPIO_47_PAD  RTE_GPIO_47_PAD
#define SL_SI91X_GPIO_47_PIN  RTE_GPIO_47_PIN
#define SL_SI91X_GPIO_47_MODE RTE_GPIO_47_MODE

#define SL_SI91X_GPIO_48_PORT RTE_GPIO_48_PORT
#define SL_SI91X_GPIO_48_PAD  RTE_GPIO_48_PAD
#define SL_SI91X_GPIO_48_PIN  RTE_GPIO_48_PIN
#define SL_SI91X_GPIO_48_MODE RTE_GPIO_48_MODE

#define SL_SI91X_GPIO_49_PORT RTE_GPIO_49_PORT
#define SL_SI91X_GPIO_49_PAD  RTE_GPIO_49_PAD
#define SL_SI91X_GPIO_49_PIN  RTE_GPIO_49_PIN
#define SL_SI91X_GPIO_49_MODE RTE_GPIO_49_MODE

#define SL_SI91X_GPIO_50_PORT RTE_GPIO_50_PORT
#define SL_SI91X_GPIO_50_PAD  RTE_GPIO_50_PAD
#define SL_SI91X_GPIO_50_PIN  RTE_GPIO_50_PIN
#define SL_SI91X_GPIO_50_MODE RTE_GPIO_50_MODE

#define SL_SI91X_GPIO_51_PORT RTE_GPIO_51_PORT
#define SL_SI91X_GPIO_51_PAD  RTE_GPIO_51_PAD
#define SL_SI91X_GPIO_51_PIN  RTE_GPIO_51_PIN
#define SL_SI91X_GPIO_51_MODE RTE_GPIO_51_MODE

#define SL_SI91X_GPIO_52_PORT RTE_GPIO_52_PORT
#define SL_SI91X_GPIO_52_PAD  RTE_GPIO_52_PAD
#define SL_SI91X_GPIO_52_PIN  RTE_GPIO_52_PIN
#define SL_SI91X_GPIO_52_MODE RTE_GPIO_52_MODE

#define SL_SI91X_GPIO_53_PORT RTE_GPIO_53_PORT
#define SL_SI91X_GPIO_53_PAD  RTE_GPIO_53_PAD
#define SL_SI91X_GPIO_53_PIN  RTE_GPIO_53_PIN
#define SL_SI91X_GPIO_53_MODE RTE_GPIO_53_MODE

#define SL_SI91X_GPIO_54_PORT RTE_GPIO_54_PORT
#define SL_SI91X_GPIO_54_PAD  RTE_GPIO_54_PAD
#define SL_SI91X_GPIO_54_PIN  RTE_GPIO_54_PIN
#define SL_SI91X_GPIO_54_MODE RTE_GPIO_54_MODE

#define SL_SI91X_GPIO_55_PORT RTE_GPIO_55_PORT
#define SL_SI91X_GPIO_55_PAD  RTE_GPIO_55_PAD
#define SL_SI91X_GPIO_55_PIN  RTE_GPIO_55_PIN
#define SL_SI91X_GPIO_55_MODE RTE_GPIO_55_MODE

#define SL_SI91X_GPIO_56_PORT RTE_GPIO_56_PORT
#define SL_SI91X_GPIO_56_PAD  RTE_GPIO_56_PAD
#define SL_SI91X_GPIO_56_PIN  RTE_GPIO_56_PIN
#define SL_SI91X_GPIO_56_MODE RTE_GPIO_56_MODE

#define SL_SI91X_GPIO_57_PORT RTE_GPIO_57_PORT
#define SL_SI91X_GPIO_57_PAD  RTE_GPIO_57_PAD
#define SL_SI91X_GPIO_57_PIN  RTE_GPIO_57_PIN
#define SL_SI91X_GPIO_57_MODE RTE_GPIO_57_MODE

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_0_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_0_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_0_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_0_PORT RTE_ULP_GPIO_0_PORT
#define SL_SI91X_ULP_GPIO_0_PAD  RTE_ULP_GPIO_0_PAD
#define SL_SI91X_ULP_GPIO_0_PIN  RTE_ULP_GPIO_0_PIN
#define SL_SI91X_ULP_GPIO_0_MODE RTE_ULP_GPIO_0_MODE
#elif (SL_SI91X_ULP_GPIO_0_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_0_PORT RTE_ULP_GPIO_0_PORT
#define SL_SI91X_ULP_GPIO_0_PIN  RTE_ULP_GPIO_0_PIN
#define SL_SI91X_ULP_GPIO_0_MODE RTE_ULP_GPIO_0_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_0_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_1_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_1_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_1_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_1_PORT RTE_ULP_GPIO_1_PORT
#define SL_SI91X_ULP_GPIO_1_PAD  RTE_ULP_GPIO_1_PAD
#define SL_SI91X_ULP_GPIO_1_PIN  RTE_ULP_GPIO_1_PIN
#define SL_SI91X_ULP_GPIO_1_MODE RTE_ULP_GPIO_1_MODE
#elif (SL_SI91X_ULP_GPIO_1_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_1_PORT RTE_ULP_GPIO_1_PORT
#define SL_SI91X_ULP_GPIO_1_PIN  RTE_ULP_GPIO_1_PIN
#define SL_SI91X_ULP_GPIO_1_MODE RTE_ULP_GPIO_1_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_1_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_2_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_2_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_2_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_2_PORT RTE_ULP_GPIO_2_PORT
#define SL_SI91X_ULP_GPIO_2_PAD  RTE_ULP_GPIO_2_PAD
#define SL_SI91X_ULP_GPIO_2_PIN  RTE_ULP_GPIO_2_PIN
#define SL_SI91X_ULP_GPIO_2_MODE RTE_ULP_GPIO_2_MODE
#elif (SL_SI91X_ULP_GPIO_2_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_2_PORT RTE_ULP_GPIO_2_PORT
#define SL_SI91X_ULP_GPIO_2_PIN  RTE_ULP_GPIO_2_PIN
#define SL_SI91X_ULP_GPIO_2_MODE RTE_ULP_GPIO_2_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_2_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_3_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_3_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_3_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_3_PORT RTE_ULP_GPIO_3_PORT
#define SL_SI91X_ULP_GPIO_3_PAD  RTE_ULP_GPIO_3_PAD
#define SL_SI91X_ULP_GPIO_3_PIN  RTE_ULP_GPIO_3_PIN
#define SL_SI91X_ULP_GPIO_3_MODE RTE_ULP_GPIO_3_MODE
#elif (SL_SI91X_ULP_GPIO_3_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_3_PORT RTE_ULP_GPIO_3_PORT
#define SL_SI91X_ULP_GPIO_3_PIN  RTE_ULP_GPIO_3_PIN
#define SL_SI91X_ULP_GPIO_3_MODE RTE_ULP_GPIO_3_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_3_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_4_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_4_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_4_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_4_PORT RTE_ULP_GPIO_4_PORT
#define SL_SI91X_ULP_GPIO_4_PAD  RTE_ULP_GPIO_4_PAD
#define SL_SI91X_ULP_GPIO_4_PIN  RTE_ULP_GPIO_4_PIN
#define SL_SI91X_ULP_GPIO_4_MODE RTE_ULP_GPIO_4_MODE
#elif (SL_SI91X_ULP_GPIO_4_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_4_PORT RTE_ULP_GPIO_4_PORT
#define SL_SI91X_ULP_GPIO_4_PIN  RTE_ULP_GPIO_4_PIN
#define SL_SI91X_ULP_GPIO_4_MODE RTE_ULP_GPIO_4_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_4_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_5_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_5_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_5_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_5_PORT RTE_ULP_GPIO_5_PORT
#define SL_SI91X_ULP_GPIO_5_PAD  RTE_ULP_GPIO_5_PAD
#define SL_SI91X_ULP_GPIO_5_PIN  RTE_ULP_GPIO_5_PIN
#define SL_SI91X_ULP_GPIO_5_MODE RTE_ULP_GPIO_5_MODE
#elif (SL_SI91X_ULP_GPIO_5_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_5_PORT RTE_ULP_GPIO_5_PORT
#define SL_SI91X_ULP_GPIO_5_PIN  RTE_ULP_GPIO_5_PIN
#define SL_SI91X_ULP_GPIO_5_MODE RTE_ULP_GPIO_5_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_5_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_6_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_6_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_6_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_6_PORT RTE_ULP_GPIO_6_PORT
#define SL_SI91X_ULP_GPIO_6_PAD  RTE_ULP_GPIO_6_PAD
#define SL_SI91X_ULP_GPIO_6_PIN  RTE_ULP_GPIO_6_PIN
#define SL_SI91X_ULP_GPIO_6_MODE RTE_ULP_GPIO_6_MODE
#elif (SL_SI91X_ULP_GPIO_6_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_6_PORT RTE_ULP_GPIO_6_PORT
#define SL_SI91X_ULP_GPIO_6_PIN  RTE_ULP_GPIO_6_PIN
#define SL_SI91X_ULP_GPIO_6_MODE RTE_ULP_GPIO_6_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_6_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_7_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_7_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_7_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_7_PORT RTE_ULP_GPIO_7_PORT
#define SL_SI91X_ULP_GPIO_7_PAD  RTE_ULP_GPIO_7_PAD
#define SL_SI91X_ULP_GPIO_7_PIN  RTE_ULP_GPIO_7_PIN
#define SL_SI91X_ULP_GPIO_7_MODE RTE_ULP_GPIO_7_MODE
#elif (SL_SI91X_ULP_GPIO_7_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_7_PORT RTE_ULP_GPIO_7_PORT
#define SL_SI91X_ULP_GPIO_7_PIN  RTE_ULP_GPIO_7_PIN
#define SL_SI91X_ULP_GPIO_7_MODE RTE_ULP_GPIO_7_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_7_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_8_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_8_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_8_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_8_PORT RTE_ULP_GPIO_8_PORT
#define SL_SI91X_ULP_GPIO_8_PAD  RTE_ULP_GPIO_8_PAD
#define SL_SI91X_ULP_GPIO_8_PIN  RTE_ULP_GPIO_8_PIN
#define SL_SI91X_ULP_GPIO_8_MODE RTE_ULP_GPIO_8_MODE
#elif (SL_SI91X_ULP_GPIO_8_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_8_PORT RTE_ULP_GPIO_8_PORT
#define SL_SI91X_ULP_GPIO_8_PIN  RTE_ULP_GPIO_8_PIN
#define SL_SI91X_ULP_GPIO_8_MODE RTE_ULP_GPIO_8_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_8_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_9_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_9_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_9_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_9_PORT RTE_ULP_GPIO_9_PORT
#define SL_SI91X_ULP_GPIO_9_PAD  RTE_ULP_GPIO_9_PAD
#define SL_SI91X_ULP_GPIO_9_PIN  RTE_ULP_GPIO_9_PIN
#define SL_SI91X_ULP_GPIO_9_MODE RTE_ULP_GPIO_9_MODE
#elif (SL_SI91X_ULP_GPIO_9_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_9_PORT RTE_ULP_GPIO_9_PORT
#define SL_SI91X_ULP_GPIO_9_PIN  RTE_ULP_GPIO_9_PIN
#define SL_SI91X_ULP_GPIO_9_MODE RTE_ULP_GPIO_9_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_9_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_10_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_10_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_10_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_10_PORT RTE_ULP_GPIO_10_PORT
#define SL_SI91X_ULP_GPIO_10_PAD  RTE_ULP_GPIO_10_PAD
#define SL_SI91X_ULP_GPIO_10_PIN  RTE_ULP_GPIO_10_PIN
#define SL_SI91X_ULP_GPIO_10_MODE RTE_ULP_GPIO_10_MODE
#elif (SL_SI91X_ULP_GPIO_10_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_10_PORT RTE_ULP_GPIO_10_PORT
#define SL_SI91X_ULP_GPIO_10_PIN  RTE_ULP_GPIO_10_PIN
#define SL_SI91X_ULP_GPIO_10_MODE RTE_ULP_GPIO_10_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_10_PIN Pin Configuration!"
#endif

#ifdef SI917_RADIO_BOARD
#define SL_SI91X_ULP_GPIO_11_PORT_ID 1
#else
#define SL_SI91X_ULP_GPIO_11_PORT_ID 0
#endif

#if (SL_SI91X_ULP_GPIO_11_PORT_ID == 0)
#define SL_SI91X_ULP_GPIO_11_PORT RTE_ULP_GPIO_11_PORT
#define SL_SI91X_ULP_GPIO_11_PAD  RTE_ULP_GPIO_11_PAD
#define SL_SI91X_ULP_GPIO_11_PIN  RTE_ULP_GPIO_11_PIN
#define SL_SI91X_ULP_GPIO_11_MODE RTE_ULP_GPIO_11_MODE
#elif (SL_SI91X_ULP_GPIO_11_PORT_ID == 1)
#define SL_SI91X_ULP_GPIO_11_PORT RTE_ULP_GPIO_11_PORT
#define SL_SI91X_ULP_GPIO_11_PIN  RTE_ULP_GPIO_11_PIN
#define SL_SI91X_ULP_GPIO_11_MODE RTE_ULP_GPIO_11_MODE
#else
#error "Invalid  SL_SI91X_ULP_GPIO_11_PIN Pin Configuration!"
#endif

#define SL_SI91X_UULP_GPIO_0_PIN  RTE_UULP_GPIO_0_PIN
#define SL_SI91X_UULP_GPIO_0_MODE RTE_UULP_GPIO_0_MODE

#define SL_SI91X_UULP_GPIO_1_PIN  RTE_UULP_GPIO_1_PIN
#define SL_SI91X_UULP_GPIO_1_MODE RTE_UULP_GPIO_1_MODE

#define SL_SI91X_UULP_GPIO_2_PIN  RTE_UULP_GPIO_2_PIN
#define SL_SI91X_UULP_GPIO_2_MODE RTE_UULP_GPIO_2_MODE

#define SL_SI91X_UULP_GPIO_3_PIN  RTE_UULP_GPIO_3_PIN
#define SL_SI91X_UULP_GPIO_3_MODE RTE_UULP_GPIO_3_MODE

#define SL_SI91X_UULP_GPIO_4_PIN  RTE_UULP_GPIO_4_PIN
#define SL_SI91X_UULP_GPIO_4_MODE RTE_UULP_GPIO_4_MODE

#define SL_SI91X_UULP_GPIO_5_PIN  RTE_UULP_GPIO_5_PIN
#define SL_SI91X_UULP_GPIO_5_MODE RTE_UULP_GPIO_5_MODE

#ifdef __cplusplus
}
#endif

#endif /*__SL_SI91X_GPIO_BOARD_H__*/

/* @} end of Board_Drivers */
/* @} end of Board_Specific_Driver */
