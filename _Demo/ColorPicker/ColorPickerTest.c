#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "ColorPickerTest"
#define VERSION         "V0.2"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("ColorPickerTest");
TAP_ETCINFO             (__DATE__);

dword                   Color = 0x00ff0000;
char                    s[24];
bool                    ColorPicker = FALSE;
bool                    DoInit = TRUE;

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) param2;

  if(DoInit)
  {
    OSDMenuInitialize(FALSE, TRUE, FALSE, TRUE, "Color Picker Test", "");
    OSDMenuItemAdd("Dummy entry", "", NULL, NULL, TRUE, FALSE, 0);

    TAP_SPrint(s, "%d, %d, %d", (Color >> 16) & 0xff, (Color >> 8) & 0xff, Color & 0xff);
    OSDMenuItemAdd("\x5Änderbare Farbe", s, NULL, NULL, TRUE, FALSE, 0);
    OSDMenuItemModifyColorPatch(1, Color | 0x80000000);

    OSDMenuItemAdd("Exit", "", NULL, NULL, TRUE, FALSE, 0);

    OSDMenuUpdate(FALSE);
    DoInit = FALSE;
  }

  if(event == EVT_KEY)
  {
    OSDMenuEvent(&event, &param1, &param2);

    if(ColorPicker && !OSDMenuColorPickerIsVisible())
    {
      //The last event has removed the color picker. Update the menu item
      ColorPicker = FALSE;
      Color = OSDMenuColorPickerColor();
      TAP_SPrint(s, "%d, %d, %d", (Color >> 16) & 0xff, (Color >> 8) & 0xff, Color & 0xff);
      OSDMenuItemModifyValue(1, s);
      OSDMenuItemModifyColorPatch(1, Color | 0x80000000);
      OSDMenuUpdate(FALSE);
    }

    if(param1 == RKEY_Ok)
    {
      switch(OSDMenuGetCurrentItem())
      {
        case 0:
          break;

        case 1:
        {
          ColorPicker = TRUE;
          OSDMenuColorPickerShow("Demo", Color);
          break;
        }

        case 2:
        {
          OSDMenuDestroy();
          TAP_Exit();
          break;
        }
      }
    }

    if(param1 == RKEY_Exit)
    {
      OSDMenuDestroy();
      TAP_Exit();
    }

  }

  return 0;
}

int TAP_Main(void)
{
  KeyTranslate(TRUE, &TAP_EventHandler);
  return 1;
}
