#include "FBLib_hdd.h"
#include "libFireBird.h"

int HDD_Smart_ReturnStatus(void)
{
  TRACEENTER;

  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SMART,        //COMMAND
                                                                  SMART_STATUS,     //FEATURE
                                                                  0x00,             //NSECTOR
                                                                  0,                //SECTOR
                                                                  0x4f,             //LCYL
                                                                  0xc2,             //HCYL
                                                                  0,                //SELECT
                                                                  0};               //COMMAND

  if(SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0))
  {
    TRACEEXIT;
    return 19;
  }

  if((CommandBlock[4] == 0x4f) && (CommandBlock[5] == 0xc2))
  {
    TRACEEXIT;
    return 0;
  }

  if((CommandBlock[4] == 0xf4) && (CommandBlock[5] == 0x2c))
  {
    TRACEEXIT;
    return 20;
  }

  TRACEEXIT;
  return 19;
}
