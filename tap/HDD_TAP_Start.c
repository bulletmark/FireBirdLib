#include                <sys/types.h>
#include                <sys/shm.h>
#include                <string.h>
#include                "FBLib_tap.h"

TYPE_Parametered_Tap   *fbl_parametered_tap = NULL;

dword HDD_TAP_Start(char *TAPFileName, bool BatchMode, void* ParameterBlock, dword *TAPID)
{
  dword                 ret;
  dword                 _TempWorkFolder[4];
  static dword          *_hddTapFolder = NULL;
  static dword          *_hddTsFolder = NULL;
  char                  CurrentDir[FBLIB_DIR_SIZE];
  int                   shmidBatch = 0, shmidParameterBlock = 0;
  char                 *segptrBatch = NULL;
  tTAPInfo              TAPInfo;

  static void  (*ApplHdd_SetWorkFolder)(void*) = NULL;
  static dword (*ApplHdd_SelectFolder)(void*, char  const*) = NULL;
  static void  (*Appl_ExecProgram)(char*) = NULL;

  //Set the TAPID and batch flag
  if(!HDD_TAP_GetInfo(TAPFileName, &TAPInfo)) return 0;
  if (TAPID != NULL) *TAPID = TAPInfo.TAPID;

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

  if(!Appl_ExecProgram)      Appl_ExecProgram      = (void*)FIS_fwAppl_ExecProgram();
  if(!ApplHdd_SetWorkFolder) ApplHdd_SetWorkFolder = (void*)FIS_fwApplHdd_SetWorkFolder();
  if(!ApplHdd_SelectFolder)  ApplHdd_SelectFolder  = (void*)FIS_fwApplHdd_SelectFolder();
  if(!_hddTapFolder)        _hddTapFolder          = (dword*)FIS_vHddTapFolder();
  if(!_hddTsFolder)         _hddTsFolder           = (dword*)FIS_vHddTsFolder();

  //"Calculate" the current absolute directory of the new TAP
  TAP_SPrint(CurrentDir, "mnt/hd");
  HDD_TAP_GetCurrentDir(&CurrentDir[strlen(CurrentDir)]);

  //Create a new folder structure
  memset(_TempWorkFolder, 0, sizeof(_TempWorkFolder));
  _TempWorkFolder[0] = 0xbacaed31;
  ret = ApplHdd_SelectFolder(&_TempWorkFolder, CurrentDir);
  if(!ret)
  {
    ApplHdd_SetWorkFolder(_TempWorkFolder);
    memcpy((void*)_hddTapFolder[0], &_TempWorkFolder[0], sizeof(_TempWorkFolder));
    Appl_ExecProgram(TAPFileName);
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

  ApplHdd_SelectFolder(&_hddTapFolder, "mnt/hd/ProgramFiles");
  ApplHdd_SetWorkFolder((void*)*_hddTsFolder);

  return 1;
}
