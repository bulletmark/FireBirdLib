#include                "FBLib_tmsvfd.h"

bool  VFDUsedByTAP = FALSE;
byte *grid = NULL;

bool VFD_GetControl(bool GiveControl)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_GetControl");
  #endif

  void (*ApplNewVfd_Start)(void);
  void (*ApplNewVfd_Stop)(void);

  if(VFDUsedByTAP == GiveControl)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(GiveControl)
  {
    ApplNewVfd_Stop = (void*)FIS_fwApplVfdStop();
    if(!ApplNewVfd_Stop)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return FALSE;
    }
    ApplNewVfd_Stop();
  }
  else
  {
    ApplNewVfd_Start = (void*)FIS_fwApplVfdStart();
    if(!ApplNewVfd_Start)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return FALSE;
    }

    ApplNewVfd_Start();
  }

  VFDUsedByTAP = GiveControl;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
