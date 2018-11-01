#include <string.h>
#include "FBLib_hdd.h"
#include "libFireBird.h"

bool ChangeDirRoot(void)
{
  TRACEENTER();

  HDD_ChangeDir("/");

  TRACEEXIT();
  return TRUE;
}
