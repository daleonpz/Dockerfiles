/**
 ****************************************************************************************
 *
 * @file main.c
 *
 * @brief BLE peripheral application
 *
 * Copyright (C) 2015-2018 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
/* Standard includes. */
#include <string.h>
#include <stdbool.h>

#include "osal.h"
#include "resmgmt.h"
#include "ad_ble.h"
#include "ad_nvms.h"
#include "ble_mgr.h"
#include "hw_gpio.h"
#include "sys_clock_mgr.h"
#include "sys_power_mgr.h"
#include "sys_watchdog.h"
#include "platform_devices.h"
#include "debug_log.h"
#include "SEGGER_RTT.h"
#include "ad_gpadc.h"
#include "led.h"
#include "tasks.h"

/* Task priorities */
#define mainBLE_PERIPHERAL_TASK_PRIORITY              ( OS_TASK_PRIORITY_NORMAL )

#if dg_configUSE_WDOG
INITIALISED_PRIVILEGED_DATA int8_t idle_task_wdog_id = -1;
#endif

static const gpio_config gpio_cfg[] = {
HW_GPIO_PINCONFIG(ADC_PORT, ADC_PIN, INPUT, ADC, true),
//S1 = H, S2 = H, S3 = H => Z = VBAT
        HW_GPIO_PINCONFIG(S1_PORT, S1_PIN, OUTPUT_PUSH_PULL, GPIO, true),
        HW_GPIO_PINCONFIG(S2_PORT, S2_PIN, OUTPUT_PUSH_PULL, GPIO, true),
        HW_GPIO_PINCONFIG(S3_PORT, S3_PIN, OUTPUT_PUSH_PULL, GPIO, true),
        HW_GPIO_PINCONFIG(SWITCH_DISABLE_PORT, SWITCH_DISABLE_PIN, OUTPUT_PUSH_PULL, GPIO, true),
        HW_GPIO_PINCONFIG(HW_GPIO_PORT_3, HW_GPIO_PIN_2, INPUT, I2C_SDA, true), // I2C SDA
        HW_GPIO_PINCONFIG(HW_GPIO_PORT_1, HW_GPIO_PIN_5, INPUT, I2C_SCL, true), // I2C SCL
        HW_GPIO_PINCONFIG(HW_GPIO_PORT_3, HW_GPIO_PIN_1, INPUT, GPIO, false), // Accel Int 1
        HW_GPIO_PINCONFIG(HW_GPIO_PORT_3, HW_GPIO_PIN_5, INPUT, GPIO, false), // Accel Int 2
        HW_GPIO_PINCONFIG_END // important!!!
        };

/*
 * Perform any application specific hardware configuration.  The clocks,
 * memory, etc. are configured before main() is called.
 */
static void prvSetupHardware(void);
/*
 * Task functions .
 */
void ble_peripheral_task(void *params);

static OS_TASK handle = NULL;

/**
 * @brief System Initialization and creation of the BLE task
 */
static void system_init(void *pvParameters)
{
#if defined CONFIG_RETARGET
        extern void retarget_init(void);
#endif

        /* Prepare clocks. Note: cm_cpu_clk_set() and cm_sys_clk_set() can be called only from a
         * task since they will suspend the task until the XTAL16M has settled and, maybe, the PLL
         * is locked.
         */
        cm_sys_clk_init(sysclk_XTAL16M);
        cm_apb_set_clock_divider(apb_div1);
        cm_ahb_set_clock_divider(ahb_div1);
        cm_lp_clk_init();

        /*
         * Initialize platform watchdog
         */
        sys_watchdog_init();

#if dg_configUSE_WDOG
        // Register the Idle task first.
        idle_task_wdog_id = sys_watchdog_register(false);
        ASSERT_WARNING(idle_task_wdog_id != -1);
        sys_watchdog_configure_idle_id(idle_task_wdog_id);
#endif

#if defined CONFIG_RTT
        SEGGER_RTT_Init();
        debug_log_init();
#endif

        /* Set system clock */
        cm_sys_clk_set(sysclk_XTAL16M);

        /* Prepare the hardware to run this demo. */
        prvSetupHardware();

        /* init resources */
        resource_init();

        GPADC_INIT();

        ad_nvms_init();

        /* Set the desired sleep mode. */
        pm_set_wakeup_mode(true);
        pm_set_sleep_mode(pm_mode_extended_sleep);

#if defined CONFIG_RETARGET
        retarget_init();
#endif

        /* Initialize BLE Manager */
        ble_mgr_init();

        /* Start the BLE Peripheral application task. */
        OS_TASK_CREATE("BLE Peripheral", /* The text name assigned to the task, for
         debug only; not used by the kernel. */
        ble_peripheral_task, /* The function that implements the task. */
        NULL, /* The parameter passed to the task. */
#if defined CONFIG_RETARGET
                1024, /* The number of bytes to allocate to the
                 stack of the task. */
#else
                200 * OS_STACK_WORD_SIZE, /* The number of bytes to allocate to the
                 stack of the task. */
#endif
                mainBLE_PERIPHERAL_TASK_PRIORITY,/* The priority assigned to the task. */
                ble_peripheral_handle); /* The task handle. */
        OS_ASSERT(ble_peripheral_handle);

        /* the work of the SysInit task is done */
        OS_TASK_DELETE(OS_GET_CURRENT_TASK());
}
/*-----------------------------------------------------------*/

/**
 * @brief Basic initialization and creation of the system initialization task.
 */
int main(void)
{
        OS_BASE_TYPE status;

        cm_clk_init_low_level(); /* Basic clock initializations. */

        /* Start SysInit task. */
        status = OS_TASK_CREATE("SysInit", /* The text name assigned to the task, for
         debug only; not used by the kernel. */
        system_init, /* The System Initialization task. */
        ( void * ) 0, /* The parameter passed to the task. */
        1024, /* The number of bytes to allocate to the
         stack of the task. */
        OS_TASK_PRIORITY_HIGHEST, /* The priority assigned to the task. */
        handle); /* The task handle */
        OS_ASSERT(status == OS_TASK_CREATE_SUCCESS);

        /* Start the tasks and timer running. */
        vTaskStartScheduler();

        /* If all is well, the scheduler will now be running, and the following
         line will never be reached.  If the following line does execute, then
         there was insufficient FreeRTOS heap memory available for the idle and/or
         timer tasks     to be created.  See the memory management section on the
         FreeRTOS web site for more details. */
        for (;;)
                ;
}

static void periph_init()
{
        // DOUT_MCU
        //hw_gpio_configure_pin_power(SWITCH_DISABLE_PORT, SWITCH_DISABLE_PIN, HW_GPIO_POWER_V33);
        //hw_gpio_configure_pin(SWITCH_DISABLE_PORT, SWITCH_DISABLE_PIN, HW_GPIO_MODE_OUTPUT, HW_GPIO_FUNC_GPIO, true);
        //init_led_after_wakeup();
        hw_gpio_configure(gpio_cfg);

        /* I2C_1V8 */
        hw_gpio_configure_pin_power(HW_GPIO_PORT_3, HW_GPIO_PIN_2, HW_GPIO_POWER_VDD1V8P);
        hw_gpio_configure_pin_power(HW_GPIO_PORT_1, HW_GPIO_PIN_5, HW_GPIO_POWER_VDD1V8P);

        /* ACCEL INT */
        hw_gpio_configure_pin_power(HW_GPIO_PORT_3, HW_GPIO_PIN_1, HW_GPIO_POWER_VDD1V8P);
        hw_gpio_configure_pin_power(HW_GPIO_PORT_3, HW_GPIO_PIN_5, HW_GPIO_POWER_VDD1V8P);
        //init_led_after_wakeup();
}

/**
 * \brief Initialize the peripherals domain after power-up.
 *
 */

static void prvSetupHardware(void)
{
        /* Init hardware */
        pm_system_init(periph_init);
}
/**
 * @brief Malloc fail hook
 */
void vApplicationMallocFailedHook(void)
{
        /* vApplicationMallocFailedHook() will only be called if
         configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
         function that will get called if a call to OS_MALLOC() fails.
         OS_MALLOC() is called internally by the kernel whenever a task, queue,
         timer or semaphore is created.  It is also called by various parts of the
         demo application.  If heap_1.c or heap_2.c are used, then the size of the
         heap available to OS_MALLOC() is defined by configTOTAL_HEAP_SIZE in
         FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
         to query the size of free heap space that remains (although it does not
         provide information on how the remaining heap might be fragmented). */
        taskDISABLE_INTERRUPTS()
        ;
        for (;;)
                ;
}

/**
 * @brief Application idle task hook
 */
void vApplicationIdleHook(void)
{
        /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
         to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
         task. It is essential that code added to this hook function never attempts
         to block in any way (for example, call OS_QUEUE_GET() with a block time
         specified, or call OS_DELAY()).  If the application makes use of the
         OS_TASK_DELETE() API function (as this demo application does) then it is also
         important that vApplicationIdleHook() is permitted to return to its calling
         function, because it is the responsibility of the idle task to clean up
         memory allocated by the kernel to any task that has since been deleted. */

#if dg_configUSE_WDOG
        sys_watchdog_notify(idle_task_wdog_id);
#endif
}

/**
 * @brief Application stack overflow hook
 */
void vApplicationStackOverflowHook( OS_TASK pxTask, char *pcTaskName)
{
        (void)pcTaskName;
        (void)pxTask;

        /* Run time stack overflow checking is performed if
         configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
         function is called if a stack overflow is detected. */
        taskDISABLE_INTERRUPTS()
        ;
        for (;;)
                ;
}

/**
 * @brief Application tick hook
 */
void vApplicationTickHook(void)
{

        OS_POISON_AREA_CHECK( OS_POISON_ON_ERROR_HALT, result );

}
