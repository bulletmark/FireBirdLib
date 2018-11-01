#include                "libFireBird.h"

__ino64_t HDD_GetInodeByTypeFile(TYPE_File *File)
{
  TRACEENTER();

  char                  AbsFileName[FBLIB_DIR_SIZE];
  __ino64_t             ret;

  if(HDD_GetAbsolutePathByTypeFile(File, AbsFileName))
    ret = HDD_GetInodeByFileName(AbsFileName);
  else
    ret = 0;

  TRACEEXIT();
  return ret;
}
