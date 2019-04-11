cmake_minimum_required(VERSION 3.13)

# These Amazon FreeRTOS related global variables are available to use.
# AFR_ROOT_DIR          Amazon FreeRTOS source root.
# AFR_MODULES_DIR       Amazon FreeRTOS modules root.
# AFR_DEMOS_DIR         Amazon FreeRTOS demos root.
# AFR_TESTS_DIR         Amazon FreeRTOS tests root.
# AFR_3RDPARTY_DIR      3rdparty libraries root.

# AFR_VENDOR_NAME       Folder name for vendor.
# AFR_BOARD_NAME        Folder name for this board.

# AFR_TOOLCHAIN         Compiler chosen by the user. Should be one of
#                       the file names under ${AFR_ROOT_DIR}/cmake/toolchains
# AFR_IS_TESTING        1 if testing enabled, otherwise, 0.

# You may also use these 2 functions we defined to glob files when needed. However, we recommend
# to specify your source files explicitly to avoid unexpected behavior unless you're 100% sure.
# CMake reference link: https://cmake.org/cmake/help/latest/command/file.html#filesystem
# afr_glob_files(<out_var> [RECURSE] <DIRECTORY> <directory> [<GLOBS> <glob-expressions>...])
# afr_glob_src(<out_var> [RECURSE] <DIRECTORY> <directory> [<EXTENSIONS> <file-extensions>...])

# If you don't specify GLOBS or EXTENSIONS parameters,
# afr_glob_files: glob all files including hidden files in the specified directory.
# afr_glob_src:   glob all files ending with either .c, .h, .s or .asm

# Use RECURSE if you want to recursively search all subdirectories.

# Example usage,
# afr_glob_src(board_code DIRECTORY "${board_dir}/application_code/${vendor}_code")
# afr_glob_src(driver_code RECURSE DIRECTORY "${driver_path}")
# afr_glob_src(headers DIRECTORY "${some_path}" EXTENSIONS h)

# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS Console metadata
# -------------------------------------------------------------------------------------------------
# Provide metadata for listing on Amazon FreeRTOS console.
afr_set_board_metadata(NAME "CURIOSITY_PIC32MZ-EF")
afr_set_board_metadata(DISPLAY_NAME "CURIOSITY_PIC32MZ-EF")
afr_set_board_metadata(DESCRIPTION "CURIOSITY_PIC32MZ-EF")
afr_set_board_metadata(VENDOR_NAME "Microchip Technology Inc")
afr_set_board_metadata(FAMILY_NAME "PIC32MZ-EF")
afr_set_board_metadata(DATA_RAM_MEMORY "512KB")
afr_set_board_metadata(PROGRAM_MEMORY "2MB")
afr_set_board_metadata(CODE_SIGNER "AmazonFreeRTOS-Default")
afr_set_board_metadata(SUPPORTED_IDE "MPLABX")
afr_set_board_metadata(IDE_MPLABX_NAME "Microchip MPLAB-X")
afr_set_board_metadata(IDE_MPLABX_COMPILERS "Microchip XC32")

set(board_demos_dir "${AFR_ROOT_DIR}/demos/microchip/curiosity_pic32mzef/common")
set(board_tests_dir "${AFR_ROOT_DIR}/tests/microchip/curiosity_pic32mzef/common")
if(AFR_IS_TESTING)
    set(board_dir "${board_tests_dir}")
else()
    set(board_dir "${board_demos_dir}")
endif()

# -------------------------------------------------------------------------------------------------
# Compiler settings
# -------------------------------------------------------------------------------------------------
# If you have multiple compiler supports, you can use AFR_TOOLCHAIN. Also might be a good idea to
# put your compiler settings to different files and just include them here, e.g.,
# include(<vendor_dir>/compilers/${AFR_TOOLCHAIN}.cmake)

# ==================== Example ====================
afr_mcu_port(compiler)

# Compile definitions/macros
target_compile_definitions(
    AFR::compiler::mcu_port
    INTERFACE CURIOSITY_PIC32MZ_EF
)

# Compiler flags
set(c_flags -g -x c -ffunction-sections -O1 -mprocessor=32MZ2048EFM100 -mnewlib-libc -std=gnu99 -fgnu89-inline)
set(asm_flags -mprocessor=32MZ2048EFM100 -MMD -MF -DXPRJ_pic32mz_ef_curiosity=pic32mz_ef_curiosity -no-legacy-libc -Wa$<COMMA>--gdwarf-2)
target_compile_options(
    AFR::compiler::mcu_port
    INTERFACE
    $<IF:$<COMPILE_LANGUAGE:C>,${c_flags},${asm_flags}>
)

# Libraries to link
target_link_libraries(
     AFR::compiler::mcu_port
     INTERFACE
         "${AFR_ROOT_DIR}/lib/third_party/mcu_vendor/microchip/harmony/v2.05/bin/framework/peripheral/PIC32MZ2048EFM100_peripherals.a"
 )

# Linker flags
target_link_options(
    AFR::compiler::mcu_port
    INTERFACE
        -Wl,--script="${board_dir}/application_code/microchip_code/app_mz.ld",--defsym=_min_heap_size=170000,--defsym=_min_stack_size=10000,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,--allow-multiple-definition
)

# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS portable layers
# -------------------------------------------------------------------------------------------------
# Define portable layer targets with afr_mcu_port(<module_name>). We will create an CMake
# INTERFACE IMPORTED target called AFR::${module_name}::mcu_port for you. You can use it with
# standard CMake functions like target_*. To better organize your files, you can define your own
# targets and use target_link_libraries(AFR::${module_name}::mcu_port INTERFACE <your_targets>)
# to provide the public interface you want expose.
# -------------------------------------------------------------------------------------------------
# Normally the portable layer for kernel should be vendor's driver code.
afr_mcu_port(kernel)
target_sources(
    AFR::kernel::mcu_port
    INTERFACE
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MPLAB/PIC32MZ/port.c"
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MPLAB/PIC32MZ/port_asm.S"
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MPLAB/PIC32MZ/portmacro.h"
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MemMang/heap_4.c"
)

target_include_directories(
    AFR::kernel::mcu_port
    INTERFACE
        "${board_dir}"
        "${board_dir}/config_files"
        "${board_dir}/application_code/microchip_code"
        "${AFR_MODULES_DIR}/pkcs11/portable/microchip/curiosity_pic32mzef"
        "${AFR_MODULES_DIR}/third_party/mbedtls/include"
        "${AFR_MODULES_DIR}/include"
        "${AFR_MODULES_DIR}/include/private"
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MPLAB/PIC32MZ"
        "${board_dir}/../../../common/include"
        "${AFR_MODULES_DIR}/third_party/jsmn"
        "${AFR_MODULES_DIR}/third_party/pkcs11"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/bsp"
        "${AFR_MODULES_DIR}/FreeRTOS/portable/MPLAB/PIC32MZ"
        "${AFR_MODULES_DIR}/FreeRTOS-Plus-TCP/include"
        "${AFR_MODULES_DIR}/FreeRTOS-Plus-TCP/source/portable/Compiler/GCC"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/system/common"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/include"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/wireless_driver_extension"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/wireless_driver_extension/common/include"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/wireless_driver_extension/driver/include"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/wireless_driver_extension/driver/source"
        "${AFR_MODULES_DIR}/third_party/mcu_vendor/microchip/harmony/v2.05/framework/driver/wifi/wilc1000/wireless_driver/include"
        "${AFR_MODULES_DIR}/ota/portable/microchip/curiosity_pic32mzef"
        "${AFR_MODULES_DIR}/third_party/tinycbor"
        "${AFR_MODULES_DIR}/ota"
        "${AFR_MODULES_DIR}/cbor/src"
        "${AFR_MODULES_DIR}/defender/src"
        "${AFR_MODULES_DIR}/defender/metrics"
        "${AFR_MODULES_DIR}/defender/portable/freertos"
        "${AFR_MODULES_DIR}/defender/report"
)

# If you defined the driver and freertos portable target separately, you can use afr_mcu_port with
# DEPENDS keyword, e.g.,
# afr_mcu_port(kernel DEPENDS my_board_driver freertos_port)


# WiFi
afr_mcu_port(wifi)
target_sources(
    AFR::wifi::mcu_port
    INTERFACE 
        "${AFR_MODULES_DIR}/wifi/portable/microchip/curiosity_pic32mzef/aws_wifi.c"
        "${AFR_MODULES_DIR}/wifi/portable/microchip/curiosity_pic32mzef/aws_wifi_assert.c"
)

# PKCS11
afr_mcu_port(pkcs11)
target_sources(
    AFR::pkcs11::mcu_port
    INTERFACE
        "${AFR_MODULES_DIR}/pkcs11/portable/microchip/curiosity_pic32mzef/aws_pkcs11_pal.c"
        "${AFR_MODULES_DIR}/pkcs11/portable/microchip/curiosity_pic32mzef/pkcs11_nvm.c"
        "${AFR_MODULES_DIR}/include/private/threading_alt.h"
)

target_link_libraries(
    AFR::pkcs11::mcu_port
    INTERFACE 3rdparty::mbedtls
)

# Secure sockets
afr_mcu_port(secure_sockets)
target_sources(
    AFR::secure_sockets::mcu_port
    INTERFACE "${AFR_MODULES_DIR}/secure_sockets/portable/freertos_plus_tcp/aws_secure_sockets.c"
)

# OTA
afr_mcu_port(ota)
target_sources(
    AFR::ota::mcu_port
    INTERFACE "${AFR_MODULES_DIR}/ota/portable/microchip/curiosity_pic32mzef/aws_ota_pal.c"
    INTERFACE "${AFR_MODULES_DIR}/ota/portable/microchip/curiosity_pic32mzef/aws_nvm.c"
)


# -------------------------------------------------------------------------------------------------
# Amazon FreeRTOS demos and tests
# -------------------------------------------------------------------------------------------------
# We require you to define at least demos and tests executable targets. Available demos and tests
# will be automatically enabled by us. You need to provide other project settings such as linker
# scripts and post build commands.

# ==================== Example ====================
set(CMAKE_EXECUTABLE_SUFFIX ".out")

if(AFR_IS_TESTING)
    set(exe_target aws_tests)
else()
    set(exe_target aws_demos)
endif()

afr_glob_src(board_code_src DIRECTORY "${board_dir}/application_code/microchip_code")
afr_glob_src(driver_code RECURSE DIRECTORY "${AFR_3RDPARTY_DIR}/mcu_vendor/microchip/harmony/v2.05/framework") 
afr_glob_src(main_code DIRECTORY "${board_dir}/application_code")
add_executable(
    ${exe_target}
    ${board_code_src}
    ${driver_code}
    ${main_code}
    
)
target_link_libraries(
    ${exe_target}
    PRIVATE
        AFR::wifi
        AFR::utils
)

add_custom_command(
    TARGET ${exe_target} POST_BUILD
    COMMAND python ../../../common/ota/bootloader/utility/binary_image_generator.py -d ${MP_CC_DIR} -b xc32-objcopy -p "-I ihex ${ImagePath} -O binary ${ImageDir}/mplab.${IMAGE_TYPE}.bin" && python ../../../common/ota/bootloader/utility/ota_image_generator.py -b ${ImageDir}/mplab.${IMAGE_TYPE}.bin -p MCHP-Curiosity-PIC32MZEF
)
