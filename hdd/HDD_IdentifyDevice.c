#include                <linux/hdreg.h>
#include                <fcntl.h>
#include                <sys/ioctl.h>
#include                <linux/fs.h>
#include                <unistd.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

bool HDD_IdentifyDevice(char *IdentifyDeviceBuffer)
{
  TRACEENTER();

  unsigned char         parms[FBHDIO_DRIVE_CMD_HDR_SIZE + sizeof(struct hd_driveid)] = {WIN_IDENTIFY, 0, 0, 1,};

  if(SendHDDCommand(HDIO_DRIVE_CMD, parms, sizeof(struct hd_driveid)))
  {
    TRACEEXIT();
    return FALSE;
  }
  if(IdentifyDeviceBuffer) memcpy(IdentifyDeviceBuffer, &parms[4], sizeof(struct hd_driveid));

  TRACEEXIT();
  return TRUE;
}
