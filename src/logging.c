#include <stdarg.h>

#include <sqlite3ext.h>
extern const sqlite3_api_routines *sqlite3_api;

#include "logging.h"

#define LOG_BUFFER_SIZE 512

void chemicalite_log(int iErrCode, const char *zFormat, ...)
{
  char buffer[LOG_BUFFER_SIZE];

  va_list argp;
  va_start(argp, zFormat);
  sqlite3_vsnprintf(LOG_BUFFER_SIZE, buffer, zFormat, argp);
  va_end(argp);

  sqlite3_log(iErrCode, buffer);
}