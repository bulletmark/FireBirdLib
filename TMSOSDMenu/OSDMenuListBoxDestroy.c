#include "FBLib_TMSOSDMenu.h"

void OSDMenuListBoxDestroy (void)
{
  bool destroyable;

  TRACEENTER();

  if (OSDMenuListBoxIsVisible())
  {
    destroyable = (CurrentMenuLevel == 1 && Menu[0].Item == NULL);

    OSDMenuPop();

    if (destroyable) OSDMenuDestroy();
    else OSDMenuUpdate(FALSE);
  }

  TRACEEXIT();
}
