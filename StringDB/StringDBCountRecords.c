#include                "../libFireBird.h"

int StringDBCountRecords(tStringDB *StringDB)
{
  TRACEENTER();

  int                   Cnt;
  char                 *p;

  if(!StringDB)
  {
    TRACEEXIT();
    return 0;
  }

  p = StringDB->DB;
  if(!p)
  {
    TRACEEXIT();
    return 0;
  }

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

  TRACEEXIT();
  return Cnt;
}
