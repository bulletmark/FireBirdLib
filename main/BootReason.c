#include                "../libFireBird.h"

tBootReason BootReason(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("BootReason");
  #endif

  tBootReason ret;

  volatile word *reason = (word *)FIS_vBootReason();
  ret = (reason ? (tBootReason)*reason : BOOT_FRONT_PANEL);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
