#include                "../libFireBird.h"

tBootReason BootReason(void)
{
  TRACEENTER();

  tBootReason ret;

  volatile word *reason = (word *)FIS_vBootReason();
  ret = (reason ? (tBootReason)*reason : BOOT_FRONT_PANEL);

  TRACEEXIT();
  return ret;
}
