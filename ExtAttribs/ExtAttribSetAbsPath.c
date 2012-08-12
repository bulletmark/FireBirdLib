#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

bool ExtAttribSetAbsPath(char *AbsFileName, char *AttrName, byte *Data, int DataLen)
{
  char                  FullAttrName[128];
  int                   f;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName) return FALSE;


  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    TAP_SPrint(FullAttrName, "user.%s", AttrName);

    if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_CREATE) == 0)
    {
      close(f);
      return TRUE;
    }
    else
    {
      //As the attribute may already exist, retry with the replace flag
      if(fsetxattr(f, FullAttrName, Data, DataLen, XATTR_REPLACE) == 0)
      {
        close(f);
        return TRUE;
      }
    }
    close(f);
  }

  return FALSE;
}
