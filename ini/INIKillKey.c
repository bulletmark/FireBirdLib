#include <string.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

void INIKillKey(char *Key)
{
  TRACEENTER();

  char                  *i = NULL, *j = NULL;
  char                  TempKey[80];
  char                  *NewBuffer;

  if(!Key || !INIBuffer)
  {
    TRACEEXIT();
    return;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");

  INIFindStartEnd(TempKey, &i, &j, BufferSize);

  if(i && j)
  {
    NewBuffer = malloc(BufferSize);
    if(!NewBuffer)
    {
      TRACEEXIT();
      return;
    }
    memset(NewBuffer, 0, BufferSize);
    strncpy(NewBuffer, INIBuffer, i - INIBuffer);
    if(*j && (j[1] == '\r')) j++;
    if(*j && (j[1] == '\n')) j++;
    strcat(NewBuffer, ++j);
    free(INIBuffer);
    INIBuffer = NewBuffer;
  }

  TRACEEXIT();
}
