#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribSet(char *FileName, char *AttrName, byte *Data, int DataLen)
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
      if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_CREATE) == 0)
      {
        close(f);

        TRACEEXIT();
        return TRUE;
      }
      else
      {
        //As the attribute may already exist, retry with the replace flag
        if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_REPLACE) == 0)
        {
          close(f);

          TRACEEXIT();
          return TRUE;
        }
      }
      close(f);
    }
  }

  TRACEEXIT();
  return FALSE;
}
