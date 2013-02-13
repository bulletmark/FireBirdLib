#include                "../libFireBird.h"

bool Appl_ImportChData(char *FileName)
{
  bool (*__Appl_ImportChData)(char*);
  bool ret = FALSE;

  __Appl_ImportChData = (void*)FIS_fwAppl_ImportChData();
  if(__Appl_ImportChData) ret = __Appl_ImportChData(FileName);

  return ret;
}
