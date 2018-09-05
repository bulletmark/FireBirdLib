#include                <stdlib.h>
#include                <fcntl.h>
#include                <unistd.h>
#include                <string.h>
#include                "libFireBird.h"

bool StringDBLoad(tStringDB *StringDB, char *FileName)
{
  TRACEENTER;

  int                   f;
  bool                  ret;
  dword                 l, p;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(!StringDB || !StringDB->DB || !FileName || !*FileName)
  {
    TRACEEXIT;
    return FALSE;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);

  ret = FALSE;
  if(*AbsFileName)
  {
    f = open(AbsFileName, O_RDONLY);
    if(f >= 0)
    {
      TAP_MemFree(StringDB->DB);

      //DB Size
      read(f, &l, sizeof(dword));
      StringDB->DB = TAP_MemAlloc(l);

      if(!StringDB->DB)
      {
        StringDB->DBSize = 0;
        close(f);

        TRACEEXIT;
        return FALSE;
      }
      StringDB->DBSize = l;
      StringDB->DBEnd = l + StringDB->DB - 1;

      //Current pointer
      read(f, &p, sizeof(dword));
      StringDB->DBPtr = p + StringDB->DB;

      read(f, StringDB->DB, l);

      close(f);

      ret = TRUE;
    }
  }

  TRACEEXIT;
  return ret;
}
