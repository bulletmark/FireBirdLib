#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

dword HDD_GetFileTimeByAbsFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetFileTimeByAbsFileName");
  #endif

  tstat64               statbuf;
  dword                 ret;

  if(FileName)
  {
    if(lstat64(FileName, &statbuf))
      ret = 0;
    else
      ret = statbuf.st_mtime;
  }
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
