/**
 \addtogroup BSP
\{
\addtogroup CONFIG
\{
\addtogroup CUSTOM
\{
*/

/**
 ****************************************************************************************
 *
 * @file custom_config_qspi.h
 *
 * @brief Board Support Package. User Configuration file for cached QSPI mode.
 *
 * Copyright (C) 2015-2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */

#ifndef CUSTOM_CONFIG_QSPI_H_
#define CUSTOM_CONFIG_QSPI_H_

#include "bsp_definitions.h"
//#include "hw_gpio.h"

#define CONFIG_USE_BLE
#undef CONFIG_USE_FTDF

#define CONFIG_RTT

#define configTIMER_TASK_STACK_DEPTH         200

#define USE_MY_CUSTOM_PARTITION_TABLE

#define REV1    1
#define REV2    2

#define dg_configTESTMODE_MEASURE_SLEEP_CURRENT (0)

#define HARDWARE_REV    REV1

#if (HARDWARE_REV == REV1)

#define S1_PORT                                 HW_GPIO_PORT_3
#define S1_PIN                                  HW_GPIO_PIN_0
#define S2_PORT                                 HW_GPIO_PORT_4
#define S2_PIN                                  HW_GPIO_PIN_7
#define S3_PORT                                 HW_GPIO_PORT_2
#define S3_PIN                                  HW_GPIO_PIN_3

#define SWITCH_DISABLE_PORT                     HW_GPIO_PORT_4
#define SWITCH_DISABLE_PIN                      HW_GPIO_PIN_3

#define ADC_PORT                                HW_GPIO_PORT_1
#define ADC_PIN                                 HW_GPIO_PIN_2

#endif

#define dg_configUSE_LP_CLK                     LP_CLK_32768
#define dg_configEXEC_MODE                      MODE_IS_CACHED
#define dg_configCODE_LOCATION                  NON_VOLATILE_IS_FLASH
#define dg_configEXT_CRYSTAL_FREQ               EXT_CRYSTAL_IS_16M

#define dg_configIMAGE_SETUP                    DEVELOPMENT_MODE //PRODUCTION_MODE
#define dg_configEMULATE_OTP_COPY               (0)

#define dg_configUSER_CAN_USE_TIMER1            (0)

#define dg_configUSE_WDOG                       (1)
#define dg_configWDOG_MAX_TASKS_CNT             (8)

#define dg_configFLASH_CONNECTED_TO             (FLASH_CONNECTED_TO_1V8)
#define dg_configFLASH_POWER_DOWN               (1)

#define dg_configPOWER_1V8_ACTIVE               (1)
#define dg_configPOWER_1V8_SLEEP                (1)
#define dg_configPOWER_1V8P                     (1)

#define dg_configBATTERY_TYPE                   (BATTERY_TYPE_LIMN2O4)
#define dg_configBATTERY_CHARGE_CURRENT         2       // 30mA
#define dg_configBATTERY_PRECHARGE_CURRENT      20      // 2.1mA
#define dg_configBATTERY_CHARGE_NTC             1       // disabled

#define dg_configUSE_USB                        0
#define dg_configUSE_USB_CHARGER                0
#define dg_configALLOW_CHARGING_NOT_ENUM        1

#define dg_configUSE_ProDK                      (0)

#define dg_configUSE_SW_CURSOR                  (0)

#define dg_configCACHEABLE_QSPI_AREA_LEN        (NVMS_PARAM_PART_start - MEMORY_QSPIF_BASE)

#define dg_configUSE_HW_AES_HASH                (1)

/*************************************************************************************************\
 * Memory specific config
 */
#define dg_configQSPI_CACHED_OPTIMAL_RETRAM_0_SIZE_AE   ( 64 * 1024)
#define dg_configQSPI_CACHED_RAM_SIZE_AE                ( 32 * 1024)
#define dg_configQSPI_CACHED_RETRAM_0_SIZE_AE           ( 96 * 1024)

#define dg_configQSPI_CACHED_OPTIMAL_RETRAM_0_SIZE_BB   ( 64 * 1024)
#define dg_configQSPI_CACHED_RAM_SIZE_BB                ( 32 * 1024)
#define dg_configQSPI_CACHED_RETRAM_0_SIZE_BB           ( 96 * 1024)

/*************************************************************************************************\
 * FreeRTOS specific config
 */
#define OS_FREERTOS                              /* Define this to use FreeRTOS */
#define configTOTAL_HEAP_SIZE                    32000   /* This is the FreeRTOS Total Heap Size */
#define configTIMER_TASK_STACK_DEPTH             200


#define defaultBLE_ADVERTISE_INTERVAL_MAX       (BLE_ADV_INTERVAL_FROM_MS(8000))
#define defaultBLE_ADVERTISE_INTERVAL_MIN       (BLE_ADV_INTERVAL_FROM_MS(7000))
/*************************************************************************************************\
 * Peripheral specific config
 */
#define dg_configFLASH_ADAPTER                  (1)
#define dg_configNVMS_ADAPTER                   (1)
#define dg_configNVMS_VES                       (1)
#define dg_configNVPARAM_ADAPTER                (1)
#define dg_configGPADC_ADAPTER                  (1)
#define dg_configI2C_ADAPTER                    (1)
#define dg_configUSE_HW_I2C                     (1)
#define dg_configUSE_HW_GPADC                   (1)
#define dg_configUSE_HW_GPIO                    (1)

/*************************************************************************************************\
 * BLE device config
 */
#define dg_configBLE_CENTRAL                    (0)
#define dg_configBLE_GATT_CLIENT                (0)
#define dg_configBLE_OBSERVER                   (0)
#define dg_configBLE_BROADCASTER                (0)
#define dg_configBLE_L2CAP_COC                  (0)

#define defaultBLE_MAX_CONNECTIONS              (1)

#define dg_configLATCH_WKUP_SOURCE              (1)

/* Include bsp default values */
#include "bsp_defaults.h"
/* Include memory layout */
#include "bsp_memory_layout.h"

#endif /* CUSTOM_CONFIG_QSPI_H_ */

/**
\}
\}
\}
*/
