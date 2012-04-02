#include "../libFireBird.h"

inline dword FIS_fwDevFront_PowerOffReply(void)
{
  static dword          fwDevFront_PowerOffReply = 0;

  if (!fwDevFront_PowerOffReply)
    fwDevFront_PowerOffReply = TryResolve("DevFront_PowerOffReply");

  return fwDevFront_PowerOffReply;
}
