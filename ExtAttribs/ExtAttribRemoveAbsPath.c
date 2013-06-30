#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribRemoveAbsPath(char *AbsFileName, char *AttrName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ExtAttribRemoveAbsPath");
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
    fremovexattr(f, FullAttrName);
    close(f);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
