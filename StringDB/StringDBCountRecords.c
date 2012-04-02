#include                "../libFireBird.h"

int StringDBCountRecords(tStringDB *StringDB)
{
  int                   Cnt;
  char                 *p;

  if(!StringDB) return 0;

  p = StringDB->DB;
  if(!p) return 0;

  Cnt = 0;
  while(*p)
  {
    Cnt++;
    while(*p)
    {
      p++;
    }
    p++;
  }

  return Cnt;
}
