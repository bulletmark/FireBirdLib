#include "libFireBird.h"

bool isAnyOSDVisible(dword CheckX, dword CheckY, dword CheckW, dword CheckH)
{
  TRACEENTER();

  bool ret = isAnyOSDVisibleEx(CheckX, CheckY, CheckW, CheckH, TAP_PLANE);

  TRACEEXIT();
  return ret;
}
