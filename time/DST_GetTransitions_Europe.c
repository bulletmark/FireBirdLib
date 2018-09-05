#include                "FBLib_time.h"

void DST_GetTransitions_Europe(dword *DSTStartUTC, dword *DSTEndUTC, dword StartDate)
{
  TRACEENTER;

  dword       DSTStartLocal, DSTEndLocal;
  short       TZOffset;

  //DST starts at the last Sunday in March, 02:00 local
  DSTStartLocal = DST_CalcTransition(5, 6, 3, 2, 0, StartDate);

  //DST ends at the last Sunday in October, 03:00 local
  DSTEndLocal = DST_CalcTransition(5, 6, 10, 3, 0, StartDate);

  //Get the Toppy's standard time zone
  GetCurrentTimeZone(&TZOffset, NULL);

  //Convert from local to UTC times
  if(DSTStartUTC) *DSTStartUTC = AddTime(DSTStartLocal, -TZOffset);
  if(DSTEndUTC) *DSTEndUTC = AddTime(DSTEndLocal, -TZOffset);

  TRACEEXIT;
}
