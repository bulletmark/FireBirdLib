#include <string.h>
#include <stdlib.h>
#include "FBLib_ini.h"
#include "libFireBird.h"

void INISetString(char *Key, char *Value)
{
  TRACEENTER;

  char                  *i = NULL, *j = NULL;
  char                  TempKey[80];
  char                  *OldBuffer, *NewBuffer;
  dword                 l, BS = 0;

  if(!Key || !Value || !INIBuffer)
  {
    TRACEEXIT;
    return;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");

  INIFindStartEnd(TempKey, &i, &j, BufferSize);
  if(!i || !j)
  {
    l = strlen(INIBuffer) + strlen(TempKey) + strlen(Value) + 3;

    if(l > BufferSize)
    {
      OldBuffer = INIBuffer;
      BS = ((BufferSize >> 10) + 1) << 10;

      if(l > BS || !(INIBuffer = TAP_MemAlloc(BS)))
      {
        INIBuffer = OldBuffer;

        TRACEEXIT;
        return;
      }

      memset(INIBuffer, 0, BS);
      memcpy(INIBuffer, OldBuffer, BufferSize);
      BufferSize = BS;
      TAP_MemFree(OldBuffer);
    }

    strcat(INIBuffer, TempKey);
    strcat(INIBuffer, Value);
    strcat(INIBuffer, "\x0d\x0a");
  }
  else
  {
    l = strlen(INIBuffer) - (j - i) + strlen(TempKey) + strlen(Value) + 1;

    if(l > BufferSize)
      BS = ((BufferSize >> 10) + 1) << 10;
    else
      BS = BufferSize;

    if(l > BS || !(NewBuffer = TAP_MemAlloc(BS)))
    {
      TRACEEXIT;
      return;
    }

    memset(NewBuffer, 0, BS);
    strncpy(NewBuffer, INIBuffer, i - INIBuffer);
    strcat(NewBuffer, TempKey);
    strcat(NewBuffer, Value);
    strcat(NewBuffer, j + 1);
    TAP_MemFree(INIBuffer);
    INIBuffer = NewBuffer;

    BufferSize = BS;
  }

  TRACEEXIT;
}
