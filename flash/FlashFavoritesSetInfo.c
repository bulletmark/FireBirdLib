#include                <string.h>
#include                "FBLib_flash.h"

bool FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites)
{
  tFavorites           *Favs;

  //FavNum out of range
  if((FavNum < 0) || (FavNum >= FlashFavoritesGetTotal())) return FALSE;

  //Favorites is NULL
  if(!Favorites) return FALSE;

  //There is no system specific information in the fav group
  Favs = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs) return 0;

  Favs += FavNum;
  memcpy(Favs, Favorites, sizeof(tFavorites));

  return TRUE;
}
