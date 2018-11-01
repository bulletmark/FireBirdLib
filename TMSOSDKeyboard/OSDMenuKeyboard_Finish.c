#include                <stdlib.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_Finish(void)
{
  TRACEENTER();

  if(OSDMenuKeyboard_rgn)
  {
    TAP_MemFree(OSDMenuKeyboard_StringVar);
    OSDMenuKeyboard_StringVar = NULL;
    TAP_MemFree(OSDMenuKeyboard_Title);
    OSDMenuKeyboard_Title = NULL;
    OSDMenuKeyboard_GUIInitialized = FALSE;
    TAP_Osd_Delete(OSDMenuKeyboard_rgn);
    OSDMenuKeyboard_rgn = 0;
    if(OSDMenuKeyboard_ReturnToNormal) TAP_EnterNormalNoInfo();
    OSDMenuKeyboard_TMSRemoteDirectMode(FALSE);
    OSDMenuKeyboard_StringVarOrig = NULL;
    FMUC_FreeFontFile(&KeyboardFont_12);
    FMUC_FreeFontFile(&KeyboardFont_14);
  }

  TRACEEXIT();
}
