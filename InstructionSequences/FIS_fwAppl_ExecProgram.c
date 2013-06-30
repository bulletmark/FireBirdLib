#include "../libFireBird.h"

inline dword FIS_fwAppl_ExecProgram(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ExecProgram");
  #endif

  static dword          _Appl_ExecProgram = 0;

  if(!_Appl_ExecProgram)
    _Appl_ExecProgram = TryResolve("_Z16Appl_ExecProgramPc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ExecProgram;
}
