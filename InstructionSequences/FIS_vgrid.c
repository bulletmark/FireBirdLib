#include "../libFireBird.h"

inline dword FIS_vGrid(void)
{
  static dword          _grid = 0;

  if (!_grid)
    _grid = TryResolve("_grid");

  return _grid;
}
