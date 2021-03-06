#include "FBLib_hdd.h"
#include "libFireBird.h"

int HDD_AAM_Enable(byte AAMLevel)
{
  TRACEENTER();

  int ret;
  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SETFEATURES,      //COMMAND
                                                                  SETFEATURES_EN_AAM,   //FEATURE
                                                                  AAMLevel,             //NSECTOR
                                                                  0,                    //SECTOR
                                                                  0,                    //LCYL
                                                                  0,                    //HCYL
                                                                  0,                    //SELECT
                                                                  0};                   //COMMAND

  ret = SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0);

  TRACEEXIT();
  return ret;
}
