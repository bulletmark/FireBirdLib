#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "FontManager Demo"
#define VERSION         "V0.3"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("FontManager Demo Unicode");
TAP_ETCINFO             (__DATE__);

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  static word           OSDRgn = 0;
  static bool           Init = TRUE;

  tFontDataUC           FontBrushScript_18, FontLCD_18;

  (void) param2;

  if(Init)
  {
    Init = FALSE;

    //OSD erzeugen und Text schreiben
    TAP_ExitNormal();
    if(OSDRgn) TAP_Osd_Delete(OSDRgn);
    OSDRgn = TAP_Osd_Create(0, 0, 720, 576, 0, TAP_PLANE);
    TAP_Osd_FillBox(OSDRgn, 0, 0, 720, 576, 0xff202020);

    if(FMUC_LoadFontFile("Brush_Script_MT_18.ufnt", &FontBrushScript_18))
    {
      FMUC_PutString(OSDRgn, 60, 100, 600, "Brush Script from a font file", ARGB(255,0,0,4), 0xffffff00, &FontBrushScript_18, FALSE, ALIGN_LEFT);
      FMUC_PutString(OSDRgn, 60, 130, 600, "Brush Script from a font file", ARGB(255,0,122,4), 0xffffff00, &FontBrushScript_18, FALSE, ALIGN_CENTER);
      FMUC_PutString(OSDRgn, 60, 160, 600, "Brush Script from a font file", ARGB(255,122,0,4), 0xffffff00, &FontBrushScript_18, FALSE, ALIGN_RIGHT);

      FMUC_FreeFontFile(&FontBrushScript_18);
    }

    if(FMUC_LoadFontFile("LCD_18.ufnt", &FontLCD_18))
    {
      FMUC_PutString(OSDRgn, 60, 220, 719, "LCD 18pt from a font file", ARGB(255,0,192,255), 0x00000000, &FontLCD_18, FALSE, ALIGN_LEFT);

      FMUC_PutString(OSDRgn, 60, 250, 719, "LCD 18pt from a font file", COLOR_White , RGB(16,16,16), &FontLCD_18, FALSE, ALIGN_LEFT);
      FMUC_PutString(OSDRgn, 60, 280, 719, "LCD 18pt from a font file", COLOR_White , RGB(30,30,30), &FontLCD_18, FALSE, ALIGN_LEFT);
      FMUC_PutString(OSDRgn, 60, 310, 719, "LCD 18pt from a font file", COLOR_White , RGB(80,80,80), &FontLCD_18, FALSE, ALIGN_LEFT);

      //Some Korean stuff taken from topfield.co.kr
      FMUC_PutString(OSDRgn, 60, 340, 719, "\xED\x86\xA0\xED\x95\x84\xEB\x93\x9C\xEB\x8A\x94\x20\xEB\xAF\xB8"
                                           "\xEB\x9E\x98\xEC\x9D\x98\x20\xEB\x94\x94\xEC\xA7\x80\xED\x84\xB8"
                                           "\x20\xEB\xB0\xA9\xEC\x86\xA1\xEB\xB6\x84\xEC\x95\xBC\xEB\xA5\xBC"
                                           "\x20\xEC\x9D\xB4\xEB\x81\x8C\xEC\x96\xB4\xEA\xB0\x88\x20\x50\x56"
                                           "\x52\xEB\xB6\x84\xEC\x95\xBC\xEC\x9D\x98\x20\xEC\x84\xA0\xEB\x8F"
                                           "\x84\x20\xEA\xB8\xB0\xEC\x97\x85\xEC\x9E\x85\xEB\x8B\x88\xEB\x8B\xA4", COLOR_White , RGB(120,80,40), &FontLCD_18, FALSE, ALIGN_LEFT);

      FMUC_FreeFontFile(&FontLCD_18);
    }

    TAP_Osd_Sync();
  }

  if(event == EVT_KEY)
  {
    if(param1 == RKEY_Exit)
    {
      if(OSDRgn) TAP_Osd_Delete(OSDRgn);
      TAP_Osd_Sync();
      TAP_EnterNormal();
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
