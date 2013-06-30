#include                <string.h>
#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "OSDKeyboard Demo"
#define VERSION         "V0.2"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("OSDKeyboard Demo");
TAP_ETCINFO             (__DATE__);

char                    Text[100];

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) param2;

  //The event handler returns true if the user has clicked exit
  //The keyboard does not enter normal mode if the Toppy wasn't in normal during the first call of the event handler
  //It's the responsibility of the caller to restore the OSD. The keyboard deletes its OSD region but doesn't do any OSD update.
  if(OSDMenuKeyboard_EventHandler(&event, &param1, &param2))
  {
    //Output the text on the telnet console and exit the demo
    TAP_PrintNet("OSD Keyboard = '%s'\n", Text);
    DumpMemory(Text, strlen(Text), 16);
    TAP_Exit();
  }

  //Do not pass any key events to the next TAP / the firmware
  if(event == EVT_KEY) param1 = 0;

  return param1;
}

int TAP_Main(void)
{
  KeyTranslate(TRUE, &TAP_EventHandler);

  strcpy(Text, "Test");

  //Initialize the Keyboard
  //Right now, there is no save or exit. Whenever the remote control's exit is clicked, the contents of the textbox will be copied into the destination variable.
  OSDMenuKeyboard_Setup("Keyboard Test", Text, sizeof(Text));
  OSDMenuKeyboard_LegendButton(1, BI_Exit, "Exit Keyboard");

  return 1;
}
