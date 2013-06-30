#include                <string.h>
#include                "FBLib_flash.h"

int FlashFavoritesFindService(int SvcType, int SvcNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashFavoritesFindService");
  #endif

  tFavorites            Favs;
  int                   i, j, NrFavs;

  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //SvcNum out of range
  if((SvcNum < 0) || (SvcNum >= FlashServiceGetTotal(SvcType)))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }


  NrFavs = FlashFavoritesGetTotal();
  for(i = 0; i < NrFavs; i++)
  {
    if(FlashFavoritesGetInfo(i, &Favs))
    {
      for(j = 0; j < Favs.NrEntries; j++)
        if((Favs.SvcType[j] == SvcType) && (Favs.SvcNum[j] == SvcNum))
        {
          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return i;
        }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return -1;
}
