/***************************************************************************/ /**
 * @file sl_si91x_hal_soft_reset.c
 * @brief SoC soft reset API
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
#include "rsi_wwdt.h"
#include "cmsis_os2.h"
#include "sl_si91x_hal_soc_soft_reset.h"

/*
 *
 * @brief  WDT interrupt handler
 * @param  None
 * @return None
 */
#ifndef MATTER_WDT_IRQ
void WDT_IRQHandler(void)
{
  /*Clear interrupt */
  RSI_WWDT_IntrClear();
}
#endif
/*
 *
 * @brief  This API is used to config WDT
 * @param  None
 * @return None
 */
void sl_si91x_soc_soft_reset(void)
{
  RSI_PS_NpssPeriPowerUp(SLPSS_PWRGATE_ULP_MCUWDT);
  osDelay(2);
  /*Un mask WDT interrupt */
  RSI_WWDT_IntrUnMask();
  /*configure the WDT reset and interrupt counters */
  RSI_WWDT_ConfigIntrTimer(MCU_WDT, WDT_INTERRUPT_TIMER);
  /*Configure the WDT reset value*/
  RSI_WWDT_ConfigSysRstTimer(MCU_WDT, WDT_SYSTEM_RESET_TIMER);
  /*NVIC interrupt enables*/
  NVIC_EnableIRQ(NVIC_WDT);
  /*Start WDT */
  RSI_WWDT_Start(MCU_WDT);

  /*Upon Reset key size is 16 by default in case of inline  encryption */
  /*Store key length bit (32 Bytes) in BBFF if device security is with 32 Bytes key*/
  if (M4_QSPI_AES_CONFIG & AES_QSPI_KEY_SIZE) {
    M4_BBFF_STORAGE1 |= KEY_LENGTH;
  }
  while (1)
    ;
}
/*
 *
 * @brief  This API is used to do soc NVIC reset with the debug module disabled.
 * @param  None
 * @return None
 */
void sl_si91x_soc_nvic_reset(void)
{
  /*Upon Reset key size is 16 by default in case of inline  encryption */
  /*Store key length bit (32 Bytes) in BBFF if device security is with 32 Bytes key*/
  if (M4_QSPI_AES_CONFIG & AES_QSPI_KEY_SIZE) {
    M4_BBFF_STORAGE1 |= KEY_LENGTH;
  }
  __asm volatile("cpsid i" ::: "memory");
  /*Data Synchronization Barrier */
  __DSB();
  /*Instruction Synchronization Barrier */
  __ISB();
  /*Power Down the Debug Module */
  RSI_PS_M4ssPeriPowerDown(M4SS_PWRGATE_ULP_M4_DEBUG_FPU);
  /*Set the SYSRESETREQ bit in the AIRCR register to initiate a system reset */
  SCB->AIRCR = (0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk;
  /*Ensure the instruction is not optimized out */
  /*Data Synchronization Barrier */
  __DSB();
  /*Instruction Synchronization Barrier */
  __ISB();
  /*Wait for the reset to occur */
  while (1) {
    /* Infinite loop to keep the program running until the reset happens */
  }
}
