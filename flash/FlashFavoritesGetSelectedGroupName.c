#include                <string.h>
#include                "../libFireBird.h"

char *FlashFavoritesGetSelectedGroupName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashFavoritesGetSelectedGroupName");
  #endif

  static char           FavName[12];
  tFavorites            Favorites;

  if(FlashFavoritesGetInfoCurrent(&Favorites))
    strcpy(FavName, Favorites.GroupName);
  else
    FavName[0] = '\0';

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FavName;
}
