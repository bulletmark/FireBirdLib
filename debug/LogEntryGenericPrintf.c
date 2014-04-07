#include  <stdio.h>
#include  <string.h>
#include "stdarg.h"    //va_list
#include  "../libFireBird.h"

int vsnprintf(char *str, size_t size, const char *format, va_list ap);   //define missing prototype

void LogEntryGenericPrintf(char *ProgramName, bool Console, char *format, ...)
{
  TRACEENTER();

  char Text[512];

  if(!format)
  {
    TRACEEXIT();
    return;
  }

  va_list args;
  va_start(args, format);
  vsnprintf(Text, sizeof(Text), format, args);
  va_end(args);
  LogEntryGeneric(ProgramName, Console, Text);

  TRACEEXIT();
}
