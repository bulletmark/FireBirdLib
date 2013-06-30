#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

__ino64_t HDD_GetInodeByAbsFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetInodeByAbsFileName");
  #endif

  tstat64               statbuf;
  __ino64_t             ret;

  if(FileName)
  {
    if(lstat64(FileName, &statbuf))
      ret = 0;
    else
      ret = statbuf.st_ino;
  }
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
