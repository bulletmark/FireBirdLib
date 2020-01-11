#include                <stdio.h>
#include                <stdlib.h>
#include                <mntent.h>
#include                <string.h>
#include                "libFireBird.h"

bool HDD_FindMountPoint(const char *File, char *MountPoint)
{
  TRACEENTER();

  bool ret;

  ret = HDD_FindMountPointDevice(File, MountPoint, NULL);

  TRACEEXIT();
  return ret;
}
