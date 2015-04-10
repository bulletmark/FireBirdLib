#include                <stdlib.h>
#include                "FBLib_FontManager.h"

#undef malloc
#undef free

bool FM_LoadFontFile(char *FontFileName, tFontData *FontData)
{
  TRACEENTER();

  TYPE_File            *f;
  dword                 GreyScaleSize;
  dword                 i, j, k;
  char                  TAPPath[FBLIB_DIR_SIZE], FileName[MAX_FILE_NAME_SIZE+1];

  //Initialize the struct
  if(FontData) memset(FontData, 0, sizeof(tFontData));

  if(!FontFileName || !FontFileName[0] || !FontData)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FontFileName, TAPPath, PF_TAPPathOnly);
  ConvertPathType(FontFileName, FileName, PF_FileNameOnly);

  HDD_TAP_PushDir();
  if(*TAPPath) HDD_ChangeDir(TAPPath);
  if(!TAP_Hdd_Exist(FileName))
  {
    char                s[120];
    extern char         __tap_program_name__[MAX_PROGRAM_NAME];

    TAP_SPrint(s, "failed to load %s", FileName);
    LogEntryFBLibPrintf(TRUE, "FontManager: %s", s);
    ShowMessageWin(__tap_program_name__, s, "Please install the font", 300);

    HDD_TAP_PopDir();

    TRACEEXIT();
    return FALSE;
  }

  f = TAP_Hdd_Fopen(FileName);
  if(f == NULL)
  {
    HDD_TAP_PopDir();

    TRACEEXIT();
    return FALSE;
  }

  TAP_Hdd_Fread(FontData->FontDef, sizeof(tFontDef), 191, f);

  /* Check for normal or compressed bitmap font */
  if(FontData->FontDef[0].BitmapIndex == 0)
  {
    /* Normal font file. Last font table entry defines total size */
    GreyScaleSize = FontData->FontDef[190].Width * FontData->FontDef[190].Height + FontData->FontDef[190].BitmapIndex;
  }
  else
  {

    /* Compressed font file. The first index for a compressed bitmap font
     * is set to the size of the bitmap so we can identify and read the
     * bitmap array, even though that index is logically zero.
     */
    GreyScaleSize = FontData->FontDef[0].BitmapIndex;
  }

  FontData->pFontData = malloc(GreyScaleSize);

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

  HDD_TAP_PopDir();

  TRACEEXIT();
  return TRUE;
}
