#include                "../libFireBird.h"

void TAP_EnterNormalNoInfo(void)
{
 void (*_EnterNormal)(byte);

  _EnterNormal = (void*)FIS_fwAppl_EnterNormal();
  if(_EnterNormal) _EnterNormal(0);
}
