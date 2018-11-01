#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_ini.h"
#include                "libFireBird.h"

char                    *INIBuffer = NULL, *INICommentBuffer = NULL;
dword                   BufferSize = 0;

INILOCATION INIOpenFile(char *FileName, char *AppName)
{
  TRACEENTER();

  TYPE_File             *f;
  dword                 flen, ret = 0;
  INILOCATION           INILocation;

  HDD_TAP_PushDir();
  INILocation = INILocateFile(FileName, AppName);

  if(INILocation == INILOCATION_NotFound)
  {
    HDD_TAP_PopDir();
    BufferSize = 512;
    if(!(INIBuffer = TAP_MemAlloc(BufferSize)))
    {
      TRACEEXIT();
      return INILOCATION_NotFound;
    }

    memset(INIBuffer, 0, BufferSize);

    TRACEEXIT();
    return INILOCATION_NewFile;
  }

  f = TAP_Hdd_Fopen(FileName);
  if(f == NULL)
  {
    HDD_TAP_PopDir();

    TRACEEXIT();
    return INILOCATION_NotFound;
  }

  flen = TAP_Hdd_Flen(f);
  BufferSize = (((flen >> 9) + 2) << 9);

  INIBuffer = TAP_MemAlloc(BufferSize);
  if(INIBuffer)
  {
    memset(INIBuffer, 0, BufferSize);
    ret = TAP_Hdd_Fread(INIBuffer, flen, 1, f);
    flen = strlen(INIBuffer);
    if (flen && (INIBuffer[flen - 1] != '\x0d' && INIBuffer[flen - 1] != '\x0a'))
      strcat(INIBuffer, "\x0d\x0a");
  }
  TAP_Hdd_Fclose(f);

  if(INIBuffer && !flen)
  {
    strcat(INIBuffer, "\x0d\x0a");
    ret = 1;
  }

  HDD_TAP_PopDir();

  TRACEEXIT();
  return (INIBuffer && (ret > 0) ? INILocation : INILOCATION_NotFound);
}
