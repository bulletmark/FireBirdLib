#include "../libFireBird.h"

bool isInfoBoxVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isInfoBoxVisible");
  #endif

  byte                 *iboxTimerId;

  iboxTimerId = (byte*)FIS_vIboxTimerId();
  if(!iboxTimerId)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (*iboxTimerId != 0xff);
}
