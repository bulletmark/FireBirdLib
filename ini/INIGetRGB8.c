#include <string.h>
#include <stdlib.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_ini.h"
#include "../libFireBird.h"

//Expects 8 bit RGB values

bool INIGetRGB8(char *Key, byte *Red, byte *Green, byte *Blue, dword DefaultValue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetRGB8");
  #endif

  char                  *i = NULL, *j = NULL, *k;
  char                  TempKey[80];
  dword                 l, x;
  size_t                plen;

  if(!Key)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  strncpy(TempKey, Key, sizeof(TempKey) - 2);
  TempKey[sizeof(TempKey) - 2] = '\0';
  strcat(TempKey, "=");
  l = strlen(TempKey);

  INIFindStartEnd(TempKey, &i, &j, l + 14);

  if(!i || !j || (j < i + l)) x = DefaultValue;
  else
  {
    k = i + l;
    x = 0;

    // red
    if((k = ParseLine(k, &plen, ',')) && (plen > 0 && k + plen < j))
    {
      x |= (strtoul(k, NULL, (plen > 2 && tolower(*(k + 1)) == 'x' ? 16 : 10)) & 0xff) << 16;
      k += plen;

      // green
      if((k = ParseLine(k, &plen, ',')) && (plen > 0 && k + plen < j))
      {
        x |= (strtoul(k, NULL, (plen > 2 && tolower(*(k + 1)) == 'x' ? 16 : 10)) & 0xff) << 8;
        k += plen;

        // blue
        if(*k == ',') k++;
        x |= strtoul(k, NULL, (j - k > 2 && tolower(*(k + 1)) == 'x' ? 16 : 10)) & 0xff;
      }
      else x = DefaultValue;
    }
    else x = DefaultValue;
  }

  if(Red)   *Red   = (x >> 16) & 0xff;
  if(Green) *Green = (x >> 8) & 0xff;
  if(Blue)  *Blue  = x & 0xff;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
