#include                <string.h>
#include                "FBLib_FontManager.h"

bool FMUC_LoadFontFile(char *FontFileName, tFontDataUC *FontData)
{
  TRACEENTER();

  char                  Hdr[5];
  char                  FileName[MAX_FILE_NAME_SIZE+1];

  //Initialize the struct
  if(FontData) memset(FontData, 0, sizeof(tFontDataUC));

  if(!FontFileName || !FontFileName[0] || !FontData)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FontFileName, FileName, PF_FileNameOnly);

  //Open the font file
  HDD_TAP_PushDir();
  HDD_ChangeDir(FONTSDIR);

  if(!TAP_Hdd_Exist(FileName))
  {
    char                s[120];
    extern char         __tap_program_name__[MAX_PROGRAM_NAME];

    TAP_SPrint(s, "failed to load %s", FileName);
    LogEntryFBLibPrintf(TRUE, "FontManager UC: %s", s);
    ShowMessageWin(__tap_program_name__, s, "Please install the font", 300);
    HDD_TAP_PopDir();

    TRACEEXIT();
    return FALSE;
  }

  FontData->FileHandle = TAP_Hdd_Fopen(FileName);
  HDD_TAP_PopDir();
  if(FontData->FileHandle == NULL)
  {
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to open '%s'", FileName);

    TRACEEXIT();
    return FALSE;
  }

  //Check the header
  TAP_Hdd_Fread(Hdr, 4, 1, FontData->FileHandle);
  Hdr[4] = '\0';
  if(strcmp(Hdr, "UFNT"))
  {
    TAP_Hdd_Fclose(FontData->FileHandle);
    FontData->FileHandle = NULL;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: '%s' has invalid header", FileName);

    TRACEEXIT();
    return FALSE;
  }

  //Read the size of the FontDef table and allocate the necessary memory
  TAP_Hdd_Fread(&FontData->FontDefEntries, sizeof(dword), 1, FontData->FileHandle);
  FontData->FontDef = FMUC_ReserveMemory("FMUC_LoadFontFile FontDef", FontData->FontDefEntries * sizeof(tFontDefUC));

  if(FontData->FontDef == NULL)
  {
    TAP_Hdd_Fclose(FontData->FileHandle);
    FontData->FileHandle = NULL;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to allocate %d bytes for the FontDef table of '%s'", FontData->FontDefEntries * sizeof(tFontDefUC), FileName);

    TRACEEXIT();
    return FALSE;
  }

  //LogEntryFBLibPrintf(TRUE, "FontManager UC: %d glyphs available in '%s'", FontData->FontDefEntries, FontFileName);

  //Read the FontDef table
  TAP_Hdd_Fread(FontData->FontDef, sizeof(tFontDefUC), FontData->FontDefEntries, FontData->FileHandle);

  //Reserve memory for the font cache
  FontData->GlyphCacheEntries = 0;

  FontData->GlyphCache = FMUC_ReserveMemory("FMUC_LoadFontFile GlyphCache", FontData->FontDefEntries * sizeof(tGlyphCacheUC));
  if(FontData->GlyphCache == NULL)
  {
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to allocate %d bytes for the FontCache table of '%s'", FontData->FontDefEntries * sizeof(tGlyphCacheUC), FileName);

    TRACEEXIT();
    return FALSE;
  }

  TRACEEXIT();
  return TRUE;
}
