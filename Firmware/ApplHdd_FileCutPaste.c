#include                "../libFireBird.h"

dword ApplHdd_FileCutPaste(char  const* SourceFileName, unsigned int StartBlock, unsigned int NrBlocks, char const* CutFileName)
{
  dword                 (*__ApplHdd_FileCutPaste)(char  const*, unsigned int, unsigned int, char  const*);
  dword                 ret= 0;

  __ApplHdd_FileCutPaste = (void*)FIS_fwApplHdd_FileCutPaste();
  if(__ApplHdd_FileCutPaste) ret = __ApplHdd_FileCutPaste(SourceFileName, StartBlock, NrBlocks, CutFileName);

  return ret;
}
