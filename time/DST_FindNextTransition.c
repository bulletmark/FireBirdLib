#include                "FBLib_time.h"

dword DST_FindNextTransition(void)
{
  TRACEENTER;

  dword                 DSTStartUTC, DSTEndUTC;
  dword                 ret;

  if(DSTRule == DSTR_Undefined) DST_GetDefaultDSTRule();

  ret = 0;
  switch(DSTRule)
  {
    case DSTR_Undefined:
    case DSTR_Firmware:
    {
      break;
    }

    case DSTR_Europe:
    {
      DST_GetTransitions_Europe(&DSTStartUTC, &DSTEndUTC, 0);
      ret = (DSTStartUTC < DSTEndUTC) ? DSTStartUTC : DSTEndUTC;
      ret = UTC2LocalTime(ret, NULL);
      break;
    }

    case DSTR_Manual:
    {
      DST_GetTransitions_Manual(&DSTStartUTC, &DSTEndUTC);
      ret = (DSTStartUTC < DSTEndUTC) ? DSTStartUTC : DSTEndUTC;
      ret = UTC2LocalTime(ret, NULL);
      break;
    }
  }

  TRACEEXIT;
  return ret;
}
