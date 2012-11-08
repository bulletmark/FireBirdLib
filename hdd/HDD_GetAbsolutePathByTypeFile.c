#include                <string.h>
#include                "../libFireBird.h"

bool HDD_GetAbsolutePathByTypeFile(TYPE_File *File, char *AbsFileName)
{
  dword   *d;

  if(AbsFileName) AbsFileName[0] = '\0';

  if(!File || !AbsFileName) return FALSE;

  //TYPE_File->handle points to a structure with 4 dwords. The third one points to the absolute path
  d = File->handle;
  if(!d || !d[2]) return FALSE;

  strcpy(AbsFileName, (char*)d[2]);
  StrMkISO(AbsFileName);

  return TRUE;
}
