#include                <string.h>
#include                "FBLib_FontManager.h"

bool FMUC_LoadFontFile(char *FontFileName, tFontDataUC *FontData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FMUC_LoadFontFile");
  #endif

  char                  Hdr[5];

  if(!FontFileName || !FontFileName[0] || !FontData)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Initialize the struct
  memset(FontData, 0, sizeof(tFontDataUC));

  //Open the font file
  HDD_TAP_PushDir();
  HDD_ChangeDir(FONTSDIR);

  if(!TAP_Hdd_Exist(FontFileName))
  {
    char                s[120];
    extern char         __tap_program_name__[MAX_PROGRAM_NAME];

    TAP_SPrint(s, "failed to load %s", FontFileName);
    LogEntryFBLibPrintf(TRUE, "FontManager UC: %s", s);
    ShowMessageWin(__tap_program_name__, s, "Please install the font", 300);
    HDD_TAP_PopDir();

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  FontData->FileHandle = TAP_Hdd_Fopen(FontFileName);
  HDD_TAP_PopDir();
  if(FontData->FileHandle == NULL)
  {
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to open '%s'", FontFileName);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check the header
  TAP_Hdd_Fread(Hdr, 4, 1, FontData->FileHandle);
  Hdr[4] = '\0';
  if(strcmp(Hdr, "UFNT"))
  {
    TAP_Hdd_Fclose(FontData->FileHandle);
    FontData->FileHandle = NULL;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: '%s' has invalid header", FontFileName);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Read the size of the FontDef table and allocate the necessary memory
  TAP_Hdd_Fread(&FontData->FontDefEntries, sizeof(dword), 1, FontData->FileHandle);
  FontData->FontDef = FMUC_ReserveMemory("FMUC_LoadFontFile FontDef", FontData->FontDefEntries * sizeof(tFontDefUC));

  if(FontData->FontDef == NULL)
  {
    TAP_Hdd_Fclose(FontData->FileHandle);
    FontData->FileHandle = NULL;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to allocate %d bytes for the FontDef table of '%s'", FontData->FontDefEntries * sizeof(tFontDefUC), FontFileName);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to allocate %d bytes for the FontCache table of '%s'", FontData->FontDefEntries * sizeof(tGlyphCacheUC), FontFileName);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
