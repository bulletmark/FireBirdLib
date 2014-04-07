#include "../libFireBird.h"

inline dword FIS_vGrid(void)
{
  TRACEENTER();

  static dword          _grid = 0;

  if(!_grid)
    _grid = TryResolve("_grid");

  TRACEEXIT();
  return _grid;
}
