#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_LegendButton(dword Line, tButtonIcon ButtonIcon, char *Text)
{
  TRACEENTER;

  if(OSDMenuKeyboard_NrButtons < 20)
  {
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Line = Line;
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].ButtonIcon = ButtonIcon;
    strncpy(OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Text, Text, 20);
    OSDMenuKeyboard_Buttons[OSDMenuKeyboard_NrButtons].Text[19] = '\0';

    OSDMenuKeyboard_NrButtons++;
  }

  TRACEEXIT;
}
