#include                "../libFireBird.h"

int FlashFavoritesGetTotal(void)
{
  int                   i;
  tFavorites           *Favs;

  Favs = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs) return 0;

  i = 0;
  while(Favs->GroupName[0])
  {
    i++;
    Favs++;
  }

  return i;
}
