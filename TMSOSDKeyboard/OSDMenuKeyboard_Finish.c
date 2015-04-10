#include                <stdlib.h>
#include                "FBLib_TMSOSDKeyboard.h"

#undef malloc
#undef free

void OSDMenuKeyboard_Finish(void)
{
  TRACEENTER();

  if(OSDMenuKeyboard_rgn)
  {
    free(OSDMenuKeyboard_StringVar);
    OSDMenuKeyboard_StringVar = NULL;
    free(OSDMenuKeyboard_Title);
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
