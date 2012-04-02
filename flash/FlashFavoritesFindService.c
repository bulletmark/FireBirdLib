#include                <string.h>
#include                "FBLib_flash.h"

int FlashFavoritesFindService(int SvcType, int SvcNum)
{
  tFavorites           *Favs;
  int                   i, j, NrFavs;

  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio)) return FALSE;

  //SvcNum out of range
  if((SvcNum < 0) || (SvcNum >= FlashServiceGetTotal(SvcType))) return FALSE;

  //There is no system specific information in the fav group
  Favs = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs) return 0;

  NrFavs = FlashFavoritesGetTotal();
  for(i = 0; i < NrFavs; i++)
  {
    for(j = 0; j < Favs->NrEntries; j++)
      if((Favs->SvcType[j] == SvcType) && (Favs->SvcNum[j] == SvcNum))
        return i;

    Favs++;
  }

  return -1;
}
