#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribGet(char *FileName, char *AttrName, byte *Data, int MaxDataLen, int *DataLen)
{
  char                  AbsFileName[512];

  if(!FileName || !*FileName || !TAP_Hdd_Exist(FileName) || !AttrName || !*AttrName)
  {
    if(DataLen) *DataLen = 0;
    return FALSE;
  }

  memset(AbsFileName, 0, sizeof(AbsFileName));
  strcpy(AbsFileName, TAPFSROOT);
  HDD_TAP_GetCurrentDir(&AbsFileName[strlen(AbsFileName)]);
  if(AbsFileName[strlen(AbsFileName) - 1] != '/') strcat(AbsFileName, "/");
  strcat(AbsFileName, FileName);

  return ExtAttribGetAbsPath(AbsFileName, AttrName, Data, MaxDataLen, DataLen);
}
