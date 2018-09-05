#include                "FBLib_time.h"

dword LocalTime2UTC(dword LocalTime, short *Offset)
{
  TRACEENTER;

  bool                  DST;
  short                 StdOffset, DSTOffset;
  dword                 UTCTime, DSTStartUTC, DSTEndUTC;
  dword                 ret;

  if(DSTRule == DSTR_Undefined) DST_GetDefaultDSTRule();

  if(!GetCurrentTimeZone(&StdOffset, &DST)) StdOffset = 60;

  switch(DSTRule)
  {
    case DSTR_Undefined:
    case DSTR_Firmware:
    {
      UTCTime = AddTime(LocalTime, -StdOffset);
      if(DST) UTCTime = AddTime(UTCTime, -60);

      TRACEEXIT;
      return UTCTime;
    }

    case DSTR_Europe:
    {
      DST_GetTransitions_Europe(&DSTStartUTC, &DSTEndUTC, LocalTime);
      break;
    }

    case DSTR_Manual:
    {
      DST_GetTransitions_Manual(&DSTStartUTC, &DSTEndUTC);
      break;
    }
  }

  //The local to UTC conversion has to be done in three steps.
  //1.: the standard offset will be subtracted to get at least near to UTC
  //2.: check against the transition times to determine if LocalTime is within the DST zone
  //3.: if necessary, subtract the DST offset
  UTCTime = AddTime(LocalTime, -StdOffset);
  if(DSTStartUTC < DSTEndUTC)
  {
    //We are currently in standard time
    DSTOffset = 0;

    //Is UTCTime in DST?
    if((UTCTime >= DSTStartUTC) && (UTCTime < DSTEndUTC)) DSTOffset = 60;
  }
  else
  {
    //We are currently in DST
    DSTOffset = 60;

    //Is UTCTime outside of the DST zone?
    if((UTCTime >= DSTEndUTC) && (UTCTime < DSTStartUTC)) DSTOffset = 0;
  }

  if(Offset) *Offset = StdOffset + DSTOffset;
  ret = AddTime(UTCTime, -DSTOffset);

  TRACEEXIT;
  return ret;
}
