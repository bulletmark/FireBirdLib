#include                "../libFireBird.h"

tBootReason BootReason(void)
{
  volatile word *reason = (word *)FIS_vBootReason();

  return (reason ? (tBootReason)*reason : BOOT_FRONT_PANEL);
}
