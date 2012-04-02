#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuButtonColor(dword Color)
{
  ButtonColor = (Color != 0 ? Color : RGB(230, 230, 250));
}
