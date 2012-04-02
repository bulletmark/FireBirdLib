#include                "FBLib_debug.h"

void CallTraceEnable (bool Enable)
{
  if(!CallTraceInitialized) CallTraceInit();

  CallTraceEnabled = Enable;
}
