#include "FBLib_rec.h"
#include "../flash/FBLib_flash.h"

bool HDD_RECSlotSetDuration(byte Slot, word Duration)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_RECSlotSetDuration");
  #endif

  //Because only the TP struct differes, we may use one timer struct for all systems
  TYPE_Timer_TMSS     *RECSlot;

  //Sanity check of the parameters
  if(Slot > HDD_NumberOfRECSlots())
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  RECSlot = (TYPE_Timer_TMSS*)FIS_vRECSlotAddress(Slot);
  if(RECSlot == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check if the selected REC-slot is currently in use
  if(RECSlot->Duration == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  RECSlot->Duration = Duration;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
