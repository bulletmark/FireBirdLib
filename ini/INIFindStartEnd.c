#include <string.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

void INIFindStartEnd (char *Key, char **Start, char **End, dword MaxEntrylen)
{
  char                  *CR, *LF, *p;

  if(!Start || !End || !MaxEntrylen) return;

  if (!INIBuffer)
  {
    *Start = NULL;
    return;
  }

  *End = NULL;
  *Start = INIBuffer - 1;
  do
  {
    *Start = stricstr (*Start + 1, Key);
    if (*Start == NULL) return;
    p = *Start;
    if(*Start > INIBuffer) p--;
  } while((*p == '#') || (*p == ';'));

  CR = strchr (*Start, '\x0d');
  LF = strchr (*Start, '\x0a');

  if(CR)
  {
    if(LF)
    {
      if(CR + 1 == LF)
        *End = CR - 1;      // Windows
      else                  // junk
      {
        *End = LF - 1;
        return;
      }
    }
    else *End = CR - 1;     // Mac
  }
  else
    if(LF)
      *End = LF - 1;        // Unix
    else                    // junk
    {
      *End = NULL;
      return;
    }

  if (*End >= *Start + MaxEntrylen) *End = *Start + MaxEntrylen - 1;
}
