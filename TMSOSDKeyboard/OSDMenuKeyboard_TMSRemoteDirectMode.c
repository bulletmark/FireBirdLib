#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_TMSRemoteDirectMode(bool DirectMode)
{
  TRACEENTER;

  TAPCOM_Channel      Channel;

  Channel = TAPCOM_OpenChannel(TMSREMOTETAPID, DirectMode ? TMSREMOTE_TAPCOM_SERVICE_SETDIRECT : TMSREMOTE_TAPCOM_SERVICE_CLEARDIRECT, 0, NULL);
  TAPCOM_CloseChannel(Channel);

  TRACEEXIT;
}
