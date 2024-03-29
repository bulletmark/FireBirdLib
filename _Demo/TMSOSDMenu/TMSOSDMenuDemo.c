#include                <stdio.h>
#include                "tap.h"
#include                "libFireBird.h"

#include                "graphic/qplogo.gd"
#include                "graphic/status_viewed.gd"
#include                "graphic/status_bad.gd"

#define PROGRAM_NAME    "TMSOSDMenu Demo"
#define VERSION         "V0.3"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird & ibbi");
TAP_DESCRIPTION         ("TMSOSDMenu Demo");
TAP_ETCINFO             (__DATE__);


typedef enum
{
  ST_Init,
  ST_Idle,
  ST_SelectionDialog,
  ST_YesNoDialog,
  ST_WaitInfoBox,
  ST_Exit
} tState;

tState                  State = ST_Init;

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  static tCursorType cursor = CT_Standard;

  (void) param2;

  OSDMenuEvent(&event, &param1, &param2);

  switch(State)
  {
    case ST_Init:
    {
      OSDMenuInitialize(FALSE, TRUE, TRUE, TRUE, PROGRAM_NAME, "Main Menu");
      OSDMenuLogo(493, 486, &_qplogoGd);

      OSDMenuItemAdd("31. hr-fernsehen", "30 Min. WL", NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("2nd Name", "2nd Value", NULL, NULL, FALSE, FALSE, 0);
      OSDMenuItemAdd("3rd Name", "3rd Value", NULL, NULL, TRUE, FALSE, 0);
      OSDMenuItemAdd("4th Name", "4th Value", &_status_viewed_Gd, &_status_bad_Gd, TRUE, TRUE, 0);
      OSDMenuItemAdd("5th Name", "5th Value", NULL, NULL, TRUE, TRUE, 0);

      OSDMenuItemAdd("6th Name", "6th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("7th Name", "7th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("8th Name", "8th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("9th Name", "9th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("10th Name", "10th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("11th Name", "11th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("12th Name", "12th Value", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("Umlaute", "\x5ABC �������", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("This text is too long for this line", "", NULL, NULL, TRUE, TRUE, 0);

      OSDMenuButtonAdd(1, BI_Red,    NULL, "Tiny");
      OSDMenuButtonAdd(1, BI_Green,  NULL, "Normal");
      OSDMenuButtonAdd(1, BI_Yellow, NULL, "Small");

      OSDMenuButtonAdd(2, BI_Blue,  NULL, "Change Cursor");
      OSDMenuButtonAdd(2, BI_White,  NULL, "Show List Box");

      OSDMenuUpdate(FALSE);

      State = ST_Idle;

      break;
    }

    case ST_Idle:
    {
      if(event == EVT_KEY)
      {
        if(param1 == RKEY_Exit)
        {
          if (OSDMenuListBoxIsVisible()) OSDMenuListBoxDestroy();
          else
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
        else if (param1 == RKEY_Yellow)
        {
          OSDMenuSetLineHeight(LH_Small);
          OSDMenuUpdate(FALSE);
        }
        else if (param1 == RKEY_Blue)
        {
          if (++cursor == CT_NRITEMS) cursor = CT_Standard;
          OSDMenuSetCursor(cursor);
          OSDMenuUpdate(FALSE);
        }
        else if (param1 == RKEY_White)
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
        }
        else if ((param1 == RKEY_Ok) && OSDMenuListBoxIsVisible())
        {
          char message[80];

          snprintf(message, sizeof(message), "You've selected '%s'.", OSDMenuItemGetCurrentName());
          message[sizeof(message) - 1] = 0;

          OSDMenuMessageBoxInitialize(PROGRAM_NAME, message);
          OSDMenuMessageBoxButtonAdd("That's true");
          OSDMenuMessageBoxShow();

          State = ST_SelectionDialog;
        }
        param1 = 0;
      }

      break;
    }

    case ST_SelectionDialog:
    {
      if (!OSDMenuMessageBoxIsVisible()) State = ST_Idle;
      break;
    }

    case ST_YesNoDialog:
    {
      if(!OSDMenuMessageBoxIsVisible())
      {
        if(OSDMenuMessageBoxLastButton() == 0)
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
      if(!OSDMenuInfoBoxIsVisible()) State = ST_Exit;
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

int TAP_Main(void)
{
  KeyTranslate(TRUE, &TAP_EventHandler);
  return 1;
}
