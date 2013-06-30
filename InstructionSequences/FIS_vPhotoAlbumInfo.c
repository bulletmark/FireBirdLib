#include "../libFireBird.h"

inline dword FIS_vPhotoAlbumInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPhotoAlbumInfo");
  #endif

  static dword          vphotoAlbumInfo = 0;

  if(!vphotoAlbumInfo)
    vphotoAlbumInfo = TryResolve("_photoAlbumInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vphotoAlbumInfo;
}
