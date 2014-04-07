#include <string.h>
#include <unistd.h>
#include <tap.h>
#include "FBLib_rec.h"

extern int truncate (__const char *__file, __off_t __length);

void infData_Truncate(char *infFileName, dword Position)
{
  TRACEENTER();

  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(infFileName && *infFileName)
  {
    ConvertPathType(infFileName, AbsFileName, PF_FullLinuxPath);
    if(*AbsFileName) truncate(AbsFileName, Position);
  }

  TRACEEXIT();
}
