#include                <string.h>
#include                "../libFireBird.h"

bool StringDBDel(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBDel");
  #endif

  dword                 l;
  char                 *s, *d;

  if(!StringDB || !StringDB->DBPtr)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(StringDB->DBPtr >= StringDB->DBEnd)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  l = strlen(StringDB->DBPtr) + 1;
  d = StringDB->DBPtr;
  s = StringDBGet(StringDB, StringDBNext(StringDB));
  StringDB->DBPtr = d;

  while(s < StringDB->DBEnd)
  {
    if(d < StringDB->DBEnd)
      *s = *d;
    else
      *s = '\0';

    s++;
    d++;
  }

  StringDB->DBEnd = StringDB->DBEnd - l;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
