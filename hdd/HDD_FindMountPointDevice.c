#include                <stdio.h>
#include                <stdlib.h>
#include                <mntent.h>
#include                <string.h>
#include                "../libFireBird.h"

bool HDD_FindMountPointDevice(char *File, char *MountPoint, char *MountDevice)
{
  TRACEENTER();

  struct mntent        *ent;
  FILE                 *aFile;
  char                  AbsFile[FBLIB_DIR_SIZE], Root[FBLIB_DIR_SIZE], Dev[FBLIB_DIR_SIZE];

  Root[0] = '\0';
  Dev[0] = '\0';
  AbsFile[0] = '\0';
  ConvertPathType(File, AbsFile, PF_LinuxPathOnly);
  if(*AbsFile)
  {
    aFile = setmntent("/proc/mounts", "r");
    if(aFile != NULL)
    {
      while(NULL != (ent = getmntent(aFile)))
      {
        if(strstr(AbsFile, ent->mnt_dir) == AbsFile)
        {
          if(strlen(ent->mnt_dir) > strlen(Root))
          {
            strcpy(Root, ent->mnt_dir);
            strcpy(Dev, ent->mnt_fsname);
          }
        }
      }
      endmntent(aFile);
    }
  }

  if(*Root && (Root[strlen(Root) - 1] != '/')) strcat(Root, "/");
  if(*Dev && (Dev[strlen(Dev) - 1] != '/')) strcat(Dev, "/");

  if(MountPoint) strcpy(MountPoint, Root);
  if(MountDevice) strcpy(MountDevice, Dev);

  TRACEEXIT();
  return (Root[0] != '\0' || Dev[0] != '\0');
}
