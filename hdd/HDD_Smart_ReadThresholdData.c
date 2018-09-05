#include "FBLib_hdd.h"
#include "libFireBird.h"

int HDD_Smart_ReadThresholdData(word *DataBuf)
{
  TRACEENTER;

  unsigned char         CommandBlock[FBHDIO_DRIVE_CMD_HDR_SIZE + 512] = {WIN_SMART, 0, SMART_READ_THRESHOLDS, 1,};

  if(SendHDDCommand(HDIO_DRIVE_CMD, CommandBlock, 512))
  {
    TRACEEXIT;
    return 19;
  }
  memcpy(DataBuf, &CommandBlock[4], 512);

  TRACEEXIT;
  return 0;
}
