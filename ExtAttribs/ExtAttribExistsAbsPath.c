#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

int ExtAttribExistsAbsPath(char *AbsFileName, char *AttrName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribExistsAbsPath");
  #endif

  char                  FullAttrName[128];
  int                   f, i;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    TAP_SPrint(FullAttrName, "user.%s", AttrName);

    if((i = fgetxattr(f, FullAttrName, NULL, 0)) >= 0)
    {
      close(f);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return i;
    }
    close(f);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
