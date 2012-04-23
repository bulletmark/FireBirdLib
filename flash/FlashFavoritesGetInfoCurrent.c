#include                <string.h>
#include                "../libFireBird.h"

bool FlashFavoritesGetInfoCurrent(tFavorites *Favorites)
{
  byte                 *EEPROM;  //Size = 128
  byte                  NrGrps, CurrentGroup;

  NrGrps = FlashFavoritesGetTotal();
  EEPROM = (byte*)FIS_vEEPROM();
  CurrentGroup = EEPROM[0x0012];

  if((NrGrps == 0) || !Favorites || (CurrentGroup == 0xFF)) return FALSE;

  return FlashFavoritesGetInfo(CurrentGroup, Favorites);
}
