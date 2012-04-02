#include <string.h>
#include "FBLib_hdd.h"
#include "../libFireBird.h"

bool ChangeDirRoot (void)
{
  HDD_ChangeDir("/");
  return TRUE;
}
