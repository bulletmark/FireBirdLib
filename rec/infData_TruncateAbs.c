#include <string.h>
#include <unistd.h>
#include <tap.h>
#include "FBLib_rec.h"

extern int truncate (__const char *__file, __off_t __length);

void infData_TruncateAbs(char *infFileName, dword Position)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_TruncateAbs");
  #endif

  truncate(infFileName, Position);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
