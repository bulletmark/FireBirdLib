#include                <string.h>
#include                "FBLib_flash.h"

bool FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites)
{
  tFavorites           *Favs30100;
  tFavorites1050       *Favs1050;
  int                   NrGroups, NrSvcsPerGroup;

  //FavNum out of range
  if((FavNum < 0) || (FavNum >= FlashFavoritesGetTotal())) return FALSE;

  //Favorites is NULL
  if(!Favorites) return FALSE;

  Favs30100 = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs30100) return 0;
  Favs1050 = (tFavorites1050*)Favs30100;

  FlashFavoritesGetParameters(&NrGroups, &NrSvcsPerGroup);
  switch(NrSvcsPerGroup)
  {
    case 100:
    {
      Favs30100 += FavNum;
      memcpy(Favs30100, Favorites, sizeof(tFavorites));
      break;
    }

    case 50:
    {
      Favs1050 += FavNum;
      memcpy(Favs1050->GroupName, Favorites->GroupName, sizeof(Favs1050->GroupName));
      memcpy(Favs1050->SvcNum, Favorites->SvcNum, sizeof(Favs1050->SvcNum));
      memcpy(Favs1050->SvcType, Favorites->SvcType, sizeof(Favs1050->SvcType));
      Favs1050->NrEntries = Favorites->NrEntries;
      Favs1050->unused1 = Favorites->unused1;
      break;
    }
  }

  return TRUE;
}
