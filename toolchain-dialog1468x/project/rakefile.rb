require 'rake/clean'
require 'rake/loaders/makefile'

##############################################
## Parse Linker File
##############################################
# Toolchain was installed in the docker image under $/usr/toolchain
DEV_NAME  = ENV['DEVICE'].upcase
INC_SUOTA = ENV['SUOTA'].upcase

##############################################
## Define Compiler/linker Variables 
##############################################
TOOLCHAIN_PATH = "/usr/toolchain" 
COMPILER_PATH = "#{TOOLCHAIN_PATH}/GCC/4_9-2015q3"

SOURCE_DIR  = "src"
INCLUDE_DIR = File.join( File.dirname(__FILE__), "/include")
CONFIG_DIR  = File.join( File.dirname(__FILE__), "/config")
if INC_SUOTA == "yes"
    WORKING_DIR = File.dirname(__FILE__)
end
OBJ_DIR     = "build/obj"
BUILD_DIR   = "build"

GCC         = "#{COMPILER_PATH}/bin/arm-none-eabi-gcc"
OBJCOPY     = "#{COMPILER_PATH}/bin/arm-none-eabi-objcopy"
EABI_SIZE   = "#{COMPILER_PATH}/bin/arm-none-eabi-size"

SDK_DIR     = "/usr/toolchain/boards/sdk"

FileUtils.mkdir_p "#{OBJ_DIR}/"
FileUtils.mkdir_p "#{BUILD_DIR}/"
FileUtils.touch("#{BUILD_DIR}/memory.map")

SDK_FILES = Rake::FileList.new(
  "#{SDK_DIR}/middleware/segger_tools/SEGGER/SEGGER_RTT.c", 
  "#{SDK_DIR}/middleware/segger_tools/SEGGER/SEGGER_RTT_printf.c", 
  "#{SDK_DIR}/bsp/startup/config.c", 
  "#{SDK_DIR}/bsp/startup/startup_ARMCM0.S", 
  "#{SDK_DIR}/bsp/startup/system_ARMCM0.c", 
  "#{SDK_DIR}/bsp/startup/vector_table.S", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_aes_hash.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_coex.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_cpm.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_crypto.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_dma.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_ecc.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_ecc_curves.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_ecc_ucode.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_fem_sky66112-11.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_gpadc.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_gpio.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_hard_fault.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_i2c.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_irgen.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_keyboard_scanner.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_otpc.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_qspi.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_quad.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_rf.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_soc.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_spi.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_tempsens.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_timer0.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_timer1.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_timer2.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_trng.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_uart.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_usb.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_usb_charger.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_watchdog.c", 
  "#{SDK_DIR}/bsp/peripherals/src/hw_wkup.c", 
  "#{SDK_DIR}/bsp/peripherals/src/sys_tcs.c", 
  "#{SDK_DIR}/bsp/osal/msg_queues.c", 
  "#{SDK_DIR}/bsp/osal/resmgmt.c", 
  "#{SDK_DIR}/bsp/osal/usb_osal_wrapper.c", 
  "#{SDK_DIR}/bsp/memory/src/qspi_automode.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_charger.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_clock_mgr.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_power_mgr.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_rtc.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_socf.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_trng.c", 
  "#{SDK_DIR}/bsp/system/sys_man/sys_watchdog.c", 
  "#{SDK_DIR}/interfaces/ble/src/util/list.c", 
  "#{SDK_DIR}/interfaces/ble/src/util/queue.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/driver/rf/src/rf_ble_functions.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch/main/ble/arch_main.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch/main/ble/jump_table.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/modules/rwip/src/rwip.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/modules/nvds/src/nvds.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/profiles/prf.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/rwble/rwble.c", 
  "#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/rwble/window_stats.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_ad_msg.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_cmd.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_common.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_gap.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_gattc.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_gatts.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_gtl.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_helper.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/ble_mgr_l2cap.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/storage.c", 
  "#{SDK_DIR}/interfaces/ble/src/manager/storage_flash.c", 
  "#{SDK_DIR}/interfaces/ble/src/adapter/ad_ble.c", 
  "#{SDK_DIR}/interfaces/ble/src/adapter/ble_prod_test.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_attribdb.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_common.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_gap.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_gattc.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_gattc_util.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_gatts.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_l2cap.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_storage.c", 
  "#{SDK_DIR}/interfaces/ble/src/ble_uuid.c", 
  "#{SDK_DIR}/interfaces/ble_services/src/tps.c", 
  "#{SDK_DIR}/interfaces/ble_services/src/dis.c", 
  "#{SDK_DIR}/interfaces/ble_services/src/ble_service.c" )
if INC_SUOTA == "yes"
    SDK_FILES.include("#{SDK_DIR}/interfaces/ble_services/src/dlg_suota.c")
end
SDK_FILES.include(
  "#{SDK_DIR}/bsp/adapters/src/ad_battery.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_crypto.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_flash.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_gpadc.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_i2c.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_keyboard_scanner.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_nvms.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_nvms_direct.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_nvms_ves.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_nvparam.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_rf.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_spi.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_temp_sens.c", 
  "#{SDK_DIR}/bsp/adapters/src/ad_uart.c", 
  "#{SDK_DIR}/bsp/free_rtos/portable/MemMang/heap_4.c", 
  "#{SDK_DIR}/bsp/free_rtos/portable/GCC/ARM_CM0/port.c", 
  "#{SDK_DIR}/bsp/free_rtos/croutine.c", 
  "#{SDK_DIR}/bsp/free_rtos/event_groups.c", 
  "#{SDK_DIR}/bsp/free_rtos/list.c", 
  "#{SDK_DIR}/bsp/free_rtos/queue.c", 
  "#{SDK_DIR}/bsp/free_rtos/tasks.c", 
  "#{SDK_DIR}/bsp/free_rtos/timers.c" )

OBJECTS_SDK = SDK_FILES.ext(".obj")

SOURCES     = Rake::FileList["#{SOURCE_DIR}/*.c"]
OBJECTS     = SOURCES.ext(".obj")

INCLUDES    = INCLUDE_DIR
TARGET      = "#{BUILD_DIR}/#{File.basename(File.dirname(__FILE__))}_#{Time.now.strftime("%Y%m%d_%H%M")}"

COMPILER_OPTS = "-mcpu=cortex-m0 -mthumb -fsigned-char -ffunction-sections -fdata-sections -std=gnu11 -Og -ggdb"

if INC_SUOTA == "yes"
    INCLUDE_PATHS = " \
            -include #{CONFIG_DIR}/custom_config_qspi_suota.h \
                " 
else
    INCLUDE_PATHS = " \
            -include #{CONFIG_DIR}/custom_config_qspi.h \
                " 
end


INCLUDE_LIBS_PATH = " \
    -I#{COMPILER_PATH}/arm-none-eabi/include \
    -I#{CONFIG_DIR} \
    -I#{INCLUDES} "
if INC_SUOTA == "yes"
    INCLUDE_LIBS_PATH = INCLUDE_LIBS_PATH + "-I#{WORKING}"
end
INCLUDE_LIBS_PATH = INCLUDE_LIBS_PATH + " \
    -I#{SDK_DIR} \
    -I#{SDK_DIR}/bsp/adapters/include \
    -I#{SDK_DIR}/bsp/config \
    -I#{SDK_DIR}/bsp/free_rtos/include \
    -I#{SDK_DIR}/bsp/include \
    -I#{SDK_DIR}/bsp/memory/include \
    -I#{SDK_DIR}/bsp/osal \
    -I#{SDK_DIR}/bsp/peripherals/include \
    -I#{SDK_DIR}/bsp/system/sys_man/include \
    -I#{SDK_DIR}/interfaces/ble_clients/include \
    -I#{SDK_DIR}/interfaces/ble/config \
    -I#{SDK_DIR}/interfaces/ble/include \
    -I#{SDK_DIR}/interfaces/ble/include/adapter \
    -I#{SDK_DIR}/interfaces/ble/include/manager \
    -I#{SDK_DIR}/interfaces/ble_services/include \
    -I#{SDK_DIR}/interfaces/ble/src/stack/config \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/att \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/att/attc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/att/attm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/att/atts \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gap \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gap/gapc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gap/gapm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gatt \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gatt/gattc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/gatt/gattm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/l2c/l2cc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/l2c/l2cm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/smp \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/smp/smpc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/host/smp/smpm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/hl/src/rwble_hl \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/controller/em \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/controller/llc \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/controller/lld \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/controller/llm \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/ll/src/rwble \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ble/profiles \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/ea/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/em/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/hci/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/ip/hci/src \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/common/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/dbg/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/gtl/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/gtl/src \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/h4tl/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/ke/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/ke/src \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/nvds/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/modules/rwip/api \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch/boot/armgcc_4_8 \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch/compiler/armgcc_4_8 \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/arch/ll/armgcc_4_8 \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/build/ble-full/reg/fw \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/driver/flash \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/driver/reg \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/driver/rf \
    -I#{SDK_DIR}/interfaces/ble/src/stack/plf/black_orca/src/driver/rf/api \
    -I#{SDK_DIR}/interfaces/ble_stack \
    -I#{SDK_DIR}/middleware/segger_tools/Config/ \
    -I#{SDK_DIR}/middleware/segger_tools/OS/ \
    -I#{SDK_DIR}/middleware/segger_tools/SEGGER/ \
"
######################################
ARM_OPTIONS = "-mcpu=cortex-m0 -mthumb"

CFLAGS = "-Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu11 -Wall -ggdb -g3"

if DEV_NAME == "DA14683"
    ORCA_OPTS = "-Ddg_configBLACK_ORCA_IC_REV=BLACK_ORCA_IC_REV_B \
                -Ddg_configBLACK_ORCA_IC_STEP=BLACK_ORCA_IC_STEP_B"
    BLE_STACK_BOARD = "ble_stack_da14683_00"
    PROD_ID = "DA14683-00"
else
    ORCA_OPTS = "-Ddg_configBLACK_ORCA_IC_REV=BLACK_ORCA_IC_REV_A \
                -Ddg_configBLACK_ORCA_IC_STEP=BLACK_ORCA_IC_STEP_E"
    BLE_STACK_BOARD = "ble_stack_da14681_01"
    PROD_ID = "DA14681-01"
end


# ORCA_OPTS = "-Ddg_configBLACK_ORCA_IC_REV=BLACK_ORCA_IC_REV_A \
#             -Ddg_configBLACK_ORCA_IC_STEP=BLACK_ORCA_IC_STEP_E"

OPTIONS =   "-DCONFIG_CUSTOM_PRINT\
            -D__USES_INITFINI__ \
            -DNDEBUG \
            -DCONFIG_UART_USE_RESMGMT \
            -DHARNESS_TESTS_ENABLED #{ORCA_OPTS}"

##############################################
## Ruby Tools on Docker
##############################################
require_relative "tools/RakeSupportFunctions"
include RakeSupportFunctions


##############################################
## Building Process
##############################################
task :default => :build

rule '.obj' => '.c' do |task|
    puts "#{BBlue}[Building C Object] #{task.name} #{Color_Off} \n"
    quiet_sh "#{GCC} #{ARM_OPTIONS} #{CFLAGS} #{ORCA_OPTS} -DNDEBUG #{INCLUDE_LIBS_PATH} #{INCLUDE_PATHS} -MMD -MP -MF   #{File.join( OBJ_DIR, File.basename(task.name.ext(".d")))} -MT #{File.join( OBJ_DIR, File.basename(task.name.ext(".o")))} -c -o #{task.name} #{task.source} #{COLOR_OUTPUT}"
end

rule '.obj' => '.S' do |task|
    puts "#{BBlue}[Building S Object] #{task.name} #{Color_Off} \n"
    quiet_sh "#{GCC} #{ARM_OPTIONS} #{CFLAGS} #{ORCA_OPTS} -DNDEBUG #{INCLUDE_LIBS_PATH} #{INCLUDE_PATHS} -MMD -MP -MF #{File.join( OBJ_DIR, File.basename(task.name.ext(".d")))} -MT #{File.join( OBJ_DIR, File.basename(task.name.ext(".o")))} -c -o #{task.name} #{task.source} #{COLOR_OUTPUT}"
end


##################
# libraries 
##################
task :build_ld  do
    quiet_sh "#{GCC} #{ORCA_OPTS} -I #{SDK_DIR}/bsp/config #{INCLUDE_PATHS} -E -P -c #{SDK_DIR}/bsp/ldscripts/ble_projects/sections.ld.h -o #{BUILD_DIR}/sections.ld"

    quiet_sh "#{GCC} #{ORCA_OPTS} -I #{SDK_DIR}/bsp/config #{INCLUDE_PATHS} -E -P -c #{SDK_DIR}/bsp/ldscripts/ble_projects/mem.ld.h -o #{BUILD_DIR}/mem.ld"
end

##################
# Project 
##################
task :build => "#{TARGET}.elf" 

file "#{TARGET}.elf" => [OBJECTS_SDK, OBJECTS, :build_ld].flatten(1) do |task|
    puts "#{BBlue}[Linking]#{Color_Off}\n"

    quiet_sh "#{GCC} #{ARM_OPTIONS} #{CFLAGS}  -T\"./#{BUILD_DIR}/mem.ld\" -T\"./#{BUILD_DIR}/sections.ld\" -Xlinker --gc-sections -L\"#{SDK_DIR}/interfaces/ble_stack//#{PROD_ID}-Release\" -L\"#{SDK_DIR}/bsp/misc\" -Wl,-Map #{BUILD_DIR}/memory.map --specs=nano.specs --specs=nosys.specs -o #{task.name} #{OBJECTS_SDK} #{OBJECTS} -l#{BLE_STACK_BOARD} -lm"

    sh "#{OBJCOPY} -O binary #{TARGET}.elf #{TARGET}.bin"

    sh "#{EABI_SIZE} --format=berkeley #{TARGET}.elf"
end

CLEAN.include("#{OBJ_DIR}", "#{BUILD_DIR}","**/*.obj", "#{SDK_DIR}/**/*.obj"  )
