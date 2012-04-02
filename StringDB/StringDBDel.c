#include                <string.h>
#include                "../libFireBird.h"

bool StringDBDel(tStringDB *StringDB)
{
  dword                 l;
  char                 *s, *d;

  if(!StringDB || !StringDB->DBPtr) return FALSE;

  if(StringDB->DBPtr >= StringDB->DBEnd) return TRUE;

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

  return TRUE;
}
