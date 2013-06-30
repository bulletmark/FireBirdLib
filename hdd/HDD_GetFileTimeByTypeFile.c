#include                "../libFireBird.h"

dword HDD_GetFileTimeByTypeFile(TYPE_File *File)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetFileTimeByTypeFile");
  #endif

  char                  AbsFileName[512];
  dword                 ret;

  if(HDD_GetAbsolutePathByTypeFile(File, AbsFileName))
    ret = HDD_GetFileTimeByAbsFileName(AbsFileName);
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
