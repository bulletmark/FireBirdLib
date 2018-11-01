#include "FBLib_av.h"
#include "libFireBird.h"

//It is not possible to set the tuner for the PIP
bool TunerSet(byte Tuner)
{
  TRACEENTER();

  int                   tvRadio, chNum;
  byte                 *__etcInfo;

  //Parameter sanity check
  if(Tuner > 1)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!(__etcInfo = (byte*)FIS_vEtcInfo()))
  {
    TRACEEXIT();
    return FALSE;
  }

  __etcInfo[0x12 + CHANNEL_Main] = Tuner;
  __etcInfo[0x12 + CHANNEL_Sub]  = 1 - Tuner;

  TAP_Channel_GetCurrent(&tvRadio, &chNum);
  TAP_Channel_Start(CHANNEL_Main, tvRadio, chNum);

  TRACEEXIT();
  return TRUE;
}
