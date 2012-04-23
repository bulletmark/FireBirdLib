#include                <string.h>
#include                "../libFireBird.h"

char *FlashFavoritesGetSelectedGroupName(void)
{
  static char           FavName[12];
  tFavorites            Favorites;

  if(FlashFavoritesGetInfoCurrent(&Favorites))
    strcpy(FavName, Favorites.GroupName);
  else
    FavName[0] = '\0';

  return FavName;
}
