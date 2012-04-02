#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_Draw(void)
{
  int                   i=0;
  int                   j=0;
  int                   k=0;
  char                 *keytext, *p, pc;
  extern tFontData      Calibri_14_FontData;
  dword                 tw;
  char                  CharAtCursor;
  dword                 x;
  #define MAXX          415
  char                 *StringVarStart;
  dword                 State, SubState;
  extern TYPE_GrData    _TextCursor14_Gd;

  int                   w, h;
  float                 AntiAliasFactor;

  w = 444;
  h = 383;
  AntiAliasFactor = 1;

  if(OSDMenuKeyboard_rgn == 0)
  {
    TAP_GetState(&State, &SubState);
    OSDMenuKeyboard_ReturnToNormal = (State == STATE_Normal) && (SubState == SUBSTATE_Normal);
    TAP_ExitNormal();
    OSDMenuKeyboard_rgn = TAP_Osd_Create((720 - w) >> 1, (576 - h) >> 1, w, h, 0, 0);
  }
  TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 0, 0, w, h, COLOR_Grey01);

  // Titelbox erzeugen
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 0, 444, 36, COLOR_Grey08, COLOR_Grey08, COLOR_Grey03);
  FM_PutStringAA(OSDMenuKeyboard_rgn, 5, 10, 440, OSDMenuKeyboard_Title, COLOR_Orange01, 0, &Calibri_14_FontData, FALSE, ALIGN_CENTER, AntiAliasFactor);

  // Tastaturbox erzeugen
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 34, 444, 244, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);

  // Textbox erzeugen
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 276, 444, 30, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);

  for (i=0;i<NRKEYPADKEYS;i++)
  {
    if (i < 26)
    {
      if(i != KeyPadPosition)
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 50, 50, COLOR_Grey12, COLOR_Grey08, COLOR_Grey04);
        FM_PutStringAA(OSDMenuKeyboard_rgn, 22+k*50, 70+(j*50), 70+(k*50), Keypad[KeyPadMode][i], COLOR_Grey19, 0, &Calibri_14_FontData, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      else
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 50, 50, COLOR_Grey08, COLOR_Grey12, COLOR_Orange03);
        TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 24+k*50, 81+(j*50), 46, 23, COLOR_Orange02);
        FM_PutStringAA(OSDMenuKeyboard_rgn, 22+k*50, 70+(j*50), 70+(k*50), Keypad[KeyPadMode][i], COLOR_Grey00, 0, &Calibri_14_FontData, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }

      k++;
      if (k == 8)
      {
        k=0;
        j++;
      }
    }
    else
    {
      if (i == 26) keytext = "Space";
      else if (i == 27) keytext = "Backspace";
      else keytext = "OK";

      if (i != KeyPadPosition)
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 100, 50, COLOR_Grey12, COLOR_Grey08, COLOR_Grey04);
        FM_PutStringAA(OSDMenuKeyboard_rgn, 22+k*50, 70+(j*50), 120+(k*50), keytext, COLOR_Grey19, 0, &Calibri_14_FontData, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      else
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 100, 50, COLOR_Grey08, COLOR_Grey12, COLOR_Orange03);
        TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 24+k*50, 81+(j*50), 96, 23, COLOR_Orange02);
        FM_PutStringAA(OSDMenuKeyboard_rgn, 22+k*50, 70+(j*50), 120+(k*50), keytext, COLOR_Grey00, 0, &Calibri_14_FontData, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      k+=2;
    }
  }

  //Aktuellen Text malen
  x = 6;

  //OSDMenuKeyboard_TextStartPosition prüfen und anpassen
  if(OSDMenuKeyboard_CursorPosition < OSDMenuKeyboard_TextStartPosition) OSDMenuKeyboard_TextStartPosition = OSDMenuKeyboard_CursorPosition;
  p = &OSDMenuKeyboard_StringVar[OSDMenuKeyboard_CursorPosition];
  pc = *p;
  *p = '\0';
  while((FM_GetStringWidth(&OSDMenuKeyboard_StringVar[OSDMenuKeyboard_TextStartPosition], &Calibri_14_FontData) + _TextCursor14_Gd.width) > (MAXX - x - 10))
  {
    if(OSDMenuKeyboard_TextStartPosition >= (int)strlen(OSDMenuKeyboard_StringVar)) break;
    OSDMenuKeyboard_TextStartPosition++;
  }
  *p = pc;
  StringVarStart = &OSDMenuKeyboard_StringVar[OSDMenuKeyboard_TextStartPosition];

  TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 4, 280, 436, 22, COLOR_Grey05);

  //..., falls der Text bereits links hinausgeschoben ist
  if(OSDMenuKeyboard_TextStartPosition > 0)
  {
    FM_PutStringAA(OSDMenuKeyboard_rgn, x, 282, MAXX, "...", COLOR_Grey19, 0, &Calibri_14_FontData, TRUE, ALIGN_LEFT, AntiAliasFactor);
    x += FM_GetStringWidth("...", &Calibri_14_FontData);
  }

  if(OSDMenuKeyboard_CursorPosition == 0)
  {
    //Cursor malen
    TAP_Osd_PutGd(OSDMenuKeyboard_rgn, 6, 286, &_TextCursor14_Gd, TRUE);

    //Ganzen Text malen
    FM_PutStringAA(OSDMenuKeyboard_rgn, x + _TextCursor14_Gd.width, 282, MAXX, OSDMenuKeyboard_StringVar, COLOR_Grey19, 0, &Calibri_14_FontData, TRUE, ALIGN_LEFT, AntiAliasFactor);
  }
  else if(OSDMenuKeyboard_CursorPosition == (int)strlen(OSDMenuKeyboard_StringVar))
  {
    //Ganzen Text malen
    FM_PutStringAA(OSDMenuKeyboard_rgn, x, 282, MAXX, StringVarStart, COLOR_Grey19, 0, &Calibri_14_FontData, TRUE, ALIGN_LEFT, AntiAliasFactor);

    //Cursor malen
    tw = FM_GetStringWidth(StringVarStart, &Calibri_14_FontData);
    TAP_Osd_PutGd(OSDMenuKeyboard_rgn, x + tw, 286, &_TextCursor14_Gd, TRUE);
  }
  else
  {
    //Ersten Teil des Textes malen
    CharAtCursor = OSDMenuKeyboard_StringVar[OSDMenuKeyboard_CursorPosition];
    OSDMenuKeyboard_StringVar[OSDMenuKeyboard_CursorPosition] = '\0';
    FM_PutStringAA(OSDMenuKeyboard_rgn, x, 282, MAXX, StringVarStart, COLOR_Grey19, 0, &Calibri_14_FontData, TRUE, ALIGN_LEFT, AntiAliasFactor);

    //Cursor malen
    x += FM_GetStringWidth(StringVarStart, &Calibri_14_FontData);
    TAP_Osd_PutGd(OSDMenuKeyboard_rgn, x, 286, &_TextCursor14_Gd, TRUE);
    x += _TextCursor14_Gd.width;

    //Zweiten Teil des Textes malen
    OSDMenuKeyboard_StringVar[OSDMenuKeyboard_CursorPosition] = CharAtCursor;
    FM_PutStringAA(OSDMenuKeyboard_rgn, x, 282, MAXX, &OSDMenuKeyboard_StringVar[OSDMenuKeyboard_CursorPosition], COLOR_Grey19, 0, &Calibri_14_FontData, TRUE, ALIGN_LEFT, AntiAliasFactor);
  }

  //Legende
  OSDMenuKeyboard_ButtonsX[0] = 10;
  OSDMenuKeyboard_ButtonsX[1] = 10;
  OSDMenuKeyboard_ButtonsX[2] = 10;
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 306, 444, 77, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);
  for(i = 0; i < OSDMenuKeyboard_NrButtons; i++)
    OSDMenuKeyboard_DrawLegendButton(OSDMenuKeyboard_Buttons[i].Line, OSDMenuKeyboard_Buttons[i].ButtonIcon, OSDMenuKeyboard_Buttons[i].Text);

  TAP_Osd_Sync();
}
