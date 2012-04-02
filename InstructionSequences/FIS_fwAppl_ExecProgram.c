#include "../libFireBird.h"

inline dword FIS_fwAppl_ExecProgram(void)
{
  static dword          _Appl_ExecProgram = 0;

  if (!_Appl_ExecProgram)
    _Appl_ExecProgram = TryResolve("_Z16Appl_ExecProgramPc");

  return _Appl_ExecProgram;
}
