#include                "tap.h"
#include                "../../libFireBird.h"

#define PROGRAM_NAME    "CrashCheck"

TAP_ID                  (0x8E0A42FD);
TAP_PROGRAM_NAME        (PROGRAM_NAME);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("");
TAP_ETCINFO             (__DATE__);


dword TAP_EventHandler(word event, dword param1, dword param2)
{
  static bool DoNotReenter = FALSE;

  (void) param2;

  //If visible, forward events to the message box
  if(OSDMenuMessageBoxIsVisible()) OSDMenuEvent(&event, &param1, &param2);

  //Prevent recursive entries
  if(DoNotReenter) return param1;
  DoNotReenter = TRUE;

  if(event == EVT_KEY)
  {
    switch(param1)
    {
      case RKEY_Exit:
      {
        //The standard exit path
        //Don't forget to add a CrashCheck_Shutdown() to every termination path of the TAP
        TAP_PrintNet("CrashCheck TAP has been stopped by the user\n");
        CrashCheck_Shutdown(PROGRAM_NAME);
        TAP_Exit();
        param1 = 0;
        break;
      }

      case RKEY_Record:
      {
        //For demo purposes, this will stop the TAP but won't reset the crash counter (like at a crash)
        TAP_PrintNet("CrashCheck TAP has crashed\n");
        TAP_Exit();
        param1 = 0;
        break;
      }
    }
  }

  //Check for stop events otherwise the crash counter will increase with every shutdown of the Toppy
  if(event == EVT_STOP)
  {
    TAP_PrintNet("CrashCheck TAP has been stopped via the file list or Toppy shutdown\n");
    CrashCheck_Shutdown(PROGRAM_NAME);
  }

  DoNotReenter = FALSE;
  return param1;
}

int TAP_Main(void)
{
  //This should be one of the first functions called
  //It will increase the crash counter in the file /ProgramFiles/Settings/CrashCheck.ini and...
  //...return TRUE if the counter is less than 3
  if(!CrashCheck_Startup(PROGRAM_NAME))
  {
    //Something made the Toppy crash more than two times. Inform the user that this TAP will terminate to prevent another crash.
    //Of course, it is not possible to determine which TAP has produced the crash and it is possible that the culprit doesn’t even use the crash check functions.
    //Leave it up to the user if he would like to try to run the TAP again but make sure that the message automatically times our or it may block the AutoStart if no one is in front of the TV
    OSDMenuMessageBoxInitialize(PROGRAM_NAME, "This TAP will be stopped due to an\nexcessive number of unexpected crashes.");
    OSDMenuMessageBoxButtonAdd("Exit");
    OSDMenuMessageBoxButtonAdd("Continue");
    OSDMenuMessageBoxButtonSelect(0);
    OSDMenuMessageBoxShow();

    dword Timeout = TAP_GetTick() + 500;
    while(OSDMenuMessageBoxIsVisible())
    {
      TAP_SystemProc();
      if(TAP_GetTick() > Timeout) OSDMenuMessageBoxDestroy();
    }

    //User has choosen to exit or the timeout has occured
    if((int)OSDMenuMessageBoxLastButton() < 1) return 0;
  }

  //Do all tasks during a normal startup
  //...

  return 1;
}
