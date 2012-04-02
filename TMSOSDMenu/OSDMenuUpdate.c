#include                "FBLib_TMSOSDMenu.h"

void OSDMenuUpdate(bool SuppressOSDSync)
{
  //Create an OSD region if not already available
  if(OSDRgn == 0)
  {
    OSDDirty     = TRUE;
    TitleDirty   = TRUE;
    ListDirty    = TRUE;
    ButtonsDirty = TRUE;
    LogoDirty    = TRUE;
    OSDRgn = TAP_Osd_Create(0, 0, 720, 576, 0, 0);
    TAP_ExitNormal();
  }

  //Draw background & grey rectangles
  if(OSDDirty) OSDDrawBackground();

  //Draw left and right title
  if(TitleDirty) OSDDrawTitle();

  //Draw software icon
  if(LogoDirty) OSDDrawLogo();

  //Draw buttons
  if(ButtonsDirty) OSDDrawButtons();

  //Calculate TopIndex & SelectionIndex
  OSDCalcIndices();

  //Draw selection bar
  //Calculate max width of all item's texts
  //Draw item numbers, icons & text
  //Draw value text and arrows
  if(ListDirty)
  {
    OSDDrawScrollBar();
    switch(Menu[CurrentMenuLevel].OSDMenuDisplayMode)
    {
      case OMDM_Standard: OSDDrawList(); break;
      case OMDM_Memo:     OSDDrawMemo(); break;
    }
  }

  //Show OSD
  if(!SuppressOSDSync) TAP_Osd_Sync();
}
