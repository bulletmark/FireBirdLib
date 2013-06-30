#include <string.h>
#include "FBLib_hdd.h"
#include "../libFireBird.h"

bool ChangeDirRoot(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ChangeDirRoot");
  #endif

  HDD_ChangeDir("/");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
