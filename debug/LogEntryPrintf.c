#include  <stdio.h>
#include  <string.h>
#include "stdarg.h"    //va_list
#include  "../libFireBird.h"

int vsnprintf(char *str, size_t size, const char *format, va_list ap);   //define missing prototype

void LogEntryPrintf(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *format, ...)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogEntryPrintf");
  #endif

  char Text[512];

  if(!format)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  va_list args;
  va_start(args, format);
  vsnprintf(Text, sizeof(Text), format, args);
  va_end(args);
  LogEntry(FileName, ProgramName, Console, TimeStampFormat, Text);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
