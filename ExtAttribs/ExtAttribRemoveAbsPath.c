#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribRemoveAbsPath(char *AbsFileName, char *AttrName)
{
  char                  FullAttrName[128];
  int                   f;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName) return FALSE;

  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    TAP_SPrint(FullAttrName, "user.%s", AttrName);
    fremovexattr(f, FullAttrName);
    close(f);
    return TRUE;
  }

  return FALSE;
}
