#include                "../libFireBird.h"

bool Appl_ExportChData(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_ExportChData");
  #endif

  bool (*__Appl_ExportChData)(char*);
  bool ret = FALSE;

  __Appl_ExportChData = (void*)FIS_fwAppl_ExportChData();
  if(__Appl_ExportChData) ret = __Appl_ExportChData(FileName);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
