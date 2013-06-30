#include "../libFireBird.h"

bool isDirectSvcNumVisible(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isDirectSvcNumVisible");
  #endif

  byte                 *id;
  bool                  ret;

  id = (byte*)FIS_vDirectSvcNumTimerId();

  ret = FALSE;
  if(id) ret = (*id != 0xff);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
