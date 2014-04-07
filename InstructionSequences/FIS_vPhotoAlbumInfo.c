#include "../libFireBird.h"

inline dword FIS_vPhotoAlbumInfo(void)
{
  TRACEENTER();

  static dword          vphotoAlbumInfo = 0;

  if(!vphotoAlbumInfo)
    vphotoAlbumInfo = TryResolve("_photoAlbumInfo");

  TRACEEXIT();
  return vphotoAlbumInfo;
}
