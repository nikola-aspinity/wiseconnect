/*******************************************************************************
 * @file  sdio_secondary_example.c
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
/**===========================================================================
 * @brief : This file contains application code for SDIO slave device
 * @section Description :
 * This example demonstrates data transfer through SDIO. The device acts as a
 * slave which interfaces with an external sdio host/master.
============================================================================**/
#include "sdio_secondary_example.h"
#include "UDMA.h"
#include "clock_update.h"
#include "sl_si91x_sdio_secondary_drv_config.h"
#include "sl_si91x_peripheral_sdio_secondary.h"
#include "rsi_debug.h"
#include "rsi_rom_clks.h"
#include "sl_si91x_clock_manager.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define BLOCK_LEN        256
#define NO_OF_BLOCKS     4
#define XFER_BUFFER_SIZE (BLOCK_LEN * NO_OF_BLOCKS) // Buffer size is 256B*4 = 1KB

#define SW_CORE_CLK 1

#if SW_CORE_CLK
#define ICACHE2_ADDR_TRANSLATE_1_REG *(volatile uint32_t *)(0x20280000 + 0x24)
#ifndef MISC_CFG_SRAM_REDUNDANCY_CTRL
#define MISC_CFG_SRAM_REDUNDANCY_CTRL *(volatile uint32_t *)(M4_MISC_CONFIG_BASE + 0x18)
#endif // MISC_CFG_SRAM_REDUNDANCY_CTRL
#ifndef MISC_CONFIG_MISC_CTRL1
#define MISC_CONFIG_MISC_CTRL1 *(volatile uint32_t *)(M4_MISC_CONFIG_BASE + 0x44)
#endif // MISC_CONFIG_MISC_CTRL1
#define MISC_QUASI_SYNC_MODE  *(volatile uint32_t *)(M4_MISC_CONFIG_BASE + 0x84)
#define SOC_PLL_REF_FREQUENCY 40000000  // PLL input REFERENCE clock 40MHZ
#define PS4_SOC_FREQ          150000000 // PLL out clock 150MHz
#endif                                  // SW_CORE_CLK

#define SOC_PLL_CLK  ((uint32_t)(180000000)) // 180MHz default SoC PLL Clock as source to Processor
#define INTF_PLL_CLK ((uint32_t)(180000000)) // 180MHz default Interface PLL Clock as source to all peripherals
/*******************************************************************************
 ******************************  Data Types  ***********************************
 ******************************************************************************/

// Enum for different transmission scenarios
typedef enum {
  SEND_DATA,              // Transfer data to the sdio primary
  RECEIVE_DATA,           // Receive data from the sdio primary
  TRANSMISSION_COMPLETED, // Transmission completed mode
} sdio_mode_enum_t;

// Modify the current mode to SEND_DATA enum to send data to the master
static sdio_mode_enum_t current_mode = RECEIVE_DATA;
/*******************************************************************************
 ***************************   LOCAL VARIABLES   *******************************
 ******************************************************************************/

// Application buffer for transfers
uint8_t xfer_buffer[XFER_BUFFER_SIZE];

volatile uint8_t host_intr_event = 0;
volatile uint8_t dmaDone         = 0;
boolean_t send_data_flag         = true;
boolean_t receive_data_flag      = true;

/*******************************************************************************
 ******************************   FUNCTIONS   **********************************
 ******************************************************************************/
void gdpma_callbak(uint8_t dma_ch);
void application_callback(uint8_t events);
static void default_clock_configuration(void);

/***************************************************************************/ /**
 * @brief       
 *   This is an application callback function for host interrupt events raised
 *   within the IRQ handler in the sdio slave peripheral driver
 *
 * @param[in] events
 *   Each bit has an event linked to it
 ******************************************************************************/
void application_callback(uint8_t events)
{
  if ((events & HOST_INTR_RECEIVE_EVENT) == 1) {
    host_intr_event = 1;
  }
}

/***************************************************************************/ /**
 * @brief
 *   This is an application callback function for the data transger success using gpdma
 *   within the IRQ handler in the sdio secondary peripheral driver
 *
 ******************************************************************************/
void gdpma_callbak(uint8_t dma_ch)
{
  UNUSED_PARAMETER(dma_ch);
  dmaDone = 1;
}

uint32_t tt_start = 0, tt_end = 0;
uint32_t packet_count = 0;
uint32_t packet_size  = 0;
uint32_t throughput   = 0;
/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
// Function to configure clock on powerup
static void default_clock_configuration(void)
{
  // Core Clock runs at 180MHz SOC PLL Clock
  sl_si91x_clock_manager_m4_set_core_clk(M4_SOCPLLCLK, SOC_PLL_CLK);

  // All peripherals' source to be set to Interface PLL Clock
  // and it runs at 180MHz
  sl_si91x_clock_manager_set_pll_freq(INFT_PLL, INTF_PLL_CLK, PLL_REF_CLK_VAL_XTAL);
}
/*******************************************************************************
 * SDIO Secondary initialization function
 ******************************************************************************/
void sdio_secondary_example_init(void)
{
  sl_status_t status;

  // default clock configuration by application common for whole system
  default_clock_configuration();

  SysTick_Config(SystemCoreClock / 1000);

  status = sl_si91x_sdio_secondary_init();
  if (status != SL_STATUS_OK) {
    DEBUGOUT("\r\nSDIO Secondary init failed\r\n");
  }
  DEBUGOUT("\r\nSDIO secondary init success\r\n");

  status = sl_si91x_sdio_secondary_register_event_callback(application_callback, SL_SDIO_WR_INT_EN);
  if (status != SL_STATUS_OK) {
    DEBUGOUT("\r\nSDIO Secondary callback function registration failed\r\n");
  }
  DEBUGOUT("\r\nSDIO Secondary callback function registration success\r\n");

  sl_si91x_sdio_secondary_gpdma_register_event_callback(gdpma_callbak);

  tt_start    = GetTickCount();
  packet_size = XFER_BUFFER_SIZE;
}

/*******************************************************************************
 * Function will run continuously in while loop
 ******************************************************************************/
void sdio_secondary_example_process_action(void)
{
  // In switch case, according to the current mode, the transmission is executed.
  switch (current_mode) {
    case RECEIVE_DATA:
      if (receive_data_flag) {
        // Validation for executing the API only once.
        sl_si91x_sdio_secondary_receive(xfer_buffer);
        packet_count++;
        receive_data_flag = false;
      }

      if (dmaDone & host_intr_event) {
        current_mode      = RECEIVE_DATA;
        dmaDone           = false;
        host_intr_event   = false;
        receive_data_flag = true;
        if ((GetTickCount() - tt_start) >= 2000) {

          tt_end = GetTickCount();
          DEBUGOUT("Data is received from Host->slave successfully \n");
          DEBUGOUT("\r\nPackets received: %ld\r\n", packet_count);
          DEBUGOUT("Total bits received: %ld \r\n", (packet_count * packet_size * 8));
          DEBUGOUT("Time diff: %ld ms\r\n", (tt_end - tt_start));

          throughput = (packet_count * packet_size * 8) / ((tt_end - tt_start) / 1000);
          DEBUGOUT("Throughput master->slave = %ld bps \r\n", throughput);

          packet_count = 0;
          tt_start     = GetTickCount();
        }
        // clear application buffer
        memset(xfer_buffer, 0, XFER_BUFFER_SIZE);
      }
      break;
    case SEND_DATA:
      if (send_data_flag) {

        // Filled data in tx buffer
        for (int i = 0; i < XFER_BUFFER_SIZE; i++) {
          xfer_buffer[i] = (uint8_t)(i / 256) + 1;
        }

        // Validation for executing the API only once.
        sl_si91x_sdio_secondary_send(NO_OF_BLOCKS, xfer_buffer);
        packet_count++;
        send_data_flag = false;
      }
      if (dmaDone) {
        // It waits till i2c_send_complete is true in IRQ handler.
        DEBUGOUT("Data is transferred from slave to master successfull \n");
        current_mode   = SEND_DATA;
        send_data_flag = true;
        dmaDone        = false;
        if ((GetTickCount() - tt_start) >= 2000) {

          tt_end = GetTickCount();

          DEBUGOUT("\r\nPackets sent: %ld\r\n", packet_count);
          DEBUGOUT("Total bits sent:%ld \r\n", (packet_count * packet_size * 8));
          DEBUGOUT("Time diff :%ld ms \r\n", (tt_end - tt_start));

          throughput = (packet_count * packet_size * 8) / ((tt_end - tt_start) / 1000);
          DEBUGOUT("Throughput for slave->master= %ld bps \r\n", throughput);

          packet_count = 0;
        }
      }
      break;
    case TRANSMISSION_COMPLETED:
      break;
    default:
      break;
  }
}
