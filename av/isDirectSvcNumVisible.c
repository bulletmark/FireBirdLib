#include "libFireBird.h"

bool isDirectSvcNumVisible(void)
{
  TRACEENTER();

  byte                 *id;
  bool                  ret;

  id = (byte*)FIS_vDirectSvcNumTimerId();

  ret = FALSE;
  if(id) ret = (*id != 0xff);

  TRACEEXIT();
  return ret;
}
