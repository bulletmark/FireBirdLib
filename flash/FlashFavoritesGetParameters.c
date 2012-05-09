#include                "../libFireBird.h"

void FlashFavoritesGetParameters(int *NrGroups, int *NrSvcsPerGroup)
{
  int                   i;

  i = FIS_vFlashBlockGameSaveData() - FIS_vFlashBlockFavoriteGroup();

  if(i == 1644)
  {
    if(NrGroups) *NrGroups  = 10;
    if(NrSvcsPerGroup) *NrSvcsPerGroup  = 50;
  }
  else if(i == 9424)
  {
    if(NrGroups) *NrGroups  = 30;
    if(NrSvcsPerGroup) *NrSvcsPerGroup  = 100;
  }
  else
  {
    TAP_PrintNet("FlashFavoritesGetParameters: unknown favourite structure variant (%d bytes)\n", i);
    if(NrGroups) *NrGroups  = i;
    if(NrSvcsPerGroup) *NrSvcsPerGroup  = i;
  }
}
