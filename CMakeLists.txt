# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# User functions
include(CheckCXXCompilerFlag)
function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
        unset(flag_supported CACHE)
    endif()
endfunction()

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Drift-bandit-fura C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executables.
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable("${CMAKE_PROJECT_NAME}")
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )

pico_set_program_name("${CMAKE_PROJECT_NAME}" "Drift-bandit-fura")
pico_set_program_version("${CMAKE_PROJECT_NAME}" "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart("${CMAKE_PROJECT_NAME}" 0)
pico_enable_stdio_usb("${CMAKE_PROJECT_NAME}" 1)

# Add the standard library to the build
target_link_libraries("${CMAKE_PROJECT_NAME}"
        pico_stdlib)

# Add the standard include files to the build
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/" "${CMAKE_CURRENT_SOURCE_DIR}")

# Add any user requested libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" 
        pico_cyw43_arch_lwip_poll
        hardware_pwm
        hardware_adc
        hardware_spi
        hardware_i2c
        hardware_watchdog
)

string(APPEND CMAKE_EXE_LINKER_FLAGS "-Wl,--print-memory-usage")
enable_cxx_compiler_flag_if_supported("-Wall")
pico_add_extra_outputs("${CMAKE_PROJECT_NAME}")

