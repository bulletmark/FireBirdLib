#include                <string.h>
#include                "FBLib_flash.h"

bool FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashFavoritesSetInfo");
  #endif

  tFavorites           *Favs30100;
  tFavorites1050       *Favs1050;
  int                   NrGroups, NrSvcsPerGroup;

  //FavNum out of range
  if((FavNum < 0) || (FavNum >= FlashFavoritesGetTotal()))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Favorites is NULL
  if(!Favorites)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  Favs30100 = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs30100)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
