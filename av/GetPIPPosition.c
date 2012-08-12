#include "FBLib_av.h"
#include "../libFireBird.h"

bool GetPIPPosition(int *North, int *South, int *East, int *West)
{
#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("GetPIPPosition");
#endif

  byte                 *_isPipActive;
  word                 *_pipX, *_pipY, *_pipW, *_pipH;

  _isPipActive = (byte*)FIS_vIsPipActive();
  _pipX = (word*)FIS_vPipX();
  _pipY = (word*)FIS_vPipY();
  _pipW = (word*)FIS_vPipW();
  _pipH = (word*)FIS_vPipH();

  if(_isPipActive)
  {
    if(*_isPipActive)
    {
      if (West)  *West  = *_pipX;
      if (East)  *East  = *_pipX + *_pipW;
      if (North) *North = *_pipY;
      if (South) *South = *_pipY + *_pipH;
    }
    else
    {
      if (West)  *West  = 0;
      if (East)  *East  = 0;
      if (North) *North = 0;
      if (South) *South = 0;
    }
  }

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return (_isPipActive != 0);
}
