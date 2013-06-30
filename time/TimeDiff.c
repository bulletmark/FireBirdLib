#include "../libFireBird.h"

long TimeDiff(dword FromTime, dword ToTime)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TimeDiff");
  #endif

  bool      TimeTravel;
  dword     temp;
  int       dDate, dHour, dMin;
  long      ret;

  if((TimeTravel = (FromTime > ToTime)))
  {
    temp = FromTime;
    FromTime = ToTime;
    ToTime = temp;
  }

  dDate = (ToTime >> 16) - (FromTime >> 16);
  dHour = ((ToTime >> 8) & 0xff) - ((FromTime >> 8) & 0xff);
  dMin = (ToTime & 0xff) - (FromTime  & 0xff);

  if(dMin < 0)
  {
    dHour--;
    dMin += 60;
  }

  if(dHour < 0)
  {
    dDate--;
    dHour += 24;
  }

  ret = (dDate * 1440 + dHour * 60 + dMin) * (TimeTravel ? -1 : 1);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
