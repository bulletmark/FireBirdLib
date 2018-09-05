#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include "libFireBird.h"

bool ExtAttribGet(char *FileName, char *AttrName, byte *Data, int MaxDataLen, int *DataLen)
{
  TRACEENTER;

  char                  FullAttrName[128];
  char                  AbsFileName[FBLIB_DIR_SIZE];
  int                   f, i;

  if(!FileName || !*FileName || !AttrName || !*AttrName)
  {
    if(DataLen) *DataLen = 0;

    TRACEEXIT;
    return FALSE;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
  if(*AbsFileName)
  {
    f = open(AbsFileName, O_RDWR, 0600);
    if(f >= 0)
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

        TRACEEXIT;
        return TRUE;
      }
      close(f);
    }
  }

  if(DataLen) *DataLen = 0;

  TRACEEXIT;
  return FALSE;
}
