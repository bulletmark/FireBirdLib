#include                "libFireBird.h"

dword HDD_GetFileTimeByTypeFile(TYPE_File *File)
{
  TRACEENTER();

  char                  AbsFileName[FBLIB_DIR_SIZE];
  dword                 ret;

  if(HDD_GetAbsolutePathByTypeFile(File, AbsFileName))
    ret = HDD_GetFileTimeByFileName(AbsFileName);
  else
    ret = 0;

  TRACEEXIT();
  return ret;
}
