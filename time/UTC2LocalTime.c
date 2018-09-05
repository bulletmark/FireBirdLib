#include                "FBLib_time.h"

dword UTC2LocalTime(dword UTCTime, short *Offset)
{
  TRACEENTER;

  short                 StdOffset, DSTOffset;
  dword                 DSTStartUTC, DSTEndUTC;
  bool                  DST;
  dword                 ret;

  if(DSTRule == DSTR_Undefined) DST_GetDefaultDSTRule();

  //Read the timezone settings from the flash
  if(!GetCurrentTimeZone(&StdOffset, &DST)) StdOffset = 60;

  switch(DSTRule)
  {
    case DSTR_Undefined:
    case DSTR_Firmware:
    {
      //This one uses the "cheap" solution from the firmware. A look-ahead is not possible.
      if(Offset) *Offset = StdOffset + (DST ? 60 : 0);

      ret = Appl_TimeToLocal(UTCTime);

      TRACEEXIT;
      return ret;
    }

    case DSTR_Europe:
    {
      DST_GetTransitions_Europe(&DSTStartUTC, &DSTEndUTC, UTCTime);
      break;
    }

    case DSTR_Manual:
    {
      //Takes the rule out of DST.ini
      DST_GetTransitions_Manual(&DSTStartUTC, &DSTEndUTC);
      break;
    }
  }

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

    //Is UTCTime in standard TZ?
    if((UTCTime >= DSTEndUTC) && (UTCTime < DSTStartUTC)) DSTOffset = 0;
  }

  if(Offset) *Offset = StdOffset + DSTOffset;
  ret = AddTime(UTCTime, StdOffset + DSTOffset);

  TRACEEXIT;
  return ret;
}
