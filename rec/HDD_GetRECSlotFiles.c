#include "libFireBird.h"
#include "FBLib_rec.h"

bool HDD_GetRecSlotFiles(byte Slot, TYPE_File **RecFile, TYPE_File **InfFile, TYPE_File **NavFile)
{
  TRACEENTER();

  tHddRecordFile       *HddRecordFile;

  //Sanity check of the parameters
  HddRecordFile = (tHddRecordFile*)FIS_vhddRecordFile();

  if(Slot > HDD_NumberOfRECSlots() || !HddRecordFile)
  {
    if(RecFile) *RecFile = NULL;
    if(InfFile) *InfFile = NULL;
    if(NavFile) *NavFile = NULL;

    TRACEEXIT();
    return FALSE;
  }

  if(RecFile) *RecFile = HddRecordFile[Slot].RecFile;
  if(InfFile) *InfFile = HddRecordFile[Slot].InfFile;
  if(NavFile) *NavFile = HddRecordFile[Slot].NavFile;

  TRACEEXIT();
  return TRUE;
}
