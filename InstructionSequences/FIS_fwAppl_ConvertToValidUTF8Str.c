#include "../libFireBird.h"

inline dword FIS_fwAppl_ConvertToValidUTF8Str(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ConvertToValidUTF8Str");
  #endif

  static dword          _Appl_ConvertToValidUTF8Str = 0;

  if(!_Appl_ConvertToValidUTF8Str)
    _Appl_ConvertToValidUTF8Str = TryResolve("_Z26Appl_ConvertToValidUTF8StrPhi");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ConvertToValidUTF8Str;
}
