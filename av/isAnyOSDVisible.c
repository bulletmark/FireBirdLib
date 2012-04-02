#include "../libFireBird.h"

bool isAnyOSDVisible(dword checkX, dword checkY, dword checkW, dword checkH)
{
  return isAnyOSDVisibleEx(checkX, checkY, checkW, checkH, TAP_PLANE);
}
