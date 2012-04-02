#include                "../libFireBird.h"

dword HDD_GetInodeByTypeFile(TYPE_File *File)
{
  char                  AbsFileName[512];

  if(!HDD_GetAbsolutePathByTypeFile(File, AbsFileName)) return 0;

  return HDD_GetInodeByAbsFileName(AbsFileName);
}
