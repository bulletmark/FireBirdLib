#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

dword HDD_GetInodeByAbsFileName(char *FileName)
{
  tstat64               statbuf;
  int                   status;

  if(!FileName) return 0;
  if((status = lstat64(FileName, &statbuf))) return 0;

  return (dword)statbuf.st_ino;
}
