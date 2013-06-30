#include "../libFireBird.h"

bool HDD_TAP_GetFileNameByIndex(int Index, char **TAPFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_GetFileNameByIndex");
  #endif

  tTMSTAPTaskTable      *TMSTAPTaskTable;
  dword                 *FileHandle;

  if((Index < 0) || (Index >= TAP_MAX) || !TAPFileName)
  {
    if(TAPFileName) *TAPFileName = NULL;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  //Check if that TAP is running
  if(TMSTAPTaskTable[Index].Status != 1)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check if the file pointer is valid
  if(!TMSTAPTaskTable[Index].file)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check if the file handle is valid
  FileHandle = (dword*)TMSTAPTaskTable[Index].file->handle;
  if(!FileHandle)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(FileHandle[0] != 0xcdacedaf)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  *TAPFileName = (char*)FileHandle[2];

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
