#include <stdio.h>
#include "tap.h"
#include "libFireBird.h"

#define PROGRAM_NAME "TMSOSDMenu ListBox Demo"
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
  ST_WaitDialog,
  ST_Exit
} tState;

tState State = ST_Init;

dword TAP_EventHandler (word event, dword param1, dword param2)
{
  (void) param2;

  OSDMenuEvent(&event, &param1, &param2);

  switch (State)
  {
    case ST_Init:
    {
      OSDMenuListBoxInitialize(FALSE, FALSE, FALSE, TRUE, "List Box", 150, 250, FALSE);
      OSDMenuItemAdd("1st Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("2nd Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("3rd Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("4th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("5th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("6th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("7th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("8th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("9th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("10th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("11th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("12th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("13th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("14th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("15th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("16th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("17th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("18th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("19th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("20th Name", NULL, NULL, NULL, TRUE, FALSE, 0);
      OSDMenuButtonAdd(1, BI_Ok, NULL, "Select");
      OSDMenuButtonAdd(2, BI_Exit, NULL, "Exit");
      OSDMenuSetLineHeight(LH_Small);
      OSDMenuUpdate(FALSE);

      State = ST_Idle;

      break;
    }

    case ST_Idle:
    {
      if (event == EVT_KEY)
      {
        if (OSDMenuListBoxIsVisible())
        {
          if (param1 == RKEY_Exit)
          {
            OSDMenuListBoxDestroy();
            State = ST_Exit;
          }
          else if (param1 == RKEY_Ok)
          {
            char message[80];

            snprintf(message, sizeof(message), "You've selected '%s'.", OSDMenuItemGetCurrentName());
            message[sizeof(message) - 1] = 0;

            OSDMenuMessageBoxInitialize(PROGRAM_NAME, message);
            OSDMenuMessageBoxButtonAdd("That's true");
            OSDMenuMessageBoxShow();

            State = ST_WaitDialog;
          }
        }

        param1 = 0;
      }

      break;
    }

    case ST_WaitDialog:
    {
      if (!OSDMenuMessageBoxIsVisible()) State = ST_Idle;

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
