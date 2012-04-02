#include "../libFireBird.h"

bool HDD_TAP_GetFileNameByIndex(int Index, char **TAPFileName)
{
  tTMSTAPTaskTable      *TMSTAPTaskTable;
  dword                 *FileHandle;

  if((Index < 0) || (Index >= TAP_MAX) || !TAPFileName)
  {
    if(TAPFileName) *TAPFileName = NULL;
    return FALSE;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  //Check if that TAP is running
  if(TMSTAPTaskTable[Index].Status != 1) return FALSE;

  //Check if the file pointer is valid
  if(!TMSTAPTaskTable[Index].file) return FALSE;

  //Check if the file handle is valid
  FileHandle = (dword*)TMSTAPTaskTable[Index].file->handle;
  if(!FileHandle) return FALSE;
  if(FileHandle[0] != 0xcdacedaf) return FALSE;

  *TAPFileName = (char*)FileHandle[2];

  return TRUE;
}
