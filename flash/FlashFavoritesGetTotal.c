#include                "FBLib_flash.h"

int FlashFavoritesGetTotal(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashFavoritesGetTotal");
  #endif

  int                   i, NrGroups, NrSvcsPerGroup;
  tFavorites           *Favs30100;
  tFavorites1050       *Favs1050;

  Favs30100 = (tFavorites*)FIS_vFlashBlockFavoriteGroup();
  Favs1050 = (tFavorites1050*)Favs30100;

  if(!Favs30100)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  i = 0;

  FlashFavoritesGetParameters(&NrGroups, &NrSvcsPerGroup);
  switch(NrSvcsPerGroup)
  {
    case 100:
    {
      while(Favs30100->GroupName[0])
      {
        i++;
        Favs30100++;
        if(i >= NrSvcsPerGroup) break;
      }
      break;
    }

    case 50:
    {
      while(Favs1050->GroupName[0])
      {
        i++;
        Favs1050++;
        if(i >= NrSvcsPerGroup) break;
      }
      break;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return i;
}
