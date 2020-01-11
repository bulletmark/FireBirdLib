#include "FBLib_TMSOSDMenu.h"

void OSDMenuListBoxDestroyNoOSDUpdate (void)
{
  bool destroyable;

  TRACEENTER();

  if (OSDMenuListBoxIsVisible())
  {
    destroyable = (CurrentMenuLevel == 1 && Menu[0].Item == NULL);

    OSDMenuPop();

    if (destroyable) OSDMenuDestroyNoOSDUpdate();
  }

  TRACEEXIT();
}
