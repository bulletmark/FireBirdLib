#include "../libFireBird.h"

inline dword FIS_vGrid(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vGrid");
  #endif

  static dword          _grid = 0;

  if(!_grid)
    _grid = TryResolve("_grid");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _grid;
}
