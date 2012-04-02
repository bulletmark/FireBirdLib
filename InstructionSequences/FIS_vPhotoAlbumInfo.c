#include "../libFireBird.h"

inline dword FIS_vPhotoAlbumInfo(void)
{
  static dword          vphotoAlbumInfo = 0;

  if (!vphotoAlbumInfo)
    vphotoAlbumInfo = TryResolve("_photoAlbumInfo");

  return vphotoAlbumInfo;
}
