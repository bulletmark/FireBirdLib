#include "FBLib_hdd.h"
#include "../libFireBird.h"

int HDD_Smart_DisableAttributeAutoSave(void)
{
  TRACEENTER();

  int ret;
  unsigned char         CommandBlock[FBHDIO_DRIVE_TASK_HDR_SIZE] = {WIN_SMART,        //COMMAND
                                                                  SMART_AUTOSAVE,   //FEATURE
                                                                  0x00,             //NSECTOR
                                                                  0,                //SECTOR
                                                                  0x4f,             //LCYL
                                                                  0xc2,             //HCYL
                                                                  0,                //SELECT
                                                                  0};               //COMMAND

  ret = SendHDDCommand(HDIO_DRIVE_TASK, CommandBlock, 0);

  TRACEEXIT();
  return ret;
}
