#include                "FBLib_tapcom.h"

TAPCOM_Channel TAPCOM_OpenChannel(dword TargetID, dword ServiceID, dword ParamBlockVersion, void *ParamBlock)
{
  TRACEENTER();

  TAPCOM_InternalMesBuf *mesBuf = NULL;

  if(!LibInitialized) InitTAPex();
  if(!LibInitialized)
  {
    TRACEEXIT();
    return NULL;
  }

  mesBuf = (TAPCOM_InternalMesBuf *) TAP_MemAlloc_Chk("TAPCOM_OpenChannel", sizeof(TAPCOM_InternalMesBuf));

  if(mesBuf)
  {
    // Speicherbereich f�r Nachrichtenaustausch anlegen
    mesBuf->tapcomSignature     = TAPCOM_SIGNATURE;
    mesBuf->tapcomVersion       = TAPCOM_VERSION;
    mesBuf->ServerAlive         = 0;
    mesBuf->FromID              = __tap_ud__;
    mesBuf->ToID                = TargetID;
    mesBuf->ServiceID           = ServiceID;
    mesBuf->ParamBlockVersion   = ParamBlockVersion;
    mesBuf->ParamBlock          = ParamBlock;
    mesBuf->Status              = TAPCOM_Status_OPEN;
    mesBuf->ReturnVal           = 0;
    mesBuf->Reserved            = 0;

    //Existiert der Ziel-Server �berhaupt?
    if((TargetID != TAPCOM_App_BROADCAST) && !HDD_TAP_isRunning(TargetID))
    {
      mesBuf->Status = TAPCOM_Status_SERVER_NOT_AVAILABLE;
    }
    else
    {
      // TAPCOM Event mit der Adresse des Message-Buffers versenden.
      HDD_TAP_SendEvent(TargetID, FALSE, EVT_TAPCOM, (dword) mesBuf, 0);
    }
  }

  TRACEEXIT();
  return (TAPCOM_Channel) mesBuf;
}
