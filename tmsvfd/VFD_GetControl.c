#include                "FBLib_tmsvfd.h"

bool  VFDUsedByTAP = FALSE;
byte *grid = NULL;

bool VFD_GetControl(bool GiveControl)
{
  TRACEENTER();

  void (*ApplNewVfd_Start)(void);
  void (*ApplNewVfd_Stop)(void);

  if(VFDUsedByTAP == GiveControl)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(GiveControl)
  {
    ApplNewVfd_Stop = (void*)FIS_fwApplVfdStop();
    if(!ApplNewVfd_Stop)
    {
      TRACEEXIT();
      return FALSE;
    }
    ApplNewVfd_Stop();
  }
  else
  {
    ApplNewVfd_Start = (void*)FIS_fwApplVfdStart();
    if(!ApplNewVfd_Start)
    {
      TRACEEXIT();
      return FALSE;
    }

    ApplNewVfd_Start();
  }

  VFDUsedByTAP = GiveControl;

  TRACEEXIT();
  return TRUE;
}
