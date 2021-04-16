#include "digital_roller.h"
#include "sbt_storage.h"

digital_roller_dev roller;

PRIVILEGED_DATA OS_TIMER settling_time_timer;

PRIVILEGED_DATA OS_TIMER ble_adv_transInt_timer;

static void change_timer_period(OS_TIMER timer, uint16_t period)
{
        uint8_t is_timer_active = OS_TIMER_IS_ACTIVE(timer);

        OS_TIMER_CHANGE_PERIOD(timer, OS_MS_2_TICKS(period * 1000),
                OS_TIMER_FOREVER);

        if (is_timer_active == 0) {
                OS_TIMER_STOP(timer, OS_TIMER_FOREVER);
        }
}

static void roller_set_highResMeasInt(uint16_t measInt)
{
        OS_TIMER_STOP(ble_adv_transInt_timer, OS_TIMER_FOREVER);
        roller.config.highRes_measInt = measInt;
        if (roller_get_resolutionState() == HIGH_RESOLUTION) {
                OS_TASK_NOTIFY(measurement_task_handle, CHANGE_MEAS_TIMER_PERIOD,
                        OS_NOTIFY_SET_BITS);
        }
}

uint16_t roller_get_highResMeasInt()
{
        return roller.config.highRes_measInt;
}

static void roller_set_lowResMeasInt(uint16_t measInt)
{
        roller.config.lowRes_measInt = measInt;
        if (roller_get_resolutionState() == LOW_RESOLUTION) {
                OS_TASK_NOTIFY(measurement_task_handle, CHANGE_MEAS_TIMER_PERIOD,
                        OS_NOTIFY_SET_BITS);
        }
}

uint16_t roller_get_lowResMeasInt()
{
        return roller.config.lowRes_measInt;
}

static void roller_set_settlingTime(uint16_t settlingTime)
{
        roller.config.settling_time = settlingTime;
        debug_log("Changing period of settling timer");
        change_timer_period(settling_time_timer, settlingTime);
}

uint16_t roller_get_settlingTime()
{
        return roller.config.settling_time;
}

static void roller_set_tempThreshold(uint16_t tempThreshold)
{
        roller.config.temp_threshold = tempThreshold;
}

uint16_t roller_get_tempThreshold()
{
        return roller.config.temp_threshold;
}

static void roller_set_resolutionState(roller_states_t resolution)
{
        roller.config.resolution_state = resolution;

        resolution == HIGH_RESOLUTION ? debug_log("Switching to high resolution mode.") : debug_log("Switching to low resolution mode");

        if (resolution == HIGH_RESOLUTION) {
                OS_TIMER_START(settling_time_timer, OS_TIMER_FOREVER);
        }
        OS_TASK_NOTIFY(measurement_task_handle, CHANGE_MEAS_TIMER_PERIOD,
                OS_NOTIFY_SET_BITS);
}

roller_states_t roller_get_resolutionState()
{
        return roller.config.resolution_state;
}

static void roller_set_transInt(uint16_t transInt)
{
        roller.config.trans_int = transInt;

        change_timer_period(ble_adv_transInt_timer, transInt);
}

uint16_t roller_get_transInt()
{
        return roller.config.trans_int;
}

static void settling_timer_exceeded()
{
        debug_log("Settling time exceeded");
        roller_set_resolutionState(LOW_RESOLUTION);
        change_timer_period(settling_time_timer, 300);
}

static void ble_adv_transInt_exceeded()
{
        debug_log("Trans Int Exceeded");
        start_advertising();
}

static bool sbt_has_pending_data()
{
        if (sbt_is_storage_empty() == true && sbt_msg_queue_get_cnt() == 0) {
                return false;
        }
        return true;
}

void start_ble_adv_transInt_timer()
{
        if (!sbt_has_pending_data() && roller_get_resolutionState() == LOW_RESOLUTION && !OS_TIMER_IS_ACTIVE(ble_adv_transInt_timer)) {
                debug_log(
                        "Starting bluetooth adv transInt timer");
                OS_TIMER_START(ble_adv_transInt_timer, OS_TIMER_FOREVER);
        }
        start_advertising();
}

void start_advertising()
{
        if (!sbt_has_pending_data()) {
                debug_log("No data available, presence advertising.");
                OS_TASK_NOTIFY(ble_peripheral_handle, PRESENCE_ADVERTISEMENT,
                        OS_NOTIFY_SET_BITS);
                return;
        }
        if (roller_get_resolutionState() == LOW_RESOLUTION &&
                OS_TIMER_IS_ACTIVE(ble_adv_transInt_timer)) {
                debug_log("ble_adv_cooldown_timer is active, not advertising.");
                OS_TASK_NOTIFY(ble_peripheral_handle, PRESENCE_ADVERTISEMENT,
                        OS_NOTIFY_SET_BITS);
                return;

        }
        debug_log("Data available and no transInt timer running");
        OS_TASK_NOTIFY(ble_peripheral_handle, DATA_ADVERTISEMENT, OS_NOTIFY_SET_BITS);
}

void roller_initialize()
{
        settling_time_timer = OS_TIMER_CREATE("settling_time_timer",
                OS_MS_2_TICKS(2000), false, OS_TIMER_GET_TIMER_ID(settling_time_timer),
                settling_timer_exceeded);
        OS_ASSERT(settling_time_timer);

        ble_adv_transInt_timer = OS_TIMER_CREATE("ble_adv_transInt_timer",
                OS_MS_2_TICKS(2000), false, OS_TIMER_GET_TIMER_ID(ble_adv_transInt_timer),
                ble_adv_transInt_exceeded);
        OS_ASSERT(ble_adv_transInt_timer);

        // TODO change to default values
        roller_set_highResMeasInt(5);
        roller_set_lowResMeasInt(20);
        roller_set_tempThreshold(DEFAULT_TEMP_THRESHOLD);
        roller_set_settlingTime(300);
        roller_set_transInt(15);
        roller_set_resolutionState(LOW_RESOLUTION);

        debug_log("-----------------------------------------------------------");
        debug_log("Initialized roller config: ");
        debug_log("HighRes interval: %d seconds.", roller_get_highResMeasInt());
        debug_log("LowRes interval: %d seconds.", roller_get_lowResMeasInt());
        debug_log("Temperature threshold: %d degree Celsius * 100.", roller_get_tempThreshold());
        debug_log("Settling time: %d seconds", roller_get_settlingTime());
        debug_log("Transmission interval: %d seconds", roller_get_transInt());
        roller_get_resolutionState() == HIGH_RESOLUTION ? debug_log("Mode: High resolution") : debug_log("Mode: Low resolution");
        debug_log("-----------------------------------------------------------");
}

void roller_AlarmMode(){
        roller_set_resolutionState(HIGH_RESOLUTION);
}

uint8_t roller_processActuatorCommand(actuator_command_t actCmd)
{
        if (actCmd.key > TRIGGER_RES || actCmd.key < HIGH_RES_MEAS_INT)
                {
                return EXIT_FAILURE;
        }

        switch (actCmd.key)
        {
        case HIGH_RES_MEAS_INT:
                debug_log("Actuator Command: HIGH_RES_MEAS_INT");
                roller_set_highResMeasInt(actCmd.value);
                break;
        case LOW_RES_MEAS_INT:
                debug_log("Actuator Command: LOW_RES_MEAS_INT");
                roller_set_lowResMeasInt(actCmd.value);
                break;
        case SETTLING_TIME:
                debug_log("Actuator Command: SETTLING_TIME");
                roller_set_settlingTime(actCmd.value);
                break;
        case TRANS_INT:
                debug_log("Actuator Command: TRANS_INT");
                roller_set_transInt(actCmd.value);
                break;
        case TEMP_THRESHOLD:
                debug_log("Actuator Command: TEMP_THRESHOLD");
                roller_set_tempThreshold(actCmd.value);
                break;
        case TRIGGER_RES:
                debug_log("Actuator Command: TRIGGER_RES");
                if (actCmd.value != 0 || actCmd.value != 1) {
                        return EXIT_FAILURE;
                }
                roller_set_resolutionState((roller_states_t)actCmd.value);
                break;
        }
        return EXIT_SUCCESS;
}
