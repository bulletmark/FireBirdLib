#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

void OSDMenuKeyboard_Draw(void)
{
  TRACEENTER();

  int                   i=0;
  int                   j=0;
  int                   k=0;
  char                 *keytext;
  dword                 tw, cw;
  char                  CharAtCursor, *pCharAtCursor;
  char                  sCharAtCursor[5];
  byte                  cl;
  dword                 x, cx = 0;
  #define MAXX          437
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
  FMUC_PutStringAA(OSDMenuKeyboard_rgn, 5, 7, 438, OSDMenuKeyboard_Title, COLOR_Orange01, 0, &KeyboardFont_14, FALSE, ALIGN_CENTER, AntiAliasFactor);

  // Tastaturbox erzeugen
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 34, 444, 244, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);

  // Textbox erzeugen
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 276, 444, 30, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);

  for(i = 0; i < NRKEYPADKEYS; i++)
  {
    if(i < 26)
    {
      if(i != KeyPadPosition)
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 50, 50, COLOR_Grey12, COLOR_Grey08, COLOR_Grey04);
        FMUC_PutStringAA(OSDMenuKeyboard_rgn, 23+k*50, 70+(j*50), 70+(k*50), Keypad[KeyPadMode][i], COLOR_Grey19, 0, &KeyboardFont_14, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      else
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 50, 50, COLOR_Grey08, COLOR_Grey12, COLOR_Orange03);
        TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 24+k*50, 81+(j*50), 46, 23, COLOR_Orange02);
        FMUC_PutStringAA(OSDMenuKeyboard_rgn, 23+k*50, 70+(j*50), 70+(k*50), Keypad[KeyPadMode][i], COLOR_Grey00, 0, &KeyboardFont_14, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }

      k++;
      if(k == 8)
      {
        k=0;
        j++;
      }
    }
    else
    {
      if(i == 26) keytext = "Space";
      else if(i == 27) keytext = "Backspace";
      else keytext = "OK";

      if(i != KeyPadPosition)
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 100, 50, COLOR_Grey12, COLOR_Grey08, COLOR_Grey04);
        FMUC_PutStringAA(OSDMenuKeyboard_rgn, 23+k*50, 70+(j*50), 120+(k*50), keytext, COLOR_Grey19, 0, &KeyboardFont_14, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      else
      {
        TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 22+k*50, 56+(j*50), 100, 50, COLOR_Grey08, COLOR_Grey12, COLOR_Orange03);
        TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 24+k*50, 81+(j*50), 96, 23, COLOR_Orange02);
        FMUC_PutStringAA(OSDMenuKeyboard_rgn, 23+k*50, 70+(j*50), 120+(k*50), keytext, COLOR_Grey00, 0, &KeyboardFont_14, FALSE, ALIGN_CENTER, AntiAliasFactor);
      }
      k+=2;
    }
  }

  //Aktuellen Text malen
  x = 6;

  //OSDMenuKeyboard_TextStartPosition pr�fen und anpassen
  if(OSDMenuKeyboard_CursorPosition < OSDMenuKeyboard_TextStartPosition) OSDMenuKeyboard_TextStartPosition = OSDMenuKeyboard_CursorPosition;
  pCharAtCursor = GetUCPos(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition);
  CharAtCursor = *pCharAtCursor;
  *pCharAtCursor = '\0';

  while((FMUC_GetStringWidth(GetUCPos(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_TextStartPosition), &KeyboardFont_14) + _TextCursor14_Gd.width) > (MAXX - x - 10))
  {
    if(OSDMenuKeyboard_TextStartPosition >= (int)strlen(OSDMenuKeyboard_StringVar)) break;
    OSDMenuKeyboard_TextStartPosition++;
  }
  *pCharAtCursor = CharAtCursor;

  StringVarStart = GetUCPos(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_TextStartPosition);

  TAP_Osd_FillBox(OSDMenuKeyboard_rgn, 4, 280, 436, 22, COLOR_Grey05);

  //..., falls der Text bereits links hinausgeschoben ist
  if(OSDMenuKeyboard_TextStartPosition > 0)
  {
    FMUC_PutStringAA(OSDMenuKeyboard_rgn, x, 280, MAXX, "…", COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);
    x += FMUC_GetStringWidth("…", &KeyboardFont_14);
  }

  if(OSDMenuKeyboard_CursorPosition == 0)
  {
    if (KeyboardCursorType == KC_Text)
    {
      //Cursor malen
      TAP_Osd_PutGd(OSDMenuKeyboard_rgn, 6, 284, &_TextCursor14_Gd, TRUE);

      //Ganzen Text malen
      FMUC_PutStringAA(OSDMenuKeyboard_rgn, x + _TextCursor14_Gd.width, 280, MAXX, OSDMenuKeyboard_StringVar, COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);
    }
    else
    {
      FMUC_PutStringAA(OSDMenuKeyboard_rgn, x, 280, MAXX, OSDMenuKeyboard_StringVar, COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);
      cx = x;
      isUTF8Char(OSDMenuKeyboard_StringVar, &cl);
      strncpy(sCharAtCursor, OSDMenuKeyboard_StringVar, cl);
      sCharAtCursor[cl] = 0;
    }
  }
  else if(OSDMenuKeyboard_CursorPosition == (int)strlen(OSDMenuKeyboard_StringVar))
  {
    //Ganzen Text malen
    FMUC_PutStringAA(OSDMenuKeyboard_rgn, x, 280, MAXX, StringVarStart, COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);

    tw = FMUC_GetStringWidth(StringVarStart, &KeyboardFont_14);

    if (KeyboardCursorType == KC_Text)
    {
      //Cursor malen
      TAP_Osd_PutGd(OSDMenuKeyboard_rgn, x + tw, 284, &_TextCursor14_Gd, TRUE);
    }
    else
    {
      cx = x + tw;
      sCharAtCursor[0] = 0;
    }
  }
  else
  {
    //Ersten Teil des Textes malen
    pCharAtCursor = GetUCPos(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition);
    CharAtCursor = *pCharAtCursor;
    *pCharAtCursor = '\0';
    FMUC_PutStringAA(OSDMenuKeyboard_rgn, x, 280, MAXX, StringVarStart, COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);

    x += FMUC_GetStringWidth(StringVarStart, &KeyboardFont_14);

    if (KeyboardCursorType == KC_Text)
    {
      //Cursor malen
      TAP_Osd_PutGd(OSDMenuKeyboard_rgn, x, 284, &_TextCursor14_Gd, TRUE);
      x += _TextCursor14_Gd.width;
    }

    //Zweiten Teil des Textes malen
    *pCharAtCursor = CharAtCursor;
    FMUC_PutStringAA(OSDMenuKeyboard_rgn, x, 280, MAXX, pCharAtCursor, COLOR_Grey19, 0, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);

    cx = x;
    isUTF8Char(pCharAtCursor, &cl);
    strncpy(sCharAtCursor, pCharAtCursor, cl);
    sCharAtCursor[cl] = 0;

  }

  if (KeyboardCursorType == KC_Box)
  {
    if (!*sCharAtCursor) strcpy(sCharAtCursor, " ");

    cw = FMUC_GetStringWidth(sCharAtCursor, &KeyboardFont_14);
    FMUC_PutStringAA(OSDMenuKeyboard_rgn, cx, 280, cx + cw - 1, sCharAtCursor, COLOR_Grey19, COLOR_Orange02, &KeyboardFont_14, TRUE, ALIGN_LEFT, AntiAliasFactor);
  }

  //Legende
  OSDMenuKeyboard_ButtonsX[0] = 10;
  OSDMenuKeyboard_ButtonsX[1] = 10;
  OSDMenuKeyboard_ButtonsX[2] = 10;
  TAP_Osd_Draw3dBoxFill(OSDMenuKeyboard_rgn, 0, 306, 444, 77, COLOR_Grey08, COLOR_Grey08, COLOR_Grey04);
  for(i = 0; i < OSDMenuKeyboard_NrButtons; i++)
    OSDMenuKeyboard_DrawLegendButton(OSDMenuKeyboard_Buttons[i].Line, OSDMenuKeyboard_Buttons[i].ButtonIcon, OSDMenuKeyboard_Buttons[i].Text);

  TAP_Osd_Sync();

  TRACEEXIT();
}
