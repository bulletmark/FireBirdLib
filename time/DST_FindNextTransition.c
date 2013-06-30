#include                "FBLib_time.h"

dword DST_FindNextTransition(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DST_FindNextTransition");
  #endif

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
      DST_GetTransitions_Europe(&DSTStartUTC, &DSTEndUTC);
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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
