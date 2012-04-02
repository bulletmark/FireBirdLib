#include                <unistd.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

void LogoManager_MoveExternalUpdates(void)
{
  char                  Files[3][20] = {"LogoPack.tar", "Logos.lil", "lil.add"};
  char                  Drive, Partition;
  int                   File;
  char                  DatFile[28], cmd[255];

  //Scan some external drives to find the logo updates
  for(File = 0; File < 3; File++)
  {
    for(Drive = 'b'; Drive < 'f'; Drive++)
    {
      for(Partition = '0'; Partition < '2'; Partition++)
      {
        if(Partition == '0')
          TAP_SPrint(DatFile, "/mnt/sd%c/%s", Drive, Files[File]);
        else
          TAP_SPrint(DatFile, "/mnt/sd%c%c/%s", Drive, Partition, Files[File]);

        if(!access(DatFile, F_OK))
        {
          TAP_SPrint(cmd, "mv %s /mnt/hd/ProgramFiles/Settings/Logos", DatFile);
          system(cmd);
        }
      }
    }
  }
}
