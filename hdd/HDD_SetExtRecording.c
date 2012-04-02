#include                <string.h>
#include                "../libFireBird.h"

//This function returns 0x0000 on success
//                      0xe00* for warnings
//                  and 0xf00* for errors
word HDD_SetExtRecording(bool ExtDisk)
{
  dword                *__nExtPartition;
  textPartitionInfo    *__extPartitionInfo;
  dword                *__extTsFolder;
  byte                 *__isAllPartitionInvalid;
  int                  *__selectedPartition;
  tDirEntry            *DirEntry;
  char                 *ExtDiskPart;

  void (*Appl_SetIsExternal)(bool) = NULL;


  //Resolve all firmware functions and variables
  __nExtPartition = (dword*)FIS_vnExtPartition();
  if(!__nExtPartition) return 0xf000;

  Appl_SetIsExternal = (void*)FIS_fwAppl_SetIsExternal();
  if(!Appl_SetIsExternal) return 0xf001;

  __extPartitionInfo = (textPartitionInfo*)FIS_vExtPartitionInfo();
  if(!__extPartitionInfo) return 0xf002;

  __extTsFolder = (dword*)FIS_vExtTsFolder();
  if(!__extTsFolder) return 0xf003;

  __isAllPartitionInvalid = (byte*)FIS_vIsAllPartitionInvalid();
  if(!__isAllPartitionInvalid) return 0xf004;

  __selectedPartition = (int*)FIS_vSelectedPartition();
  if(!__selectedPartition) return 0xf005;

  if(ExtDisk)
  {
    //Check if an external disk has been mounted
    if(*__nExtPartition == 0) return 0xe000;

    //Check if there is at least one partition which can be used for recording
    if(*__isAllPartitionInvalid != 0) return 0xe001;

    //Another check to make sure that there is a selectable partition
    if(__selectedPartition[1] < 0) return 0xe002;

    //Get the first partition of that drive
    ExtDiskPart = __extPartitionInfo[__selectedPartition[1]].MountPath;

    //Build the DirEntry struct
    DirEntry = TAP_MemAlloc(sizeof(tDirEntry));
    if(!DirEntry) return 0xf006;

    DirEntry->Magic = 0xbacaed31;
    DirEntry->Path = TAP_MemAlloc(strlen(ExtDiskPart) + 1);
    if(!DirEntry->Path) return 0xf007;

    memset(DirEntry->Path, 0, strlen(ExtDiskPart) + 1);
    strcpy(DirEntry->Path, ExtDiskPart);
    DirEntry->unknown1 =  9;
    DirEntry->unknown2 = 16;

    //Let the extTsFolder point to our DirEnt structure
    *__extTsFolder = (dword)DirEntry;

    //Set the external disk usage flag
    Appl_SetIsExternal(TRUE);
  }
  else
  {
    Appl_SetIsExternal(FALSE);
  }

  return 0x0000;
}
