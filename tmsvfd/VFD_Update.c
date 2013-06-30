#include                "FBLib_tmsvfd.h"

bool VFD_Update(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_Update");
  #endif

  void (*Vfd_SendData)(void) = (void*)FIS_fwApplVfdSendData();

  if(!VFDUsedByTAP || !Vfd_SendData)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  Vfd_SendData();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
