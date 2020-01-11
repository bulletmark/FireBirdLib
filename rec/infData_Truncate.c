#include <unistd.h>
#include "FBLib_rec.h"

void infData_Truncate(const char *infFileName, dword Position)
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
