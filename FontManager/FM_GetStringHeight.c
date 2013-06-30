#include                <string.h>
#include                "FBLib_FontManager.h"

dword FM_GetStringHeight(char *Text, tFontData *FontData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_GetStringHeight");
  #endif

  dword                 i;
  dword                 h, Height = 0;

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
    {
      h = FontData->FontDef[FM_CharToIndex(Text[i])].Height;
      if(h > Height) Height = h;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Height;
}
