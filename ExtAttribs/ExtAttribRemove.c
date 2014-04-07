#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribRemove(char *FileName, char *AttrName)
{
  TRACEENTER();

  char                  FullAttrName[128];
  char                  AbsFileName[FBLIB_DIR_SIZE];
  int                   f;

  if(!FileName || !*FileName || !AttrName || !*AttrName)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
  if(*AbsFileName)
  {
    f = open(AbsFileName, O_RDWR, 0600);
    if(f >= 0)
    {
      TAP_SPrint(FullAttrName, "user.%s", AttrName);
      fremovexattr(f, FullAttrName);
      close(f);

      TRACEEXIT();
      return TRUE;
    }
  }

  TRACEEXIT();
  return FALSE;
}
