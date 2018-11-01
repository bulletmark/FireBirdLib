#include                <sys/stat.h>
#include                "FBLib_hdd.h"
#include                "libFireBird.h"

__ino64_t HDD_GetInodeByFileName(char *FileName)
{
  TRACEENTER();

  __ino64_t             ret;

  HDD_GetFileSizeAndInode(FileName, &ret, NULL);

  TRACEEXIT();
  return ret;
}
