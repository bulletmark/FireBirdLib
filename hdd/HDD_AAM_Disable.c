#include "FBLib_hdd.h"
#include "libFireBird.h"

int HDD_AAM_Disable(void)
{
  TRACEENTER;

  int ret;
  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SETFEATURES,      //COMMAND
                                                                  SETFEATURES_DIS_AAM,  //FEATURE
                                                                  0,                    //NSECTOR
                                                                  0,                    //SECTOR
                                                                  0,                    //LCYL
                                                                  0,                    //HCYL
                                                                  0,                    //SELECT
                                                                  0};                   //COMMAND

  ret = SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0);

  TRACEEXIT;

  return ret;
}
