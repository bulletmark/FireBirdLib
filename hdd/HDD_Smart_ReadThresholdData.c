#include "FBLib_hdd.h"
#include "../libFireBird.h"

int HDD_Smart_ReadThresholdData(word *DataBuf)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_Smart_ReadThresholdData");
  #endif

  unsigned char         CommandBlock[FBHDIO_DRIVE_CMD_HDR_SIZE + 512] = {WIN_SMART, 0, SMART_READ_THRESHOLDS, 1,};

  if(SendHDDCommand(HDIO_DRIVE_CMD, CommandBlock, 512))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 19;
  }
  memcpy(DataBuf, &CommandBlock[4], 512);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
