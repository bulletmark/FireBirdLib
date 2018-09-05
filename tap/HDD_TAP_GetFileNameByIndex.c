#include "libFireBird.h"

bool HDD_TAP_GetFileNameByIndex(int Index, char **TAPFileName)
{
  TRACEENTER;

  tTMSTAPTaskTable      *TMSTAPTaskTable;
  dword                 *FileHandle;

  if((Index < 0) || (Index >= TAP_MAX) || !TAPFileName)
  {
    if(TAPFileName) *TAPFileName = NULL;

    TRACEEXIT;
    return FALSE;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  //Check if that TAP is running
  if(TMSTAPTaskTable[Index].Status != 1)
  {
    TRACEEXIT;
    return FALSE;
  }

  //Check if the file pointer is valid
  if(!TMSTAPTaskTable[Index].file)
  {
    TRACEEXIT;
    return FALSE;
  }

  //Check if the file handle is valid
  FileHandle = (dword*)TMSTAPTaskTable[Index].file->handle;
  if(!FileHandle)
  {
    TRACEEXIT;
    return FALSE;
  }

  if(FileHandle[0] != 0xcdacedaf)
  {
    TRACEEXIT;
    return FALSE;
  }

  *TAPFileName = (char*)FileHandle[2];

  TRACEEXIT;
  return TRUE;
}
