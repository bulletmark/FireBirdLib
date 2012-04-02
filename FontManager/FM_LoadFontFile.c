#include                "FBLib_FontManager.h"

bool FM_LoadFontFile(char *FontFileName, tFontData *FontData)
{
  TYPE_File            *f;
  dword                 GreyScaleSize;
  dword                 i, j, k;

  if(!FontFileName || !FontFileName[0] || !FontData) return FALSE;

  memset(FontData, 0, sizeof(tFontData));

  if(!TAP_Hdd_Exist(FontFileName)) return FALSE;

  f = TAP_Hdd_Fopen(FontFileName);
  if(f == NULL) return FALSE;

  TAP_Hdd_Fread(FontData->FontDef, sizeof(tFontDef), 191, f);

  GreyScaleSize = 0;
  for(i = 0; i < 191; i++)
    GreyScaleSize += (FontData->FontDef[i].Width * FontData->FontDef[i].Height);

  FontData->pFontData = TAP_MemAlloc(GreyScaleSize);

  i = 0;
  j = GreyScaleSize;
  do
  {
    k = j;
    if(k > 32768) k = 32768;
    TAP_Hdd_Fread(&FontData->pFontData[i], k, 1, f);
    i += k;
    j -= k;
  }while(j > 0);

  TAP_Hdd_Fclose(f);

  return TRUE;
}
