#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "../libFireBird.h"

int ExtAttribExistsAbsPath(char *AbsFileName, char *AttrName)
{
  char                  FullAttrName[128];
  int                   f, i;

  if(!AbsFileName || !*AbsFileName || !AttrName || !*AttrName) return 0;

  f = open(AbsFileName, O_RDWR, 0600);
  if(f)
  {
    TAP_SPrint(FullAttrName, "user.%s", AttrName);

    if((i = fgetxattr(f, FullAttrName, NULL, 0)) >= 0)
    {
      close(f);
      return i;
    }
    close(f);
  }

  return 0;
}
