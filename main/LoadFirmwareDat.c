#include                <stdlib.h>
#include                <stdio.h>
#include                <fcntl.h>
#include                <sys/stat.h>
#include                "FBLib_main.h"

bool LoadFirmwareDat(tFWDATHeader **FWDatHeader, tToppyInfo **ToppyInfo, tFWInfo **FWInfo)
{
  TRACEENTER;

  static byte          *FWDATBin = NULL;
  char                  AbsPath[FBLIB_DIR_SIZE];
  FILE                 *fp;
  dword                 blk;
  tFWDATHeader         *FWDAT;
  struct stat           statbuf;

  if(!FWDATBin)
  {
    TAP_SPrint(AbsPath, "%s/ProgramFiles/Settings/%s", TAPFSROOT, FIRMWAREDAT);
    if(lstat(AbsPath, &statbuf))
    {
      TAP_SPrint(AbsPath, "%s/ProgramFiles/%s", TAPFSROOT, FIRMWAREDAT);
      if(lstat(AbsPath, &statbuf))
      {
        TRACEEXIT;
        return FALSE;
      }
    }

    if((fp = fopen(AbsPath, "r")) == NULL)
    {
      TRACEEXIT;
      return FALSE;
    }

    if((FWDATBin = TAP_MemAlloc(statbuf.st_size)) == NULL)
    {
      fclose(fp);

      TRACEEXIT;
      return FALSE;
    }

    blk = fread(FWDATBin, statbuf.st_size, 1, fp);
    fclose(fp);
  }
  else blk = 1;   // already loaded

  FWDAT = (tFWDATHeader *) FWDATBin;

  //Check Magic and other things
  if(blk == 0 ||
     FWDAT->Magic != 0x12345678 ||
     FWDAT->ToppyInfoLayoutVersion != 0 ||
     FWDAT->FWInfoLayoutVersion != 0)
  {
    TAP_MemFree(FWDATBin);
    FWDATBin = NULL;

    TRACEEXIT;
    return FALSE;
  }

  if(FWDatHeader) *FWDatHeader = FWDAT;
  if(ToppyInfo)   *ToppyInfo   = (tToppyInfo *) (FWDAT + 1);
  if(FWInfo)      *FWInfo      = (tFWInfo *) ((tToppyInfo *) (FWDAT + 1) + FWDAT->NrOfToppyInfoEntries);

  TRACEEXIT;
  return TRUE;
}
