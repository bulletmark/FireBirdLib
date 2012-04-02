#include "FBLib_hdd.h"
#include "../libFireBird.h"

int HDD_Smart_ReadData (word *DataBuf)
{
  unsigned char         CommandBlock[FBHDIO_DRIVE_CMD_HDR_SIZE + 512] = {WIN_SMART, 0, SMART_READ_VALUES, 1,};

  if(SendHDDCommand(HDIO_DRIVE_CMD, CommandBlock, 512)) return 19;
  memcpy(DataBuf, &CommandBlock[4], 512);
  return 0;
}
