#include                <sys/stat.h>
#include                <string.h>
#include                "FBLib_hdd.h"

tPathFormat GetPathType(char *Source)
{
  TRACEENTER;

  byte                  Result;
  tPathFormat           ret;
  char                  AbsFileName[FBLIB_DIR_SIZE];
  tstat64               statbuf;

  if((Source == NULL) || (*Source == '\0'))
  {
    TRACEEXIT;
    return 0;
  }

  // PF_FileNameOnly    xyz.tap
  // PF_TAPPathOnly     /ProgramFiles/Settings/
  // PF_LinuxPathOnly   /mnt/hd/ProgramFiles/Settings/
  // PF_FullTAPPath     /ProgramFiles/Settings/xyz.tap
  // PF_FullLinuxPath   /mnt/hd/ProgramFiles/Settings/xyz.tap

  //Catch . and / entries
  if((Source[0] == '.') || (strcmp(Source, "/") == 0))
  {
    TRACEEXIT;
    return PF_TAPPathOnly;
  }

  //If lstat() returns a result, we already have a Linux path
  if(!lstat64(Source, &statbuf))
  {
    if(S_ISDIR(statbuf.st_mode))
      Result = PF_LinuxPathOnly;
    else
      Result = PF_FullLinuxPath;

    TRACEEXIT;
    return Result;
  }

  Result = 0;

  if(strchr(Source, '/') != NULL)       Result |= 1;
  if(Source[strlen(Source) - 1] == '/') Result |= 2;
  if(strncmp(Source, "/mnt", 4) == 0)   Result |= 4;

  //Special case: a simple name without a / might point to a subdirectory. Find out
  strcpy(AbsFileName, "/mnt/hd");
  if(Source[0] == '/')
  {
    //Add to the mount point
    strcat(AbsFileName, Source);
  }
  else
  {
    //As the path is relative, we need to get the current path to make it absolute
    HDD_TAP_GetCurrentDir(&AbsFileName[7]);
    if(!StringEndsWith(AbsFileName, "/")) strcat(AbsFileName, "/");
    strcat(AbsFileName, Source);
  }

  if(!lstat64(AbsFileName, &statbuf) && S_ISDIR(statbuf.st_mode)) Result |= 3;

  //Now interpret the collected information
  ret = PF_FileNameOnly;
  switch(Result)
  {
    case 0: //In theory, results 2, 4 and 6 may never appear.
    case 2:
    case 4:
    case 6: ret = PF_FileNameOnly; break;

    case 1: ret = PF_FullTAPPath; break;
    case 3: ret = PF_TAPPathOnly; break;
    case 5: ret = PF_FullLinuxPath; break;
    case 7: ret = PF_LinuxPathOnly; break;
  }

  TRACEEXIT;
  return ret;
}
