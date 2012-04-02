#include "../libFireBird.h"

// 6: HD[1080i]
// 7: HD[720p]
// 8: SD[576p]
// 9: SD[576i]
//10: ???
//11: HD[1080i]
//12: HD[720p]
//13: SD[480p]
//14: SD[480i]
//ff: unknown

byte GetStreamFormat(byte Index)
{
  byte(*Appl_GetStreamFormat)(byte);

  Appl_GetStreamFormat = (void*)FIS_fwAppl_GetStreamFormat();

  if(Appl_GetStreamFormat) return Appl_GetStreamFormat(Index);

  return 0xff;
}
