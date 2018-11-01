#include "libFireBird.h"

bool isInfoBoxVisible(void)
{
  TRACEENTER();

  byte                 *iboxTimerId;

  iboxTimerId = (byte*)FIS_vIboxTimerId();
  if(!iboxTimerId)
  {
    TRACEEXIT();
    return FALSE;
  }

  TRACEEXIT();
  return (*iboxTimerId != 0xff);
}
