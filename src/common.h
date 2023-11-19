#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;

////////////////////////////////// BINARY

/// @brief Get the bit value at the specified position.
#define BIT_GET(x, n) ((x & (1 << n)) ? 1 : 0)

/// @brief Set the bit value at the specified position.
#define BIT_SET(x, n, on) (on ? (x) |= (1 << n) : (x) &= ~(1 << n))

////////////////////////////////// PRINT

#define TXT_COL_DEFAULT "\x1b[39m"
#define TXT_COL_BLACK "\x1b[30m"
#define TXT_COL_RED "\x1b[31m"
#define TXT_COL_GREEN "\x1b[32m"
#define TXT_COL_YELLOW "\x1b[33m"
#define TXT_COL_BLUE "\x1b[34m"
#define TXT_COL_MAGENTA "\x1b[35m"
#define TXT_COL_CYAN "\x1b[36m"
#define TXT_COL_WHITE "\x1b[37m"
#define TXT_COL_BRIGHT_BLACK "\x1b[90m"
#define TXT_COL_BRIGHT_RED "\x1b[91m"
#define TXT_COL_BRIGHT_GREEN "\x1b[92m"
#define TXT_COL_BRIGHT_YELLOW "\x1b[93m"
#define TXT_COL_BRIGHT_BLUE "\x1b[94m"
#define TXT_COL_BRIGHT_MAGENTA "\x1b[95m"
#define TXT_COL_BRIGHT_CYAN "\x1b[96m"
#define TXT_COL_BRIGHT_WHITE "\x1b[97m"
#define TXT_STL_BOLD "\x1b[1m"
#define TXT_STL_UNDERLINE "\x1b[4m"
#define TXT_STL_ITALIC "\x1b[3m"
#define TXT_RESET "\x1b[0m"

/// @brief Print message to console reporting filename, function name and a message.
/// @param filename Callee file.
/// @param funcname Callee function.
/// @param format Message format.
/// @param "..." Params list to be used based on specified format.
void print_msg(const char *filename, const char *funcname, const char *format, ...);

/// @brief Print error to console reporting filename, function name and an error message.
/// @param filename Callee file.
/// @param funcname Callee function.
/// @param format Message format.
/// @param "..." Params list to be used based on specified format.
void print_err(const char *filename, const char *funcname, const char *format, ...);

/// @brief Print warning to console reporting filename, function name and a warning message.
/// @param filename Callee file.
/// @param funcname Callee function.
/// @param format Message format.
/// @param "..." Params list to be used based on specified format.
void print_wng(const char *filename, const char *funcname, const char *format, ...);

#define NO_IMPL(file, func) { print_wng(file, func, "not implemented yet.\n"); return -5; }

////////////////////////////////// MATH

/// @brief Check if the value is in range.
#define BETWEEN(x, inf, sup) ((x >= inf) && (x <= sup))

#endif // COMMON_H
