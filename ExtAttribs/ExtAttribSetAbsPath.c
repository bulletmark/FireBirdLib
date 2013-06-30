#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribSetAbsPath(char *AbsFileName, char *AttrName, byte *Data, int DataLen)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribSetAbsPath");
  #endif

  char                  FullAttrName[128];
  int                   f;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    TAP_SPrint(FullAttrName, "user.%s", AttrName);

    if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_CREATE) == 0)
    {
      close(f);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }
    else
    {
      //As the attribute may already exist, retry with the replace flag
      if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_REPLACE) == 0)
      {
        close(f);

        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return TRUE;
      }
    }
    close(f);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
