#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

dword HDD_GetFileTimeByAbsFileName(char *FileName)
{
  tstat64               statbuf;
  int                   status;

  if(!FileName) return 0;
  if((status = lstat64(FileName, &statbuf))) return 0;

  return statbuf.st_mtime;
}
