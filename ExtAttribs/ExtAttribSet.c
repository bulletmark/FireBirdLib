#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribSet(char *FileName, char *AttrName, byte *Data, int DataLen)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribSet");
  #endif

  char                  AbsFileName[512];
  bool                  ret;

  if(!FileName || !*FileName || !TAP_Hdd_Exist(FileName) || !AttrName || !*AttrName)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  memset(AbsFileName, 0, sizeof(AbsFileName));
  strcpy(AbsFileName, TAPFSROOT);
  HDD_TAP_GetCurrentDir(&AbsFileName[strlen(AbsFileName)]);
  if(AbsFileName[strlen(AbsFileName) - 1] != '/') strcat(AbsFileName, "/");
  strcat(AbsFileName, FileName);
  ret = ExtAttribSetAbsPath(AbsFileName, AttrName, Data, DataLen);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
