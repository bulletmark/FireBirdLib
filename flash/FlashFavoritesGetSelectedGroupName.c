#include                <string.h>
#include                "libFireBird.h"

//Minimum size of FavName should be 12
char *FlashFavoritesGetSelectedGroupName(char *FavName, byte FavNameSize)
{
  TRACEENTER;

  tFavorites            Favorites;

  if(FavName && FavNameSize)
  {
    if(FlashFavoritesGetInfoCurrent(&Favorites))
    {
      strncpy(FavName, Favorites.GroupName, FavNameSize - 1);
      FavName[FavNameSize - 1] = '\0';
    }
    else
      FavName[0] = '\0';
  }

  TRACEEXIT;
  return FavName;
}
