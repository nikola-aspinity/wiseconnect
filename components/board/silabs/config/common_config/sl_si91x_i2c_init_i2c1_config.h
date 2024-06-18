/***************************************************************************/ /**
* @file sl_si91x_i2c_i2c1_config.h
* @brief I2c driver instance configuration file.
*******************************************************************************
* # License
* <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* SPDX-License-Identifier: Zlib
*
* The licensor of this software is Silicon Laboratories Inc.
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
******************************************************************************/

#ifndef SL_SI91X_I2C_I2C1_CONFIG_H
#define SL_SI91X_I2C_I2C1_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
#ifdef __cplusplus
extern "C" {
#endif

#include "sl_si91x_i2c.h"
/******************************************************************************/
/******************************* I2C Configuration **************************/
// <h> I2C1 Configuration

// <o SL_I2C_I2C1_MODE> Mode
//   <SL_I2C_LEADER_MODE=> Leader mode
//   <SL_I2C_FOLLOWER_MODE=> Follower mode
// <i> Selection of the I2C Mode.
#define SL_I2C_I2C1_MODE SL_I2C_LEADER_MODE

// <o SL_I2C_I2C1_OPERATING_MODE> Operating Mode
//   <SL_I2C_STANDARD_MODE=> Standard mode
//   <SL_I2C_FAST_MODE=> Fast mode
//   <SL_I2C_FAST_PLUS_MODE=> Fast plus mode
//   <SL_I2C_HIGH_SPEED_MODE=> High speed mode
// <i> Selection of the I2C Mode.
#define SL_I2C_I2C1_OPERATING_MODE SL_I2C_STANDARD_MODE

// <o SL_I2C_I2C1_TRANSFER_TYPE> Transfer Type
//   <SL_I2C_USING_INTERRUPT=> Using Interrupt
//   <SL_I2C_USING_DMA=> Using DMA
// <i> Selection of the I2C Mode.
#define SL_I2C_I2C1_TRANSFER_TYPE SL_I2C_USING_INTERRUPT

// </h> End I2C1 Configuration
/******************************************************************************/
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <i2c signal=SCL,SDA> SL_I2C1
// $[I2C_SL_I2C1]
#ifndef SL_I2C1_PERIPHERAL
#define SL_I2C1_PERIPHERAL I2C1
#endif

// I2C1 SCL on GPIO_50
#ifndef SL_I2C1_SCL_PORT
#define SL_I2C1_SCL_PORT 0
#endif
#ifndef SL_I2C1_SCL_PIN
#define SL_I2C1_SCL_PIN 50
#endif
#ifndef SL_I2C1_SCL_LOC
#define SL_I2C1_SCL_LOC 2
#endif

// I2C1 SDA on GPIO_51
#ifndef SL_I2C1_SDA_PORT
#define SL_I2C1_SDA_PORT 0
#endif
#ifndef SL_I2C1_SDA_PIN
#define SL_I2C1_SDA_PIN 51
#endif
#ifndef SL_I2C1_SDA_LOC
#define SL_I2C1_SDA_LOC 8
#endif
// [I2C_SL_I2C1]$
// <<< sl:end pin_tool >>>

#define SL_I2C_I2C1_SCL_PORT SL_I2C1_SCL_PORT
#define SL_I2C_I2C1_SCL_PIN  SL_I2C1_SCL_PIN
#define SL_I2C_I2C1_SCL_MUX  SL_SI91X_I2C1_SCL_MUX
#define SL_I2C_I2C1_SCL_PAD  SL_SI91X_I2C1_SCL_PAD
#define SL_I2C_I2C1_SCL_REN  SL_SI91X_I2C1_SCL_REN

#define SL_I2C_I2C1_SDA_PORT SL_I2C1_SDA_PORT
#define SL_I2C_I2C1_SDA_PIN  SL_I2C1_SDA_PIN
#define SL_I2C_I2C1_SDA_MUX  SL_SI91X_I2C1_SDA_MUX
#define SL_I2C_I2C1_SDA_PAD  SL_SI91X_I2C1_SDA_PAD
#define SL_I2C_I2C1_SDA_REN  SL_SI91X_I2C1_SDA_REN

#ifdef __cplusplus
}
#endif

#endif // SL_SI91X_I2C_I2C1_CONFIG_H