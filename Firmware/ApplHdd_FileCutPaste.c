#include                "../libFireBird.h"

dword ApplHdd_FileCutPaste(char *SourceFileName, unsigned int StartBlock, unsigned int NrBlocks, char *CutFileName)
{
  TRACEENTER();

  dword                 (*__ApplHdd_FileCutPaste)(char*, unsigned int, unsigned int, char*);
  dword                 ret= 0;

  __ApplHdd_FileCutPaste = (void*)FIS_fwApplHdd_FileCutPaste();
  if(__ApplHdd_FileCutPaste) ret = __ApplHdd_FileCutPaste(SourceFileName, StartBlock, NrBlocks, CutFileName);

  TRACEEXIT();
  return ret;
}
