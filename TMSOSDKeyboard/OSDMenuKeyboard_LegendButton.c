#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_LegendButton(dword Line, tButtonIcon ButtonIcon, const char *Text)
{
  TRACEENTER();

  if (Text && (OSDMenuKeyboard_NrButtons < 20))
  {
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Line = Line;
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].ButtonIcon = ButtonIcon;
    strncpy(OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Text, Text, BUTTONTEXTSIZE);
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Text[BUTTONTEXTSIZE - 1] = '\0';

    OSDMenuKeyboard_NrButtons++;
  }

  TRACEEXIT();
}
