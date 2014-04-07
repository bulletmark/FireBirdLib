#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

dword HDD_GetFileTimeByFileName(char *FileName)
{
  TRACEENTER();

  tstat64               statbuf;
  dword                 ret;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  ret = 0;
  if(FileName && *FileName)
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    if(*AbsFileName && !lstat64(AbsFileName, &statbuf))
      ret = statbuf.st_mtime;
  }

  TRACEEXIT();
  return ret;
}
