#include  <stdio.h>
#include  <string.h>
#include "stdarg.h"    //va_list
#include  "../libFireBird.h"

int vsnprintf(char *str, size_t size, const char *format, va_list ap);   //define missing prototype

void LogEntryGenericPrintf(char *ProgramName, bool Console, char *format, ...)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogEntryGenericPrintf");
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
  LogEntryGeneric(ProgramName, Console, Text);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
