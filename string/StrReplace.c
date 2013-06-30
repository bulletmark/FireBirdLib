#include                <string.h>
#include                "../libFireBird.h"

bool StrReplace(char *String, char *Find, char *Replace)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StrReplace");
  #endif

  int                   FindLen, ReplaceLen;
  char                 *p;
  bool                  ret = FALSE;

  //No NULL pointers?
  if(!String || !Find || !Replace)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //No empty strings? Replace may be empty
  if(!String[0] || !Find[0])
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //At least one match?
  if(!strstr(String, Find))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  FindLen = strlen(Find);
  ReplaceLen = strlen(Replace);
  if(FindLen >= ReplaceLen)
  {
    //The result won't be larger than the original, so we can directly use the source buffer
    p = String;
    do
    {
      p = strstr(p, Find);
      if(p)
      {
        ret = TRUE;
        TAP_MemCpy(p, Replace, ReplaceLen);
        strcpy(p + ReplaceLen, p + FindLen);
        p += ReplaceLen;
      }
    } while(p);
  }
  else
  {
    char *TempBuffer, *s, *d;
    int   NrOfOccurences, l;

    //Count the number of hits to calculate the buffer size
    NrOfOccurences = 0;
    p = String;
    do
    {
      p = strstr(p, Find);
      if(p)
      {
        ret = TRUE;
        NrOfOccurences++;
        p += FindLen;
      }
    } while(p);

    l = strlen(String) + NrOfOccurences*(ReplaceLen - FindLen) + 2;
    TempBuffer = TAP_MemAlloc(l);
    memset(TempBuffer, 0, l);

    s = String;
    p = String;
    d = TempBuffer;
    do
    {
      p = strstr(p, Find);
      if(p)
      {
        TAP_MemCpy(d, s, p - s);
        d += (p - s);
        TAP_MemCpy(d, Replace, ReplaceLen);
        d += ReplaceLen;

        p += FindLen;
        s = p;
      }
    } while(p);
    strcpy(d, s);

    strcpy(String, TempBuffer);
    TAP_MemFree(TempBuffer);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
