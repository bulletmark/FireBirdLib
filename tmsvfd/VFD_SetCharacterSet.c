#include "FBLib_tmsvfd.h"

tVFDCharset CurrentCharset = CS_8859_1;

bool VFD_SetCharacterSet(tVFDCharset VFDCharset)
{
  CurrentCharset = VFDCharset;
  
  return TRUE;
}
