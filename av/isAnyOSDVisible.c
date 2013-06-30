#include "../libFireBird.h"

bool isAnyOSDVisible(dword CheckX, dword CheckY, dword CheckW, dword CheckH)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isAnyOSDVisible");
  #endif

  bool ret = isAnyOSDVisibleEx(CheckX, CheckY, CheckW, CheckH, TAP_PLANE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
