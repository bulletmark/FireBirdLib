#include "FBLib_hdd.h"
#include "../libFireBird.h"

int HDD_APM_Enable(byte APMLevel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_APM_Enable");
  #endif

  int ret;
  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SETFEATURES,      //COMMAND
                                                                  SETFEATURES_EN_APM,   //FEATURE
                                                                  APMLevel,             //NSECTOR
                                                                  0,                    //SECTOR
                                                                  0,                    //LCYL
                                                                  0,                    //HCYL
                                                                  0,                    //SELECT
                                                                  0};                   //COMMAND

  ret = SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
