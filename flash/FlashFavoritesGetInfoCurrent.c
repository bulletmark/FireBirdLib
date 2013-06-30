#include                <string.h>
#include                "../libFireBird.h"

bool FlashFavoritesGetInfoCurrent(tFavorites *Favorites)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashFavoritesGetInfoCurrent");
  #endif

  byte                 *EEPROM;  //Size = 128
  byte                  NrGrps, CurrentGroup;
  bool                  ret;

  NrGrps = FlashFavoritesGetTotal();
  EEPROM = (byte*)FIS_vEEPROM();
  CurrentGroup = EEPROM[0x0012];

  ret = FALSE;
  if((NrGrps != 0) && Favorites && (CurrentGroup != 0xFF)) ret = FlashFavoritesGetInfo(CurrentGroup, Favorites);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
