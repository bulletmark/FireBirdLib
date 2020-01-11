#include                <sys/types.h>
#include                <sys/shm.h>
#include                <string.h>
#include                "FBLib_tap.h"

TYPE_Parametered_Tap   *fbl_parametered_tap = NULL;

dword HDD_TAP_Start(const char *TAPFileName, bool BatchMode, void* ParameterBlock, dword *TAPID)
{
  TRACEENTER();

  dword                 ret, Result;
  tDirEntry             _TempWorkFolder;
  dword                *_hddTapFolder;
  char                  CurrentDir[FBLIB_DIR_SIZE], FileName[MAX_FILE_NAME_SIZE + 1];
  int                   shmidBatch = 0, shmidParameterBlock = 0;
  char                 *segptrBatch = NULL;
  tTAPInfo              TAPInfo;

  //Set the TAPID and batch flag
  if(!HDD_TAP_GetInfo(TAPFileName, &TAPInfo))
  {
    TRACEEXIT();
    return 0;
  }

  if(TAPID != NULL) *TAPID = TAPInfo.TAPID;

  //Create a shared memory if batch mode has been selected
  //Just the existence is checked, no data transfered
  if(BatchMode)
  {
    shmidBatch = shmget(BATCHMODEKEY, 1, IPC_CREAT);
    segptrBatch = (char*)shmat(shmidBatch, 0, 0);
  }

  //Create a shared memory for the parameter block
  //Opposed the the TF5000 version, the existence of this shared memory block
  //is checked by StartedByTAP()
  fbl_parametered_tap = NULL;
  shmidParameterBlock = shmget(PARAMBLOCKKEY, sizeof(TYPE_Parametered_Tap), IPC_CREAT);
  if(shmidParameterBlock != -1)
  {
    fbl_parametered_tap = (TYPE_Parametered_Tap*)shmat(shmidParameterBlock, 0, 0);

    //Set the TAPID and parameter block
    fbl_parametered_tap->magic           = MAGIC;
    fbl_parametered_tap->id              = TAPInfo.TAPID;
    fbl_parametered_tap->pParameterBlock = (dword)ParameterBlock;
  }

  _hddTapFolder = (dword*)FIS_vHddTapFolder();

  Result = 0;
  ApplHdd_SaveWorkFolder();

  //"Calculate" the current absolute directory of the new TAP and remove the last /
  ConvertPathType(TAPFileName, CurrentDir, PF_LinuxPathOnly);
  if(CurrentDir[strlen(CurrentDir) - 1] == '/') CurrentDir[strlen(CurrentDir) - 1] = '\0';

  //Create a new folder structure
  memset(&_TempWorkFolder, 0, sizeof(_TempWorkFolder));
  _TempWorkFolder.Magic = 0xbacaed31;
  ret = ApplHdd_SelectFolder(&_TempWorkFolder, &CurrentDir[1]);

  if(!ret)
  {
    ApplHdd_SetWorkFolder(&_TempWorkFolder);
    memcpy((void*)_hddTapFolder[0], &_TempWorkFolder, sizeof(_TempWorkFolder));

    ConvertPathType(TAPFileName, FileName, PF_FileNameOnly);
    Appl_ExecProgram(FileName);
    Result = 1;
  }

  if(BatchMode && segptrBatch)
  {
    shmdt(segptrBatch);
    shmctl(shmidBatch, IPC_RMID, 0);
  }

  if((int)fbl_parametered_tap != -1)
  {
    shmdt(fbl_parametered_tap);
    shmctl(shmidParameterBlock, IPC_RMID, 0);
  }

  //Reset the batch flag and start parameters
  memset(&fbl_parametered_tap, 0, sizeof(fbl_parametered_tap));

  ApplHdd_RestoreWorkFolder();

  TRACEEXIT();
  return Result;
}
