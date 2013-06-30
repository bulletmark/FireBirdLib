#include                "../libFireBird.h"

__ino64_t HDD_GetInodeByTypeFile(TYPE_File *File)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetInodeByTypeFile");
  #endif

  char                  AbsFileName[512];
  __ino64_t             ret;

  if(HDD_GetAbsolutePathByTypeFile(File, AbsFileName))
    ret = HDD_GetInodeByAbsFileName(AbsFileName);
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
