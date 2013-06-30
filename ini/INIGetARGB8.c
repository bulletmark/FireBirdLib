#include <string.h>
#include <stdlib.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_ini.h"
#include "../libFireBird.h"

bool INIGetARGB8(char *Key, byte *Alpha, byte *Red, byte *Green, byte *Blue, dword DefaultValue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INIGetARGB8");
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

  INIFindStartEnd(TempKey, &i, &j, l + 19);

  if(!i || !j || (j < i + l)) x = DefaultValue;
  else
  {
    k = strchr(i + l, ',');

    if(!k || (k > j))
    {
      // old style
      x = (dword) strtoul(i + l, NULL, 16);

    }
    else
    {
      // new style
      k = i + l;
      x = 0;

      // alpha
      if((k = ParseLine(k, &plen, ',')) && (plen > 0 && k + plen < j))
      {
        x |= (strtoul(k, NULL, (plen > 2 && tolower(*(k + 1)) == 'x' ? 16 : 10)) & 0xff) << 24;
        k += plen;

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
      else x = DefaultValue;
    }
  }

  if(Alpha) *Alpha = A8888(x);
  if(Red)   *Red   = R8888(x);
  if(Green) *Green = G8888(x);
  if(Blue)  *Blue  = B8888(x);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
