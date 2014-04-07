#include                <string.h>
#include                "../libFireBird.h"

bool StringDBDel(tStringDB *StringDB)
{
  TRACEENTER();

  dword                 l;
  char                 *s, *d;

  if(!StringDB || !StringDB->DBPtr)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(StringDB->DBPtr >= StringDB->DBEnd)
  {
    TRACEEXIT();
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

  TRACEEXIT();
  return TRUE;
}
