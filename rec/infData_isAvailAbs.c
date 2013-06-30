#include <tap.h>
#include "FBLib_rec.h"

bool infData_isAvailAbs(char *infFileName, char *NameTag, dword *PayloadSize)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_isAvailAbs");
  #endif

  ret = FALSE;

  if(infData_OpenFileAbs(infFileName))
    ret = infData_LocateSigAbs(NameTag, PayloadSize);

  infData_CloseFileAbs();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
