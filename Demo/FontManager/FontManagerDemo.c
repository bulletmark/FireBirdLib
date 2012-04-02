#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "FontManager Demo"
#define VERSION         "V0.2"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("FontManager Demo");
TAP_ETCINFO             (__DATE__);

#include                "Brush_Script_MT_18.c"

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  static word           OSDRgn = 0;
  static bool           Init = TRUE;

  tFontData             LCD_18;

  (void) param2;

  if(Init)
  {
    Init = FALSE;

    //OSD erzeugen und Text schreiben
    if(OSDRgn) TAP_Osd_Delete(OSDRgn);
    OSDRgn = TAP_Osd_Create(0, 0, 720, 576, 0, TAP_PLANE);
    TAP_Osd_FillBox(OSDRgn, 0, 0, 720, 576, 0xff202020);

    FM_PutString(OSDRgn, 60, 100, 600, "Brush Script compiled into the demo TAP", ARGB(255,0,0,4), 0xffffff00, &Brush_Script_MT_18_FontData, FALSE, ALIGN_LEFT);
    FM_PutString(OSDRgn, 60, 130, 600, "Brush Script compiled into the demo TAP", ARGB(255,0,122,4), 0xffffff00, &Brush_Script_MT_18_FontData, FALSE, ALIGN_CENTER);
    FM_PutString(OSDRgn, 60, 160, 600, "Brush Script compiled into the demo TAP", ARGB(255,122,0,4), 0xffffff00, &Brush_Script_MT_18_FontData, FALSE, ALIGN_RIGHT);

    if(FM_LoadFontFile("LCD_18.fnt", &LCD_18))
    {
      FM_PutString(OSDRgn, 60, 220, 719, "LCD 18pt from a font file", ARGB(255,0,192,255), 0x00000000, &LCD_18, FALSE, ALIGN_LEFT);

      FM_PutString(OSDRgn, 60, 250, 719, "LCD 18pt from a font file", COLOR_White , RGB(16,16,16), &LCD_18, FALSE, ALIGN_LEFT);
      FM_PutString(OSDRgn, 60, 280, 719, "LCD 18pt from a font file", COLOR_White , RGB(30,30,30), &LCD_18, FALSE, ALIGN_LEFT);
      FM_PutString(OSDRgn, 60, 310, 719, "LCD 18pt from a font file", COLOR_White , RGB(80,80,80), &LCD_18, FALSE, ALIGN_LEFT);

      FM_FreeFontFile(&LCD_18);
    }

    TAP_Osd_Sync();
  }

  if(event == EVT_KEY)
  {
    if(param1 == RKEY_Exit)
    {
      if(OSDRgn) TAP_Osd_Delete(OSDRgn);
      TAP_Osd_Sync();
      TAP_Exit();
    }
    param1 = 0;
  }

  return param1;
}

int TAP_Main(void)
{
  return 1;
}
