#include                <string.h>
#include                "libFireBird.h"

bool StrReplace(char *String, char *Find, char *Replace)
{
  TRACEENTER;

  int                   FindLen, ReplaceLen;
  char                 *p;
  bool                  ret = FALSE;

  //No NULL pointers?
  if(!String || !Find || !Replace)
  {
    TRACEEXIT;
    return FALSE;
  }

  //No empty strings? Replace may be empty
  if(!String[0] || !Find[0])
  {
    TRACEEXIT;
    return FALSE;
  }

  //At least one match?
  if(!strstr(String, Find))
  {
    TRACEEXIT;
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
    int   NrOfOccurences;

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

    TempBuffer = TAP_MemAlloc(strlen(String) + NrOfOccurences*(ReplaceLen - FindLen) + 1);

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

  TRACEEXIT;
  return ret;
}
