#include                <string.h>
#include                "FBLib_FontManager.h"

dword FM_GetStringWidth(char *Text, tFontData *FontData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_GetStringWidth");
  #endif

  dword                 i;
  dword                 Width = 0;

  if(!Text || !Text[0] || !FontData || !FontData->pFontData)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  for(i = 0; i < strlen(Text); i++)
  {
    if(FM_isValidCharacter(Text[i]))
      Width += FontData->FontDef[FM_CharToIndex(Text[i])].Width;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Width;
}
