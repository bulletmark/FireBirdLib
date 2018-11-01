#include                <string.h>
#include                "FBLib_flash.h"

bool FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites)
{
  TRACEENTER();

  tFavorites           *Favs30100;
  tFavorites1050       *Favs1050;
  int                   NrGroups, NrSvcsPerGroup;
  int                   NrTVServices, NrRadioServices;
  int                   i;

  //FavNum out of range
  if((FavNum < 0) || (FavNum > FlashFavoritesGetTotal()))
  {
    TRACEEXIT();
    return FALSE;
  }

  //Favorites is NULL
  if(!Favorites)
  {
    TRACEEXIT();
    return FALSE;
  }

  Favs30100 = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  if(!Favs30100)
  {
    TRACEEXIT();
    return FALSE;
  }

  Favs1050 = (tFavorites1050*)Favs30100;

  FlashFavoritesGetParameters(&NrGroups, &NrSvcsPerGroup);

  if(FavNum >= NrGroups)
  {
    TRACEEXIT();
    return FALSE;
  }

  //Check if any channel is out of range
  TAP_Channel_GetTotalNum(&NrTVServices, &NrRadioServices);
  for(i = 0; i < min(Favorites->NrEntries, NrSvcsPerGroup); i++)
  {
    if(((Favorites->SvcType[i] == SVC_TYPE_Tv) && (Favorites->SvcNum[i] >= NrTVServices)) || ((Favorites->SvcType[i] == SVC_TYPE_Radio) && (Favorites->SvcNum[i] >= NrRadioServices)))
    {
      TRACEEXIT();
      return FALSE;
    }
  }

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
      Favs1050->NrEntries = min(Favorites->NrEntries, 50);
      Favs1050->unused1 = Favorites->unused1;
      break;
    }
  }

  TRACEEXIT();
  return TRUE;
}
