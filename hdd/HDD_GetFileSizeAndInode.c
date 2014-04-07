#include                <sys/stat.h>
#include                <string.h>
#include                "FBLib_hdd.h"

bool HDD_GetFileSizeAndInode(char *FileName, __ino64_t *CInode, __off64_t *FileSize)
{
  TRACEENTER();

  char                  AbsFileName[FBLIB_DIR_SIZE];
  tstat64               statbuf;
  bool                  ret;

  ret = FALSE;
  if(FileName && *FileName)
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    if(*AbsFileName && !lstat64(AbsFileName, &statbuf))
    {
      if(CInode) *CInode = statbuf.st_ino;
      if(FileSize) *FileSize = statbuf.st_size;
      ret = TRUE;
    }
  }

  TRACEEXIT();
  return ret;
}
