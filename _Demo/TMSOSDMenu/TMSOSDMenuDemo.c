#include                "tap.h"
#include                "libFireBird.h"

#include                "graphic/qplogo.gd"
#include                "graphic/status_viewed.gd"
#include                "graphic/status_bad.gd"

#define PROGRAM_NAME    "TMSOSDMenu Demo"
#define VERSION         "V0.2b"

TAP_ID                  (0x8E0Affff);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("TMSOSDMenu Demo");
TAP_ETCINFO             (__DATE__);


typedef enum
{
  ST_Init,
  ST_Idle,
  ST_YesNoDialog,
  ST_WaitInfoBox,
  ST_Exit
} tState;

tState                  State = ST_Init;

dword TAP_EventHandler(word event, dword param1, dword param2)
{
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
      OSDMenuItemAdd("Umlaute", "ABC ƒ÷‹‰ˆ¸ﬂ", NULL, NULL, TRUE, TRUE, 0);
      OSDMenuItemAdd("This text is too long for this line", "", NULL, NULL, TRUE, TRUE, 0);

      OSDMenuButtonAdd(1, BI_Red,    NULL, "Button 1");
      OSDMenuButtonAdd(1, BI_Green,  NULL, "Button 2");
      OSDMenuButtonAdd(1, BI_Yellow, NULL, "Button 3");

      OSDMenuButtonAdd(2, BI_Blue,  NULL,  "Button 4");
      OSDMenuButtonAdd(2, BI_White, NULL,  "Button 5");

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
  return 1;
}
