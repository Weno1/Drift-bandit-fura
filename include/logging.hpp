#pragma once

#include <stdio.h>
#include "pico/stdlib.h"

// Define Log Levels
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_NONE  4

// Set the active log level here (Change to LOG_LEVEL_DEBUG for more output)
#ifndef CURRENT_LOG_LEVEL
    #define CURRENT_LOG_LEVEL LOG_LEVEL_INFO
#endif

// Macro implementation
#define LOG_PRINT(level, color, fmt, ...) printf(color "[%s] " fmt "\033[0m\n", level, ##__VA_ARGS__)

// ANSI Color Codes for pretty terminal output
#define COLOR_RESET  "\033[0m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RED    "\033[31m"

// Debug Log
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG
    #define LOG_DEBUG(fmt, ...) LOG_PRINT("DEBUG", COLOR_CYAN, fmt, ##__VA_ARGS__)
#else
    #define LOG_DEBUG(fmt, ...)
#endif

// Info Log
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO
    #define LOG_INFO(fmt, ...) LOG_PRINT("INFO", COLOR_GREEN, fmt, ##__VA_ARGS__)
#else
    #define LOG_INFO(fmt, ...)
#endif

// Warning Log
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN
    #define LOG_WARN(fmt, ...) LOG_PRINT("WARN", COLOR_YELLOW, fmt, ##__VA_ARGS__)
#else
    #define LOG_WARN(fmt, ...)
#endif

// Error Log
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR
    #define LOG_ERROR(fmt, ...) LOG_PRINT("ERROR", COLOR_RED, fmt, ##__VA_ARGS__)
#else
    #define LOG_ERROR(fmt, ...)
#endif