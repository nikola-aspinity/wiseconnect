/***************************************************************************/ /**
* @file sensor_hub.h
* @brief sensor_hub example
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
#ifndef SENSOR_HUB_H_
#define SENSOR_HUB_H_
#include <stdint.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <event_groups.h>
#include <timers.h>
#include "rsi_chip.h"
#include "rsi_os.h"
#include "hub_hal_intf.h"
#include "sl_status.h"
#include "sensors_config.h"
#include "sensorhub_error_codes.h"
/**************************************************************************/ /**
 * @addtogroup SENSOR-HUB Sensor Hub
 * @ingroup SI91X_SERVICE_APIS
 * @{
 *
 ******************************************************************************/
/*******************************************************************************
 ********************* Sensor_HUB Defines / Macros  ****************************
 ******************************************************************************/
#define SL_SH_SENSOR_TASK_STACK_SIZE     (512 * 2)     ///< Sensor task stack size
#define SL_SH_EM_TASK_STACK_SIZE         (512 * 2)     ///< EM task stack size
#define SL_SH_POWER_SAVE_TASK_STACK_SIZE (512 * 2)     ///< Power task stack size
#define SL_EM_TASK_RUN_TICKS             osWaitForever ///< Max wait time of message queue in Event task
#define MAP_TABLE_SIZE                   10            ///< Size of the sensors interrupt MAP table

/*******************************************************************************
 ***********************  GPIO IRQ Defines / Macros  ***************************
 ******************************************************************************/
#define NPSS_GPIO_IRQHandler IRQ021_Handler             ///< NPSS gpio IRQ handler
#define NPSS_GPIO_NVIC       NPSS_TO_MCU_GPIO_INTR_IRQn ///< NPSS gpio IRQ Number 21

/*******************************************************************************
 ******************** Wake UP Alarm Defines / Macros  **************************
 ******************************************************************************/
#define SL_ALARM_PERIODIC_TIME         10   ///< Periodic alarm configuration in milliseconds
#define RC_TRIGGER_TIME                5    ///< RC clock trigger time
#define RO_TRIGGER_TIME                0    ///< RO clock trigger time
#define NO_OF_HOURS_IN_A_DAY           24   ///< Number of hours in a day
#define NO_OF_MINUTES_IN_AN_HOUR       60   ///< Number of minutes in an hour
#define NO_OF_SECONDS_IN_A_MINUTE      60   ///< Number of Seconds in a minute
#define NO_OF_MILLISECONDS_IN_A_SECOND 1000 ///< Number of milliseconds in a second
#define NO_OF_MONTHS_IN_A_YEAR         12   ///< Number of months in a year
#define BASE_YEAR                      2000 ///< Start year for alarm configuration
#define NO_OF_DAYS_IN_A_MONTH_1        28   ///< Month with 28 days
#define NO_OF_DAYS_IN_A_MONTH_2        29   ///< Month with 29 days
#define NO_OF_DAYS_IN_A_MONTH_3        30   ///< Month with 30 days
#define NO_OF_DAYS_IN_A_MONTH_4        31   ///< Month with 31 days

/*******************************************************************************
 ************************ Alarm IRQ Defines / Macros  **************************
 ******************************************************************************/
#define RTC_ALARM_IRQHandler IRQ028_Handler     ///< Alarm IRQ handler
#define NVIC_RTC_ALARM       MCU_CAL_ALARM_IRQn ///< Alarm IRQ number 28

/*******************************************************************************
 ************************ Callback function pointer  **************************
 ******************************************************************************/
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
typedef void (*sl_sensor_signalEvent_t)(uint8_t sensor_id, uint8_t event, void *data);
/** @endcond */

/*******************************************************************************
 ************************* Enumeration for sensor HUB  *************************
 ******************************************************************************/

/// @brief Enumeration for Sensor HUB data reading mode
typedef enum {
  SL_SH_POLLING_MODE,   ///< POLLING_MODE
  SL_SH_INTERRUPT_MODE, ///< INTERRUPT_MODE
  SL_SH_NO_MODE,
} sl_sensor_mode_t;

/// @brief Enumeration for Sensors HUB Callback Events
typedef enum {
  SL_SENSOR_CREATION_FAILED,
  SL_SENSOR_STARTED,
  SL_SENSOR_STOPPED,
  SL_SENSOR_DATA_READY,
  SL_SENSOR_CNFG_INVALID,
  SL_SENSOR_START_FAILED,
  SL_SENSOR_STOP_FAILED,
  SL_SENSOR_DELETED,
  SL_SENSOR_DELETE_FAILED,
} sl_sensorhub_event_t;

/// @brief Enumeration for GPIO Interrupt Configurations.
typedef enum {
  SL_SH_RISE_EDGE, ///< Interrupt at GPIO rise edge
  SL_SH_FALL_EDGE, ///< Interrupt at GPIO fall edge
  SL_SH_LOW_LEVEL, ///< Interrupt at GPIO low level
  SL_SH_HIGH_LEVEL ///< Interrupt at GPIO high level
} sl_gpio_intr_type_t;

/// @brief Enumeration for Sensor HUB data delivery mode.
typedef enum {
  SL_SH_THRESHOLD,      ///< Threshold value for sensor data delivery
  SL_SH_TIMEOUT,        ///< Timeout value for sensor data delivery
  SL_SH_NUM_OF_SAMPLES, ///< Number of samples for sensor data delivery
  SL_SH_NO_DATA_MODE    ///<
} sl_data_deliver_mode_t;

/// @brief Enumeration for Sensors Status.
typedef enum {
  SL_SENSOR_INVALID, ///< Sensor is Invalid
  SL_SENSOR_VALID,   ///< Sensor is Valid
  SL_SENSOR_START,   ///< Sensor is Started
  SL_SENSOR_STOP     ///< Sensor is Stoped
} sl_sensor_status_t;
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/// @brief Enumeration for Sensor HUB Power states.
typedef enum { SL_SH_PS4TOPS2, SL_SH_PS2TOPS4, SL_SH_SLEEP_WAKEUP, SL_SH_DUMMY } sl_power_state_t;
/** @endcond */
/*******************************************************************************
 *************************** Structures for sensor HUB  ************************
 ******************************************************************************/

/// @brief Used to Monitor the bus errors in the Sensor HUB

typedef struct {
  bool i2c; ///< I2C bus error status
  bool spi; ///< SPI bus error status
  bool adc; ///< ADC bus error status
  bool sdc;
  bool sensor_global_status; ///< All buses error status
} sl_sensorhub_errors_t;

/// @brief Sensor data delivery modes in Sensor HUB

typedef struct {
  sl_data_deliver_mode_t data_mode;
  union {
    uint32_t threshold;    ///< Threshold value for the sensor
    uint32_t timeout;      ///< Timeout values for the sensor
    uint32_t numofsamples; ///< Number of samples for the sensor
  };
} sl_data_deliver_type_t;

/// @brief Storing the Sensor Configurations from the User

typedef struct {
  char *sensor_name;              ///< Name of the sensor
  int16_t sensor_intr_type;       ///< GPIO Interrupt Configurations.
  uint16_t sampling_intr_req_pin; ///< GPIO pin for sampling the sensor data
  uint32_t sampling_interval;     ///< Sensor data sampling interval
  union {
    uint8_t address;  ///< Address of sensor
    uint16_t channel; ///< Channel for adc
  };
  sl_sensor_id_t sensor_id;                ///< Sensor id
  sl_sensor_bus_t sensor_bus;              ///< Protocol for the sensor(spi/i2c)
  sl_sensor_mode_t sensor_mode;            ///< Sensor Mode(Enumeration)
  sl_sensor_range_t sensor_range;          ///< Range of sensor
  sl_data_deliver_type_t data_deliver;     ///< Data delivery mode for the sensor
  sl_sensor_data_group_t *sensor_data_ptr; ///< Sensor data storage structure
} sl_sensor_info_t;

/// @brief Monitoring the Sensors Status.

typedef struct {
  void *sensor_handle;                ///< Sensor handle
  void *ctrl_handle;                  ///< Sensor control handle
  uint8_t sensor_event_bit;           ///< Sensor event bits
  uint8_t event_ack;                  ///< Sensor event acknowledge
  uint16_t max_samples;               ///< Maximum samples for the sensors
  sl_sensor_info_t *config_st;        ///< Sensor configuration structure
  sl_sensor_impl_type_t *sensor_impl; ///< Sensor implementation structure
  sl_sensor_status_t sensor_status;   ///< Sensor status
  TimerHandle_t timer_handle;         ///< RTOS timer handle
} sl_sensor_handle_t;

/// @brief Maintaining Sensors list for Polling mode

typedef struct {
  uint8_t sensor_index;                                 ///< Sensor index
  sl_sensor_handle_t sl_sensors_st[SL_MAX_NUM_SENSORS]; ///< Sensor handle structure
} sl_sensor_list_t;

/// @brief Used to keep track of the interrupt number and interrupt sensor index

typedef struct {
  uint8_t sensor_list_index; ///< Interrupt mode sensor index
  uint16_t intr;             ///< Interrupt GPIO Pin
  uint16_t adc_intr_channel; ///< Channel number for ADC interrupt
  uint16_t sdc_intr_channel; ///< Channel number for ADC interrupt
} sl_intr_list_t;

/// @brief Sensors interrupt mode MAP TABLE

typedef struct {
  uint8_t map_index;                        ///< Map Table Index
  sl_intr_list_t map_table[MAP_TABLE_SIZE]; ///< Sensor list MAP Table
} sl_intr_list_map_t;

/// @brief Sensor events info structure

typedef struct {
  void *em_sensor_data;       ///< String the sensor data address
  sl_sensor_id_t sensor_id;   ///< Sensor id information
  sl_sensorhub_event_t event; ///< Sensors HUB Callback Events
} sl_em_event_t;

/// @brief Event callback configuration structure

typedef struct {
  sl_sensor_signalEvent_t cb_event; ///< Event callback
  sl_sensor_id_t *cb_event_ack;     ///< Event callback acknowledge
} sl_sensor_cb_info_t;

/// @brief I2C bus interface configuration structure

typedef struct {
  uint8_t i2c_id;           ///< I2C instances(I2C0/1/2)
  uint8_t i2c_power_state;  ///< I2C power state
  uint8_t i2c_control_mode; ///< I2C bus control configuration
  uint16_t i2c_bus_speed;   ///< I2C bus speed
  uint32_t i2c_slave_addr;  ///< I2C slave address
} sl_i2c_config_t;

/// @brief SPI bus interface configuration structure

typedef struct {
  uint8_t spi_bit_width;     ///< SPI bus width
  uint8_t spi_mode;          ///< SPI Mode(Master/Slave)
  uint8_t spi_power_state;   ///< SPI bus power mode
  uint8_t spi_cs_number;     ///< Chip select number
  uint8_t spi_cs_misc_mode;  ///< SPI miscellaneous for chip select
  uint8_t spi_sec_sel_sig;   ///< SPI slave select signal definitions
  uint32_t spi_baud;         ///< SPI bus data transmission speed(clock)
  uint64_t spi_control_mode; ///< SPI bus phase and polarity
  uint64_t spi_cs_mode;      ///< SPI control slave select mode
} sl_spi_config_t;

/// @brief ADC bus interface configuration structure

typedef struct sl_adc_config {
  uint8_t adc_init;                   ///< flag to know if adc is initialized, this is necessary to deinit
  uint16_t adc_data_ready;            ///< flag to indicate data availability for all 16 channels
  sl_adc_config_t adc_cfg;            ///< adc configuration
  sl_adc_channel_config_t adc_ch_cfg; ///< adc channel configuration
} sl_adc_cfg_t;

/// @brief GPIO interface configuration structure

typedef struct {
  uint8_t c;
  uint32_t d;
} sl_gpio_config_t;

/// @brief SDC interface configuration structure

typedef struct {
  uint8_t sh_sdc_p_channel_sel[4];
  uint8_t sh_sdc_n_channel_sel[4];
  uint8_t sh_sdc_sample_ther;
  uint8_t sh_sdc_no_channel_sel;
  uint8_t sh_sdc_data_trigger_sel;
  uint8_t sh_sdc_sample_trigger_sel;
  uint8_t sh_sdc_cnt_trig_evnt;
  uint8_t sh_sdc_auxadc_diff_mode_ch[4];
  uint8_t sh_sdc_auxadc_en;
  uint8_t sh_sdc_adc_config_en;
  uint8_t sh_sdc_clk_div;
  uint8_t sh_sdc_samp_en;
} sl_sh_sdc_config_t;

/// @brief Sensor HUB bus interface configuration structure

typedef struct {
  sl_i2c_config_t i2c_config;       ///< I2C configuration structure
  sl_spi_config_t spi_config;       ///< SPI configuration structure
  sl_adc_cfg_t adc_config;          ///< ADC configuration structure
  sl_gpio_config_t gpio_config;     ///< GPIO configuration structure
  sl_sh_sdc_config_t sh_sdc_config; ///< SDC configuration structure
} sl_bus_intf_config_t;

/*******************************************************************************
*****************************   PROTOTYPES   **********************************
******************************************************************************/

/***************************************************************************/ /**
* @brief
* Initialization Peripherals of Sensor HUB.
*
* @details
* This function will initialize the Peripherals, based on the user configuration.
* like - I2C/SPI/ADC
*
* @param[in]  -    NULL
* @param[out] -    Return the Sensor Hub bus Initialization status
* @return status 0 if successful, else error code as follow:
*-       \ref SL_STATUS_FAIL (0x0001)- Fail, Peripherals initialization failed 
*-
*       \ref SL_STATUS_OK (0X000)- Success, Peripherals initialization done properly \n
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_init();

/**************************************************************************/ /**
* @brief
* Detect the sensors.
*
* @details
* This function will detect the sensor, based on the user configuration.
* and it will store the scanned sensor ID in the structure.
*
* @param[in] sensor_id_info[] -     Sensor IDs
* @param[in] num_of_sensors   -     Number of sensors given by user
* @param[out] - None
* @return if successful, Return number of sensors scanned
*               else error code
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_detect_sensors(sl_sensor_id_t sensor_id_info[], uint8_t num_of_sensors);

/**************************************************************************/ /**
* @brief
* Delete the specific sensor from the Sensor HUB.
*
* @details
* This function will delete the specific sensor from the sensor list,
* modify the sensor status to invalid, and publish the events to the event task.
*
* @param[in] sensor_id - Sensor ID
* @param[out] - Return the delete sensors status
* @return status 0 if successful, else error code as follow:
*-       \ref SL_STATUS_FAIL (0x0001) - Fail, Delete sensor failed 
*-
*       \ref SL_STATUS_OK (0X000)   - Success, Delete sensor Success \n
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_delete_sensor(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Create a sensor instance in the sensor hub.
*
* @details
* This function creates a sensor instance as per user configuration.It also allocates max sample memory for the configured sensor.
*
* @param[in] sensor_id -    Id of sensor
* @param[out] -    Return the create sensors status
* @return status 0 if successful, else error code as follow:
*-       \ref SL_STATUS_FAIL (0x0001)- Fail, Create sensor instance  failed 
*-
*       \ref SL_STATUS _OK (0X000) - Create sensor instanceSuccess , \n
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_create_sensor(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Start the sensor operation for the given sensor.
*
* @details
* This function can be called after creating a sensor with given sensor ID 
* It does following operations
* - Starts timer for sensor with polling mode.
* - Enable IRQ handle for sensor with interrupt mode.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   Return the Start sensors status
* @return status 0 if successful, else error code as follow:
*-       \ref SL_STATUS_FAIL (0x0001)- Fail, Sensor start failed 
*-
*       \ref SL_STATUS _OK (0X000) - Success ,Sensor start done properly \n
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_start_sensor(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Stop the sensor operation of the given sensor.
*
* @details
* This function does following operations
* - Stop the sensor operations of the given sensor.
* - Based on the sensor mode it will stop the Polling/interrupt mode operations and updates the sensor statutes.
* - Disable IRQ handles of the interrupt mode sensors.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   Return the Stop sensor status
* @return status 0 if successful, else error code as follows:
* -       \ref SL_STATUS_FAIL (0x0001)- Fail, Sensor stop failed 
*-
*       \ref SL_STATUS _OK (0X000) - Success ,Sensor stop done properly
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_stop_sensor(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Post the events to event manager(EM) to be notified to the application
*
* @details
* It waits for mutex till ticks_to_wait and updates event queue if mutex is acquired
*
* @param[in] sensor_id -   id of the  sensor
* @param[in] event -   sensor hub events
* @param[in] dataPtr -   sensor data pointer
* @param[in] ticks_to_wait -   max time to wait for the post
* @param[out] -   None
* @return     -   NULL
*
******************************************************************************/
void sl_si91x_em_post_event(sl_sensor_id_t sensor_id,
                            sl_sensorhub_event_t event,
                            void *dataPtr,
                            TickType_t ticks_to_wait);

/***************************************************************************/ /**
* @brief
* Task to handle the sensor operations
*
* @details
* Sensor Task does following operations
* - Create the OS event and mutex to perform the sensor operations.
* - Sample the Sensor data based on the event flags.
* - Check the events and post the sensor data to the em task based on the sensor data delivery mode.
*
* @param[in]  -   None
* @param[out] -   None
* @return     -   NULL
*
******************************************************************************/
void sl_si91x_sensor_task(void);

/***************************************************************************/ /**
* @brief
* Task to handle the system power operations
*
* @details
* Power state task changes the system from one power save mode to another power save mode like(PS4 to PS2),(PS2toPS4),(Sleep_mode) using Binary semaphore
*
* @param[in]  -   None
* @param[out] -   None
* @return     -   NULL
*
******************************************************************************/
void sl_si91x_power_state_task(void);

/***************************************************************************/ /**
* @brief
* Task to handle the operations of the Event Manager(EM)
*
* @details
* Em task does following operaions
* - Create the osMessageQueue and mutex to perform the event operations.
* - Calls the callback event
* @param[in]  -   None
* @param[out] -   None
* @return     -   NULL
*
******************************************************************************/
void sl_si91x_em_task(void);

/***************************************************************************/ /**
* @brief
* Initialize the I2C Interface based on configuration.
*
* @details
* This function will configure/Initialize I2C Interface based on configuration.
*
* @param[in]  -   None
* @param[out] -   None
* @return I2C Initializtion status
*
******************************************************************************/
int32_t sli_si91x_i2c_init(void);

/***************************************************************************/ /**
* @brief
* Initialize SPI Interface based on configuration.
*
* @details
* This function will configure/Initialize SPI Interface based on configuration.
*
* @param[in]  -   None
* @param[out] -   None
* @return SPI Initializtion status.
*
******************************************************************************/
int32_t sli_si91x_spi_init(void);

/***************************************************************************/ /**
* @brief
* Scan the I2C sensors.
*
* @details
* This function will scan the I2C sensors based on the sensor address.
*
* @param[in] address -   Address of sensor
* @param[out] -   None
* @return status 0 if successful, 
*          else it will wait for the sensor response.
*
******************************************************************************/
int32_t sli_si91x_i2c_sensors_scan(uint16_t address);

/***************************************************************************/ /**
* @brief
* to get sensor implementation.
*
* @details
* This function will get the sensor implementation of the sensor based on sensor ID.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   None
* @return if successful, returns the Sensor implementation structure
*         else returns an error code.
*
******************************************************************************/
sl_sensor_impl_type_t *sli_si91x_get_sensor_implementation(int32_t sensor_id);

/***************************************************************************/ /**
* @brief
* Create the sensor list index.
*
* @details
* This function will Create the sensor list index based on the sensor status
* For the maximum sensors available in the sensor hub
*
* @param[in]  -   None
* @param[out] -   Returns the Sensor ID from the implementation struct
* @return  returns the sensor index in sensor_list
*
******************************************************************************/
int32_t sli_si91x_create_sensor_list_index();

/***************************************************************************/ /**
* @brief
* Get the sensor index for the sensor list.
*
* @details
* This function will retrieve the sensor index from the sensor list based on 
* the sensor status and sensor ID for the maximum number of sensors 
* available in the sensor hub.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   None
* @return if successful, returns the sensor index
*         else returns SL_SH_SENSOR_INDEX_NOT_FOUND(0XFF).
*
******************************************************************************/
uint32_t sli_si91x_get_sensor_index(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Delete the sensor index for the sensor list.
*
* @details
* This function will delete the sensor from the sensor list based on 
* The sensor ID for the maximum number of sensors available in the sensor hub.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   None
* @return if successful, returns the sensor index
*         else returns error code SL_SH_SENSOR_INDEX_NOT_FOUND(0XFF).
*
******************************************************************************/
uint32_t sli_si91x_delete_sensor_list_index(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* get the sensor info from the sensor configuration structure.
*
* @details
* This function will retrieve sensor data from the sensor configuration structure 
* to update the sensor list configuration structure for the maximum number
* of sensors available in the sensor hub.
*
* @param[in] sensor_id -   Id of sensor
* @param[out] -   None
* @return if successful, returns the sensor information.
*         else returns NULL.
*
******************************************************************************/
sl_sensor_info_t *sli_si91x_get_sensor_info(sl_sensor_id_t sensor_id);

/***************************************************************************/ /**
* @brief
* Call back function to the application.
*
* @details
* This function will update the callback function event and acknowledgment.
*
* @param[in] cb_event  -   Pointer to the callback event
* @param[in] cb_ack    -   Pointer to callback acknowledge to the application
* @param[out] -   None
* @return     -   If successful returns SL_STATUS_OK else returns error code
*
******************************************************************************/
sl_status_t sl_si91x_sensorhub_notify_cb_register(sl_sensor_signalEvent_t cb_event, sl_sensor_id_t *cb_ack);

/***************************************************************************/ /**
* @brief
* Sensor OS timer callback function.
*
* @details
* This function will set the event flag bits based on the sensor sampling intervals.
* In the polling mode call the timer call-back function.
*
* @param[in] xTimer   -   Timer handle
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sl_si91x_sensors_timer_cb(TimerHandle_t xTimer);

/***************************************************************************/ /**
* @brief
* Configuring the different types of NPSS GPIO interrupts in the Sensor HUB.
*
* @details
* This function configures the NPSS gpios and enables the interrupt mode for the gpios. 
*
* @param[in] gpio_pin   -   NPSS gpio pin number
* @param[in]    -   NPSS gpio interrupt type
* @param[out]   -   None
* @return       -   If successful returns SL_STATUS_OK else returns error code
*
******************************************************************************/
sl_status_t sl_si91x_gpio_interrupt_config(uint16_t gpio_pin, sl_gpio_intr_type_t intr_type);

/***************************************************************************/ /**
* @brief
* Enable and set the priority of NPSS GPIO interrupt.
*
* @details
* This function configures and sets the priority of the NPSS GPIO interrupt.
* GPIO interrupt priority is (configMAX_SYSCALL_INTERRUPT_PRIORITY - 1)
*
* @param[in] gpio_pin   -   NPSS gpio pin number
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sl_si91x_gpio_interrupt_start(uint16_t gpio_pin);

/***************************************************************************/ /**
* @brief
* Mask and Disable the NPSS GPIO interrupt.
*
* @details
* This function masks and disables the IRQ handler of the NPSS GPIO interrupt.
*
* @param[in] gpio_pin   -   NPSS gpio pin number
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sl_si91x_gpio_interrupt_stop(uint16_t gpio_pin);

/***************************************************************************/ /**
* @brief
* Start the sensor hub Tasks.
*
* @details
* This Starts the sensor hub Tasks.
*
* @param[in]    -   None
* @param[out]   -   None
* @return       -   If succesfull returns SL_STATUS_OK else returns error code
*
******************************************************************************/
sl_status_t sl_si91x_sensor_hub_start(void);

/***************************************************************************/ /**
* @brief
* set the alarm interrupt time.
*
* @details
* This function will set the alarm interrupt based on the periodic time.
*
* @param[in] interval   -   interval time
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sli_si91x_set_alarm_intr_time(uint16_t interval);

/***************************************************************************/ /**
* @brief
* initialize the Alarm block.
*
* @details
* This function will initialize the Alarm block.
*
* @param[in]    -   None
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sli_si91x_init_m4alarm_config(void);

/***************************************************************************/ /**
* @brief
* Configure the wake-up source for the system.
*
* @details
* This function will configure the wake-up source to the system.
*
* @param[in] sleep_time  -   Sleep time for the sensor hub
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sli_si91x_config_wakeup_source(uint16_t sleep_time);

/***************************************************************************/ /**
* @brief
* Configures sleep/wakeup sources for the system.
*
* @details
* This function will configure sleep/wakeup sources.
*
* @param[in] sh_sleep_time  -   Sleep time for the sensor hub, in ADC PS-1 no parameters
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
#ifdef SL_SH_PS1_STATE
void sli_si91x_sleep_wakeup(void);
#else
void sli_si91x_sleep_wakeup(uint16_t sh_sleep_time);
#endif
/***************************************************************************/ /**
* @brief
* Change the system status from PS4 to PS2.
*
* @details
* This function will change the system status from PS4 to PS2.
*
* @param[in]    -   None
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sli_si91x_sensorhub_ps4tops2_state(void);

/***************************************************************************/ /**
* @brief
* Change the system status from PS2 to PS4.
*
* @details
* This function will change the system status from PS2 to PS4.
*
* @param[in]    -   None
* @param[out]   -   None
* @return       -   NULL
*
******************************************************************************/
void sli_si91x_sensorhub_ps2tops4_state(void);

/***************************************************************************/ /**
* @brief
* Initialize ADC Interface based on configuration.
*
* @details
* This function will configure/Initialize ADC Interface based on configuration.
*
* @param[in]   -   None
* @return      error code
*              \ref SL_STATUS_FAIL (0x0001)- Fail ,
*              \ref SL_STATUS_OK (0X000)- Success
*
******************************************************************************/
sl_status_t sli_si91x_adc_init(void);

/***************************************************************************/ /**
* @brief
* Initialize and configure the systic timer for the RTOS.
*
* @details
* Set up the systic timer to generate the tick interrupts at the required frequency.
*
* @param[in]    -   None
* @param[out]   -   None
* @return Initialize status to the application.
*
******************************************************************************/
void vPortSetupTimerInterrupt(void);

/*=============================================================================*/
/**
 * @fn         void ARM_I2C_SignalEvent(uint32_t event)
 * @brief      I2C event handler
 * @param[in] event - I2C transmit and receive events
 * @param[out]    -   None
 * @return     None
 */
/*=============================================================================*/
void ARM_I2C_SignalEvent(uint32_t event);

/*=============================================================================*/
/**
 *  @fn          sl_adc_cfg_t *sl_si91x_fetch_adc_bus_intf_info(void)
 *  @brief       Fetch ADC bus interface information. This can be used by lower level layers
 *  @return      Pointer to ADC configuration structure
 */
/*=============================================================================*/
sl_adc_cfg_t *sl_si91x_fetch_adc_bus_intf_info(void);

/*=============================================================================*/
/**
 * @fn    void sl_si91x_adc_callback(uint8_t channel_no, uint8_t event)
 * @brief ADC callback from RSI_ADC_InterruptHandler
 *
 * @param[in] channel_no - respective channel number
 * @param[in] event      - callback event (ADC_STATIC_MODE_CALLBACK, 
 *                         ADC_THRSHOLD_CALLBACK, INTERNAL_DMA, FIFO_MODE_EVENT)
 */
/*=============================================================================*/
void sl_si91x_adc_callback(uint8_t channel_no, uint8_t event);

/*=============================================================================*/
/**
 *  @fn          uint8_t sli_si91x_sdc_init(void)
 *  @brief       Initialize the sdc Interface based on the configuration.
 *  @param[in]   None
 *  @return      status 0 if successful,
 *               else error code
 *               \ref SL_STATUS_FAIL (0x0001)- Fail ,
 *               \ref SL_STATUS_OK (0X000)- Success,
 */
/*=============================================================================*/
sl_status_t sli_si91x_sdc_init(void);

/**************************************************************************/ /**
 *  @fn          void sli_config_sdc_params(sl_sdc_config_t * sdc_config)
 *  @brief       Initialize the sdc Interface based on the configuration.
 *  @param[in]   None
 *  @return      status 0 if successful,
 *               else error code
 *               \ref SL_STATUS_FAIL (0x0001)- Fail ,
 *               \ref SL_STATUS_OK (0X000)- Success,
*******************************************************************************/
void sli_config_sdc_params(sl_drv_sdc_config_t *sdc_config_st_p);
#endif

// ******** THE REST OF THE FILE IS DOCUMENTATION ONLY !***********************
/// @addtogroup SENSOR-HUB Sensor Hub
/// @{
///
///   @details
///
///
///   @n @section SENSOR-HUB_Intro Introduction
///
///    * Sensor Hub products are primarily intended to address consumer, industrial, and medical applications that require wireless connectivity, extremely low power, and high performance for sensor fusion algorithms. The MCU core, wireless connectivity, and peripherals are identical to the SI917 CCP Radio board.
///    * Sensor Hub functions as a sensor management system, facilitating hardware abstraction layer, peripheral drivers, and sensor driver layer integration to collect and distribute desired sensor data.
///    * It enables users to collect sensor data based on time interval or number of samples or when a specific data requirement are met.
///    * Sensor Hub serves as a framework that can be seamlessly integrated into any application requiring sensor management.
///    * The Sensor HUB works with sensors as per configurations provided by the application and notifies the necessary events throughout the application.
///    * The configuration for the sensors must be provided through the sensor hub config file on which the sensor hub should act.
///    * Sensor Hub relies on FreeRTOS using CMSIS RTOS version 2 wrapper.
///
///
///   @n @section SENSOR-HUB_Config Configuration
///
///    * Sensor Hub has 2 Sensor Mode:
///    * **SL_SH_POLLING_MODE**: This mode is Timer based.
///    * **SL_SH_INTERRUPT_MODE**: This mode is NPSS Button 0 GPIO Interrupt based.
///    * There are 3 types of data_deliver.mode in Polling Sensor Mode and they are **SL_SH_THRESHOLD**, **SL_SH_TIMEOUT** and **SL_SH_NUM_OF_SAMPLES**.
///    * **SL_SH_NO_DATA** data_deliver.mode is used when Interrupt Sensor Mode is selected.
///    * If the user wants a value that sets a limit or boundary, above which the sensor data should be shown then SL_SH_THRESHOLD mode should be chosen
///    * SL_SH_TIMEOUT mode is used when user wants to get the data at some intervals of time for some sampling time
///    * SL_SH_NUM_OF_SAMPLES mode is used when user wants to get the particular number of sensor data 
///    * SL_SH_NO_DATA mode is used when .
///    * Here data_deliver.timeout is the time for which the sensor should keep collecting the data for.
///    * sampling_interval is the the amount of time between two sensor data read is sampled or collected.
///    * sampling_intr_req_pin is the GPIO pin for sampling the sensor data
///
///    * Configure the number of sensors info in the **\sensors\inc\sensors_config.h** file
///    ```C
///    #define SL_MAX_NUM_SENSORS              5   // Maximum sensors present in the system
///     ```
///    * Modes: Using the configuration structure, one can configure the following parameters in the ***sensorhub_config.c*** file:
///
///     * For **POLLING Sensor Mode** configure the below parameters:
///    ```C
///    .sensor_mode                = SL_SH_POLLING_MODE,
///    .sampling_interval          = 100,
///    ```
///      * If sensor_mode is selected as ***SL_SH_POLLING_MODE***, then data_deliver.mode should be configured as **one** of the following for a sensor configuration structure:
///        * For **TIMEOUT Data Mode** configure the below parameters:
///    ```C
///    .data_deliver.mode          = SL_SH_TIMEOUT,
///    .data_deliver.timeout       = 1000,
///    ```
///        * For **THRESHOLD Data Mode** configure the below parameters:
///    ```C
///    .data_deliver.mode          = SL_SH_THRESHOLD,
///    .data_deliver.threshold     = 1000,
///    ```
///        * For **SAMPLING Data Mode** configure the below parameters:
///    ```C
///    .data_deliver.mode          = SL_SH_NUM_OF_SAMPLES,
///    .data_deliver.numOfSamples  = 5,
///    ```
///     * For **INTERRUPT Sensor Mode** configure the below parameters:
///    ```C
///    .sensor_mode                = SL_SH_INTERRUPT_MODE,
///    .sampling_intr_req_pin      = BUTTON_0_GPIO_PIN,
///    .sensor_intr_type           = SL_SH_FALL_EDGE,
///    .data_deliver.data_mode     = SL_SH_NO_DATA_MODE,
///    ```
///    * To configure the PS2, please update the below macro in the preprocessor settings:
///    ```C
///    SL_SENSORHUB_POWERSAVE=1
///    Enabling this macro will move the application from PS4 state to PS2 state. In PS2 state the sensor data will be sampled and collected.
///    ```
///
///    * To configure the power states to PS4 sleep or PS2 Sleep, please update the defines in ***\gecko_sdk_4.3.2\util\third_party\freertos\kernel\include\FreeRTOS.h** file as below:
///    ```C
///    #ifndef configUSE_TICKLESS_IDLE
///    #define configUSE_TICKLESS_IDLE 1           // 1 is to Enable the tickless Idle mode
///    #endif
///
///    #ifndef configPRE_SLEEP_PROCESSING
///    #define configPRE_SLEEP_PROCESSING(x) sli_si91x_sleep_wakeup(x)               // Here x is idle time,
///    #endif
///
///    // Configure the sleep time by using the below macro.
///    // If the number of Ideal task ticks exceeds this value, the system is allowed to sleep.
///    #ifndef configEXPECTED_IDLE_TIME_BEFORE_SLEEP
///       #define configEXPECTED_IDLE_TIME_BEFORE_SLEEP    70
///    #endif
///    ```
///    ***Note***:
///    * By using above sleep configuration, sensor hub is going to sleep by using the idle task and idle time.
///    * If the Ideal time exceeds the expected sleep time value, the system is allowed to sleep.
///    * The above idle time is fed to the Alarm timer, which we are using as a wake-up source.
///
///
///    **ADC Configurations**:
///    Configure only below parameters for ADC to change its mode from FIFO to STATIC and vice versa
///
///     * For ADC FIFO mode, configure as shown below:
///    ```C
///    .adc_config.adc_cfg.operation_mode        = SL_ADC_FIFO_MODE,
///    .adc_config.adc_ch_cfg.sampling_rate[0]   = SL_SH_ADC_SAMPLING_RATE, // Use 100 for FIFO Mode
///    ```
///     * For ADC Static mode, configure as shown below:
///    ```C
///    .adc_config.adc_cfg.operation_mode        = SL_ADC_STATIC_MODE,
///    .adc_config.adc_ch_cfg.sampling_rate[0]   = SL_SH_ADC_SAMPLING_RATE, // Use 1000 for Static Mode
///    ```
///     * To configure the PS1 power state from PS2 State, please update the below macro in the preprocessor settings:
///    ```C
///    SL_SH_ADC_PS1=1
///     Enabling this macro will move the core from PS2 Active state to PS1 state
///    ```
///      * Please update the defines in ***\gecko_sdk_4.3.2\util\third_party\freertos\kernel\include\FreeRTOS.h** file as below:
///    ```C
///    #ifndef configUSE_TICKLESS_IDLE
///    #define configUSE_TICKLESS_IDLE 1           // 1 is to Enable the tickless Idle mode
///    #endif
///
///    #ifndef configPRE_SLEEP_PROCESSING
///    #define configPRE_SLEEP_PROCESSING(x) sli_si91x_sleep_wakeup(x)               // Here x is idle time,
///    #endif
///       ```
///    ***Note***:
///      * The PS1 state transition only applies to ADC FIFO Mode. Before entering this mode, kindly turn off any other sensors.
///
///
///
///   @n @section SENSOR-HUB_Usage Usage
///
///   Sensorhub provides two apis which user can use for intergrating into any application
///   - @ref sl_si91x_sensorhub_app_task(void);
///   - @ref sl_si91x_sensor_event_handler(uint8_t sensor_id, uint8_t event);
///
///   @ref sl_si91x_sensorhub_app_task(void): initialises and starts sensor data collection. it achieves this by calling the following apis
///
///   @ref sl_si91x_sensorhub_notify_cb_register(sl_sensor_signalEvent_t cb_event, sl_sensor_id_t *cb_ack): links the event handler provided by the user as a callback function in the event task
///
///   @ref sl_si91x_sensorhub_init(): initializes the peripherals I2C, SPI, ADC, SDC
///
///   @ref sl_si91x_sensorhub_detect_sensors(sl_sensor_id_t *sensor_id_info, uint8_t num_of_sensors): scans the i2c sensors provided in the sensorhub_config.c and returns the number of these sensors that are currently connected
///
///   @ref sl_si91x_sensorhub_create_sensor(sl_sensor_id_t sensor_id): Initializes the sensor by calling the init function of the sensor provided by the user in the respective HAL, Assigs memory to it based on the data delivery mode, Creates a timer for this sensor if required
///
///   @ref sl_si91x_sensor_hub_start(): initializes the sensor task, event task and power task
///
///   @ref sl_si91x_sensorhub_start_sensor(sl_sensor_id_t sensor_id): starts the timers of the sensors created in create sensor api
///
///   @ref sl_si91x_sensor_event_handler(uint8_t sensor_id, uint8_t event) is called by the event task after sensor data is collected ,in the sensorhub appilcation it prints the data based on the sensor id and uploads it to the cloud
///
/// @} end group SENSOR-HUB ********************************************************/