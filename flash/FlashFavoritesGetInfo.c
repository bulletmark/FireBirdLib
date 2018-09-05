#include                <string.h>
#include                "FBLib_flash.h"

bool FlashFavoritesGetInfo(int FavNum, tFavorites *Favorites)
{
  TRACEENTER;

  tFavorites           *Favs30100;
  tFavorites1050       *Favs1050;
  int                   NrGroups, NrSvcsPerGroup;

  //FavNum out of range
  if((FavNum < 0) || (FavNum >= FlashFavoritesGetTotal()))
  {
    TRACEEXIT;
    return FALSE;
  }

  //Favorites is NULL
  if(!Favorites)
  {
    TRACEEXIT;
    return FALSE;
  }

  Favs30100 = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs30100)
  {
    TRACEEXIT;
    return 0;
  }
  Favs1050 = (tFavorites1050*)Favs30100;

  FlashFavoritesGetParameters(&NrGroups, &NrSvcsPerGroup);
  switch(NrSvcsPerGroup)
  {
    case 100:
    {
      Favs30100 += FavNum;
      memcpy(Favorites, Favs30100, sizeof(tFavorites));
      break;
    }

    case 50:
    {
      Favs1050 += FavNum;
      memcpy(Favorites->GroupName, Favs1050->GroupName, sizeof(Favs1050->GroupName));
      memcpy(Favorites->SvcNum, Favs1050->SvcNum, sizeof(Favs1050->SvcNum));
      memcpy(Favorites->SvcType, Favs1050->SvcType, sizeof(Favs1050->SvcType));
      Favorites->NrEntries = Favs1050->NrEntries;
      Favorites->unused1 = Favs1050->unused1;
      break;
    }
  }

  TRACEEXIT;
  return TRUE;
}
