#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_TMSRemoteDirectMode(bool DirectMode)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_TMSRemoteDirectMode");
  #endif

  TAPCOM_Channel      Channel;

  Channel = TAPCOM_OpenChannel(TMSREMOTETAPID, DirectMode ? TMSREMOTE_TAPCOM_SERVICE_SETDIRECT : TMSREMOTE_TAPCOM_SERVICE_CLEARDIRECT, 0, NULL);
  TAPCOM_CloseChannel(Channel);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
