#include                <sys/stat.h>
#include                <string.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

#ifdef _TMSEMU_
  bool HDD_GetFileSizeAndInode(char *Directory, char *FileName, dword *CInode, off_t *FileSize)
#else
  bool HDD_GetFileSizeAndInode(char *Directory, char *FileName, dword *CInode, __off64_t *FileSize)
#endif
{
  char                  AbsFileName[256];
  tstat64               statbuf;
  int                   status;

  TAP_SPrint(AbsFileName, "%s%s/%s", TAPFSROOT, Directory, FileName);

  if((status = lstat64(AbsFileName, &statbuf))) return FALSE;

  if(CInode) *CInode = statbuf.st_ino;
  if(FileSize) *FileSize = statbuf.st_size;

  return TRUE;
}
