#include                <string.h>
#include                "FBLib_FontManager.h"

dword FM_GetStringWidth(char *Text, tFontData *FontData)
{
  TRACEENTER;

  dword                 i;
  dword                 Width = 0;

  if(!Text || !Text[0] || !FontData || !FontData->pFontData)
  {
    TRACEEXIT;
    return 0;
  }

  for(i = 0; i < strlen(Text); i++)
  {
    if(FM_isValidCharacter(Text[i]))
      Width += FontData->FontDef[FM_CharToIndex(Text[i])].Width;
  }

  TRACEEXIT;
  return Width;
}
