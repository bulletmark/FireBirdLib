#include                "../libFireBird.h"

dword HDD_GetFileTimeByTypeFile(TYPE_File *File)
{
  char                  AbsFileName[512];

  if(!HDD_GetAbsolutePathByTypeFileUTF8(File, AbsFileName)) return 0;

  return HDD_GetFileTimeByAbsFileName(AbsFileName);
}
