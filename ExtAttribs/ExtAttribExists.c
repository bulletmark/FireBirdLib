#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "libFireBird.h"

int ExtAttribExists(char *FileName, char *AttrName)
{
  TRACEENTER;

  char                  FullAttrName[128];
  char                  AbsFileName[FBLIB_DIR_SIZE];
  int                   f, i;

  if(!FileName || !*FileName || !AttrName || !*AttrName)
  {
    TRACEEXIT;
    return 0;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
  if(*AbsFileName)
  {
    f = open(AbsFileName, O_RDWR, 0600);
    if(f >= 0)
    {
      TAP_SPrint(FullAttrName, "user.%s", AttrName);

      if((i = fgetxattr(f, FullAttrName, NULL, 0)) >= 0)
      {
        close(f);

        TRACEEXIT;
        return i;
      }
      close(f);
    }
  }

  TRACEEXIT;
  return 0;
}
