#include "common.h"

void print_msg(const char* filename, const char* funcname, const char* format, ...)
{
  va_list args;

  // Print MSG(filename, funcname):
  printf(TXT_COL_BRIGHT_GREEN TXT_STL_BOLD "MSG(%s, %s): " TXT_RESET, filename, funcname);

  // Initialize the argument list
  va_start(args, format);

  // Print the formatted message
  vprintf(format, args);

  // Clean up the argument list
  va_end(args);
}

void print_err(const char* filename, const char* funcname, const char* format, ...)
{
  va_list args;

  // Print MSG(filename, funcname):
  printf(TXT_COL_BRIGHT_RED TXT_STL_BOLD "ERR(%s, %s): " TXT_RESET, filename, funcname);

  // Initialize the argument list
  va_start(args, format);

  // Print the formatted message
  vprintf(format, args);

  // Clean up the argument list
  va_end(args);
}

void print_wng(const char* filename, const char* funcname, const char* format, ...)
{
  va_list args;

  // Print MSG(filename, funcname):
  printf(TXT_COL_BRIGHT_MAGENTA TXT_STL_BOLD "WNG(%s, %s): " TXT_RESET, filename, funcname);

  // Initialize the argument list
  va_start(args, format);

  // Print the formatted message
  vprintf(format, args);

  // Clean up the argument list
  va_end(args);
}
