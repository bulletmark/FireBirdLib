#include                "libFireBird.h"

void DevFront_SetIrCode(byte Index, byte Active, byte MfgID1, byte MfgID2, byte Code0a)
{
  TRACEENTER;

  void (*DevFront_SetIrCode)(byte Index, byte Active, byte MfgID1, byte MfgID2, byte Code0a);

  DevFront_SetIrCode = (void*)FIS_fwSetIrCode();
  if(DevFront_SetIrCode) DevFront_SetIrCode(Index, Active, MfgID1, MfgID2, Code0a);

  TRACEEXIT;
}
