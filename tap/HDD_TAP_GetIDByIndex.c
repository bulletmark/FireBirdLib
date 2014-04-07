#include "FBLib_tap.h"

dword HDD_TAP_GetIDByIndex(int TAPIndex)
{
  TRACEENTER();

  tTMSTAPTaskTable     *TMSTAPTaskTable;
  char                  AbsFileName[100];
  tTAPInfo              pTAPInfo;

  if((TAPIndex < 0) || (TAPIndex >= TAP_MAX))
  {
    TRACEEXIT();
    return 0;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(TMSTAPTaskTable == NULL)
  {
    TRACEEXIT();
    return 0;
  }

  if(!HDD_GetAbsolutePathByTypeFile(TMSTAPTaskTable[TAPIndex].file, AbsFileName))
  {
    TRACEEXIT();
    return 0;
  }

  if(!HDD_TAP_GetInfo(AbsFileName, &pTAPInfo))
  {
    TRACEEXIT();
    return 0;
  }

  TRACEEXIT();
  return pTAPInfo.TAPID;
}
