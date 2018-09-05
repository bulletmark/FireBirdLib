#include                "libFireBird.h"

word ApplHdd_GetFileInfo(word p1, int *TotalBlocks, int *CurrentBlock, byte p4, byte p5)
{
  TRACEENTER;

  word (*__ApplHdd_GetFileInfo)(word, int *TotalBlocks, int *CurrentBlock, byte, byte);
  word ret = 0;

  __ApplHdd_GetFileInfo = (void*)FIS_fwApplHdd_GetFileInfo();
  if(__ApplHdd_GetFileInfo) ret = __ApplHdd_GetFileInfo(p1, TotalBlocks, CurrentBlock, p4, p5);

  TRACEEXIT;
  return ret;
}
