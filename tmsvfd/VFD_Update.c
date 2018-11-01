#include                "FBLib_tmsvfd.h"

bool VFD_Update(void)
{
  TRACEENTER();

  void (*Vfd_SendData)(void) = (void*)FIS_fwApplVfdSendData();

  if(!VFDUsedByTAP || !Vfd_SendData)
  {
    TRACEEXIT();
    return FALSE;
  }

  Vfd_SendData();

  TRACEEXIT();
  return TRUE;
}
