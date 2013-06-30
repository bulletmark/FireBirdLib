#include "tap.h"
#include "libFireBird.h"
#include "Callee_TAPCOM.h"

#define PROGRAM_NAME    "Demo Caller"

TAP_ID                  (1);
TAP_PROGRAM_NAME        (PROGRAM_NAME);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("");
TAP_ETCINFO             (__DATE__);

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) event;
  (void) param2;

  return param1;
}

Callee_Parameters       params;
dword                   TAPID;

int TAP_Main(void)
{
  //Fill the paramsters
  params.StructVersion = Callee_Param_Version;
  TAP_SPrint(params.AnyText, "Launched by Caller");
  params.AnyData = 1234;

  TAP_Print("Caller: Launching Callee\n");

  //TAPID will be automatically filled an will contain callee's ID
  HDD_TAP_Start(CALLEE_TAPName, FALSE, &params, &TAPID);

  TAP_Print("Caller: Exiting\n");

  return 0;
}
