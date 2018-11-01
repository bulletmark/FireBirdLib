#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "FBLib_ini.h"
#include "libFireBird.h"

byte INIGetHexByte(char *Key, byte DefaultValue, byte MinValue, byte MaxValue)
{
  TRACEENTER();

  char                  *i = NULL, *j = NULL, *k;
  char                  TempKey[80];
  byte                  l, x;

  if(!Key)
  {
    TRACEEXIT();
    return 0;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");
  l = strlen(TempKey);

  INIFindStartEnd(TempKey, &i, &j, l + sizeof(byte) * 2);

  if(!i || !j || (j < i + l))
  {
    TRACEEXIT();
    return DefaultValue;
  }

  for(k = i + l; k <= j; k++)
    if(!isxdigit(*k))
    {
      TRACEEXIT();
      return DefaultValue;
    }

  x = (byte) strtoul(i + l, NULL, 16);

  if(x < MinValue) x = MinValue;
  if(x > MaxValue) x = MaxValue;

  TRACEEXIT();
  return x;
}
