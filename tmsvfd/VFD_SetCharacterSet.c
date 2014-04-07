#include "FBLib_tmsvfd.h"

tVFDCharset CurrentCharset = CS_8859_1;

bool VFD_SetCharacterSet(tVFDCharset VFDCharset)
{
  TRACEENTER();

  CurrentCharset = VFDCharset;

  TRACEEXIT();
  return TRUE;
}
