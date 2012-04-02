#include "FBLib_tap.h"

dword HDD_TAP_GetIDByIndex(int TAPIndex)
{
  tTMSTAPTaskTable     *TMSTAPTaskTable;
  char                  AbsFileName[100];
  tTAPInfo              pTAPInfo;

  if ((TAPIndex < 0) || (TAPIndex >= TAP_MAX)) return 0;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(TMSTAPTaskTable == NULL) return 0;

  if(!HDD_GetAbsolutePathByTypeFile(TMSTAPTaskTable[TAPIndex].file, AbsFileName)) return 0;

  if(!HDD_TAP_GetInfoByAbsPath(AbsFileName, &pTAPInfo)) return 0;

  return pTAPInfo.TAPID;
}
