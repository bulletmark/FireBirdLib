#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribGetAbsPath(char *AbsFileName, char *AttrName, byte *Data, int MaxDataLen, int *DataLen)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribGetAbsPath");
  #endif

  char                  FullAttrName[128];
  int                   f, i;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName)
  {
    if(DataLen) *DataLen = 0;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    //Get the size of the data
    TAP_SPrint(FullAttrName, "user.%s", AttrName);
    if((i = fgetxattr(f, FullAttrName, NULL, 0)) >= 0)
    {
      //Read the data
      if(i > MaxDataLen) i = MaxDataLen;
      fgetxattr(f, FullAttrName, Data, i);
      if(DataLen) *DataLen = i;
      close(f);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }
    close(f);
  }

  if(DataLen) *DataLen = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
