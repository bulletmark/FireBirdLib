#include                <fcntl.h>
#include                <unistd.h>
#include                <string.h>
#include                "libFireBird.h"

bool StringDBSave(tStringDB *StringDB, char *FileName)
{
  TRACEENTER();

  int                   f;
  bool                  ret;
  dword                 l, p;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(!StringDB || !StringDB->DB || !FileName || !*FileName)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);

  ret = FALSE;
  if(*AbsFileName)
  {
    f = open(AbsFileName, O_WRONLY | O_CREAT | O_TRUNC);
    if(f >= 0)
    {
      //DB Size
      l = StringDB->DBEnd - StringDB->DB + 1;
      write(f, &l, sizeof(dword));

      //Current pointer
      p = StringDB->DBPtr - StringDB->DB;
      write(f, &p, sizeof(dword));

      write(f, StringDB->DB, l);

      close(f);

      ret = TRUE;
    }
  }

  TRACEEXIT();
  return ret;
}
