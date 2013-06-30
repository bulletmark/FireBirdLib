#include "FBLib_tap.h"

dword HDD_TAP_GetIDByIndex(int TAPIndex)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_GetIDByIndex");
  #endif

  tTMSTAPTaskTable     *TMSTAPTaskTable;
  char                  AbsFileName[100];
  tTAPInfo              pTAPInfo;

  if((TAPIndex < 0) || (TAPIndex >= TAP_MAX))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(TMSTAPTaskTable == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(!HDD_GetAbsolutePathByTypeFile(TMSTAPTaskTable[TAPIndex].file, AbsFileName))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(!HDD_TAP_GetInfoByAbsPath(AbsFileName, &pTAPInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return pTAPInfo.TAPID;
}
