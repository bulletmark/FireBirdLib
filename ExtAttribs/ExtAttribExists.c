#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

int ExtAttribExists(char *FileName, char *AttrName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribExists");
  #endif

  char                  AbsFileName[512];
  int                   ret;

  if(!FileName || !*FileName || !TAP_Hdd_Exist(FileName) || !AttrName || !*AttrName)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  memset(AbsFileName, 0, sizeof(AbsFileName));
  strcpy(AbsFileName, TAPFSROOT);
  HDD_TAP_GetCurrentDir(&AbsFileName[strlen(AbsFileName)]);
  if(AbsFileName[strlen(AbsFileName) - 1] != '/') strcat(AbsFileName, "/");
  strcat(AbsFileName, FileName);
  ret = ExtAttribExistsAbsPath(AbsFileName, AttrName);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
