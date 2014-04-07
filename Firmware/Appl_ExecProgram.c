#include                "../libFireBird.h"

void Appl_ExecProgram(char *FileName)
{
  TRACEENTER();

  void  (*__Appl_ExecProgram)(char*);

  __Appl_ExecProgram = (void*)FIS_fwAppl_ExecProgram();
  if(__Appl_ExecProgram) __Appl_ExecProgram(FileName);

  TRACEEXIT();
}
