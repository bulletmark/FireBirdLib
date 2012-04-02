#include "FBLib_rec.h"
#include "../flash/FBLib_flash.h"

bool HDD_RECSlotSetDuration(byte Slot, word Duration)
{
  //Because only the TP struct differes, we may use one timer struct for all systems
  TYPE_Timer_TMSS     *RECSlot;

  //Sanity check of the parameters
  if (Slot > HDD_NumberOfRECSlots()) return FALSE;

  RECSlot = (TYPE_Timer_TMSS*)FIS_vRECSlotAddress(Slot);
  if(RECSlot == NULL) return FALSE;

  //Check if the selected REC-slot is currently in use
  if(RECSlot->Duration == 0) return FALSE;

  RECSlot->Duration = Duration;

  return TRUE;
}
