#include "tap.h"
#include "libFireBird.h"
#include "Callee_TAPCOM.h"

#define PROGRAM_NAME    "Demo Callee"

TAP_ID                  (2);
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


Callee_Parameters       *params = NULL;

int TAP_Main(void)
{
  //Check if this TAP has been launched by an TAP
  if(HDD_TAP_StartedByTAP())
  {
    //Get a pointer to the parameter block.
    //If the caller didn't provide any parameters, the pointer == NULL
    //Parameters are valid only during TAP_Main. Copy away whatever you need at a later time.
    params = HDD_TAP_GetStartParameter();
    if(isValidRAMPtr(params))
    {
      //Make sure that the caller doesn't use an old delcaration
      if(params->StructVersion != Callee_Param_Version)
        TAP_Print("Callee: Invalid parameter version %d. Should be %d\n", params->StructVersion, Callee_Param_Version);
      else
        TAP_Print("Callee: AnyText=%s, AnyData=%d\n", params->AnyText, params->AnyData);
    }
    else
      TAP_Print("Callee: No parameters received\n");
  }
  else
    TAP_Print("Callee: Directly lauched, no parameters received\n");


  TAP_Print("Callee: Exiting\n");

  return 0;
}
