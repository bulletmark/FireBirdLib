#include                "libFireBird.h"

bool Appl_ExportChData(char *FileName)
{
  TRACEENTER();

  bool (*__Appl_ExportChData)(char*);
  bool ret = FALSE;

  __Appl_ExportChData = (void*)FIS_fwAppl_ExportChData();
  if(__Appl_ExportChData) ret = __Appl_ExportChData(FileName);

  TRACEEXIT();
  return ret;
}
