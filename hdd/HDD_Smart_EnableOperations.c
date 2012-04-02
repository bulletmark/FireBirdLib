#include "FBLib_hdd.h"
#include "../libFireBird.h"

int HDD_Smart_EnableOperations (void)
{
  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SMART,        //COMMAND
                                                                  SMART_ENABLE,     //FEATURE
                                                                  0,                //NSECTOR
                                                                  0,                //SECTOR
                                                                  0x4f,             //LCYL
                                                                  0xc2,             //HCYL
                                                                  0,                //SELECT
                                                                  0};               //COMMAND

  return SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0);
}
