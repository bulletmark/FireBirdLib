#include "tap.h"
#include "libFireBird.h"

#define PROGRAM_NAME "TMSOSDMemo Demo"
#define VERSION      "0.1"

TAP_ID           (0x8E0Affff);
TAP_PROGRAM_NAME (PROGRAM_NAME " " VERSION);
TAP_AUTHOR_NAME  ("ibbi");
TAP_DESCRIPTION  (PROGRAM_NAME);
TAP_ETCINFO      (__DATE__);

typedef enum
{
  ST_Init,
  ST_Idle,
  ST_YesNoDialog,
  ST_WaitInfoBox,
  ST_Exit
} tState;

tState State = ST_Init;

dword TAP_EventHandler (word event, dword param1, dword param2)
{
  (void) param2;

  char text[] = "Lorem ipsum dolor sit amet, consectetur adipisici elit, sed "
                "eiusmod tempor incidunt ut labore et dolore magna aliqua. Ut "
                "enim ad minim veniam, quis nostrud exercitation ullamco "
                "laboris nisi ut aliquid ex ea commodi consequat.\n"
                "\n"
                "Quis aute iure reprehenderit in voluptate velit esse cillum "
                "dolore eu fugiat nulla pariatur. Excepteur sint obcaecat "
                "cupiditat non proident, sunt in culpa qui officia deserunt "
                "mollit anim id est laborum.\n";

  OSDMenuEvent(&event, &param1, &param2);

  switch (State)
  {
    case ST_Init:
    {
      OSDMemoInitialize(FALSE, PROGRAM_NAME, "Main Page", text);
      OSDMenuButtonAdd(1, BI_Red,  NULL, "Tiny");
      OSDMenuButtonAdd(1, BI_Green,NULL, "Normal");
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
        else if (param1 == RKEY_Red)
        {
          OSDMenuSetLineHeight(LH_Tiny);
          OSDMenuUpdate(FALSE);
        }
        else if (param1 == RKEY_Green)
        {
          OSDMenuSetLineHeight(LH_Normal);
          OSDMenuUpdate(FALSE);
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
        else State = ST_Idle;
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
