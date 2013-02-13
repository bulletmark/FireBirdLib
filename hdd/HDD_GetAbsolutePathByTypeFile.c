#include                <string.h>
#include                "../libFireBird.h"

bool HDD_GetAbsolutePathByTypeFile(TYPE_File *File, char *AbsFileName)
{
  if(AbsFileName) AbsFileName[0] = '\0';

  if(!File || !AbsFileName) return FALSE;

  if(HDD_GetAbsolutePathByTypeFileUTF8(File, AbsFileName))
    StrMkISO(AbsFileName);

  return TRUE;
}
