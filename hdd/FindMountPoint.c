#include                <stdio.h>
#include                <stdlib.h>
#include                <mntent.h>
#include                <string.h>
#include                "../libFireBird.h"

bool HDD_FindMountPoint(char *File, char *MountPoint)
{
  TRACEENTER();

  struct mntent        *ent;
  FILE                 *aFile;
  char                  AbsFile[FBLIB_DIR_SIZE], Root[FBLIB_DIR_SIZE];

  Root[0] = '\0';
  ConvertPathType(File, AbsFile, PF_LinuxPathOnly);
  if(*AbsFile)
  {
    aFile = setmntent("/proc/mounts", "r");
    if(aFile != NULL)
    {
      while(NULL != (ent = getmntent(aFile)))
      {
        if((strstr(AbsFile, ent->mnt_dir) == AbsFile) && (strlen(ent->mnt_dir) > strlen(Root)))
          strcpy(Root, ent->mnt_dir);
      }
      endmntent(aFile);
    }
  }

  if(*Root && (Root[strlen(Root) - 1] != '/')) strcat(Root, "/");

  if(MountPoint) strcpy(MountPoint, Root);

  TRACEEXIT();
  return (Root[0] != '\0');
}
