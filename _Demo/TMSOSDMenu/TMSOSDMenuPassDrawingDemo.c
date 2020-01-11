#include <stdlib.h>
#include "tap.h"
#include "libFireBird.h"

#define PROGRAM_NAME "TMSOSDMenu PassDrawing Demo"
#define VERSION      "0.1"

TAP_ID           (0x8E0Affff);
TAP_PROGRAM_NAME (PROGRAM_NAME " " VERSION);
TAP_AUTHOR_NAME  ("ibbi");
TAP_DESCRIPTION  (PROGRAM_NAME);
TAP_ETCINFO      (__DATE__);

#define LINES 20

typedef enum
{
  ST_Init,
  ST_Idle,
  ST_YesNoDialog,
  ST_WaitInfoBox,
  ST_Exit
} tState;

tState State = ST_Init;

static byte RandomFont (void)
{
  byte fntSize = 0;

  switch (rand() % 7)
  {
    case 0:
      fntSize = 10;
      break;

    case 1:
      fntSize = 12;
      break;

    case 2:
      fntSize = 14;
      break;

    case 3:
      fntSize = 16;
      break;

    case 4:
      fntSize = 18;
      break;

    case 5:
      fntSize = 20;
      break;

    case 6:
      fntSize = 20+0xB;
      break;
  }

  return fntSize;
}

static void DrawLine (tOSDCB type, word rgn)
{
  static byte fntSize[LINES][4];

  if ((type & OSDCB_MASK) == OSDCB_ListItem)
  {
    int id, i;
    char nr[4], column[10];

    id = type >> 8;
    TAP_SPrint(nr, "#%.2d", id + 1);

    OSDMenuPutString(rgn, 0, 0, GetOSDRegionWidth(rgn) - 1, nr, COLOR_White, COLOR_None, 20+0xB, FALSE, ALIGN_LEFT);

    for (i = 0; i < 4; i++)
    {
      if (fntSize[id][i] == 0) fntSize[id][i] = RandomFont();

      TAP_SPrint(column, "Column %d", i + 1);
      OSDMenuPutString(rgn, 75 + i * 125, 0, GetOSDRegionWidth(rgn) - 1, column, COLOR_White, COLOR_None, fntSize[id][i], FALSE, ALIGN_LEFT);

      if (fntSize[id][i] == 10) OSDMenuPutString(rgn, 75 + i * 125, 17, GetOSDRegionWidth(rgn) - 1, "(2nd line)", COLOR_White, COLOR_None, fntSize[id][i], FALSE, ALIGN_LEFT);
      if (fntSize[id][i] == 12) OSDMenuPutString(rgn, 75 + i * 125, 16, GetOSDRegionWidth(rgn) - 1, "(2nd line)", COLOR_White, COLOR_None, fntSize[id][i], FALSE, ALIGN_LEFT);
    }
  }
}

dword TAP_EventHandler (word event, dword param1, dword param2)
{
  int i;

  OSDMenuEvent(&event, &param1, &param2);

  switch(State)
  {
    case ST_Init:
    {
      OSDMenuInitialize(FALSE, FALSE, FALSE, TRUE, PROGRAM_NAME, "Main Menu");
      OSDMenuSetCallback(&DrawLine);

      for (i = 0; i < LINES ; i++)
      {
        OSDMenuItemAdd(" ", NULL, FALSE, FALSE, TRUE, FALSE, i);
        OSDMenuItemPassDrawing(OSDMenuItemGetNrOfItems() - 1, FALSE, FALSE);
      }

      OSDMenuUpdate(FALSE);

      State = ST_Idle;

      break;
    }

    case ST_Idle:
    {
      if (event == EVT_KEY)
      {
        if (param1 == RKEY_Exit)
        {
          OSDMenuMessageBoxInitialize(PROGRAM_NAME, "You you really want to stop?\nAre you serious?");
          OSDMenuMessageBoxButtonAdd("Yes");
          OSDMenuMessageBoxButtonAdd("No");
          OSDMenuMessageBoxButtonAdd("Don't know");

          //0 = left most button, which is the default, so the next statement is not necessary
          OSDMenuMessageBoxButtonSelect(0);
          OSDMenuMessageBoxShow();
          State = ST_YesNoDialog;
        }
        param1 = 0;
      }

      break;
    }

    case ST_YesNoDialog:
    {
      if (!OSDMenuMessageBoxIsVisible())
      {
        if (OSDMenuMessageBoxLastButton() == 0)
        {
          OSDMenuDestroy();
          OSDMenuInfoBoxShow(PROGRAM_NAME, "Good bye!\nSee you soon.\n:-)", 300);
          State = ST_WaitInfoBox;
        }
        else
        {
          State = ST_Idle;
        }
      }
      break;
    }

    case ST_WaitInfoBox:
    {
      if (!OSDMenuInfoBoxIsVisible()) State = ST_Exit;
      break;
    }

    case ST_Exit:
    {
      TAP_Exit();
      break;
    }

  }

  return param1;
}

int TAP_Main (void)
{
  KeyTranslate(TRUE, &TAP_EventHandler);

  return 1;
}
