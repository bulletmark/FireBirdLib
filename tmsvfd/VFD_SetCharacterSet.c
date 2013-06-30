#include "FBLib_tmsvfd.h"

tVFDCharset CurrentCharset = CS_8859_1;

bool VFD_SetCharacterSet(tVFDCharset VFDCharset)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_SetCharacterSet");
  #endif

  CurrentCharset = VFDCharset;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
