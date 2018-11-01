#include "FBLib_av.h"
#include "libFireBird.h"

byte TunerGet(int MainSub)
{
  TRACEENTER();

  //Parameter sanity check
  if(MainSub != CHANNEL_Main && MainSub != CHANNEL_Sub)
  {
    TRACEEXIT();
    return -1;
  }

  //Has been forgotten :-)
  extern unsigned char (*TAP_GetActiveTuner)(unsigned char);

  TRACEEXIT();
  return TAP_GetActiveTuner(MainSub);
}
