#include                <fcntl.h>
#include                <unistd.h>
#include                <string.h>
#include                "FBLib_FontManager.h"

bool FMUC_LoadFontFile(char *FontFileName, tFontDataUC *FontData)
{
  TRACEENTER();

  char                  Hdr[5];
  char                  FileName[MAX_FILE_NAME_SIZE+1];
  char                  AbsFileName[512];

  //Initialize the struct
  if(FontData) memset(FontData, 0, sizeof(tFontDataUC));

  if(!FontFileName || !FontFileName[0] || !FontData)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FontFileName, FileName, PF_FileNameOnly);

  //Open the font file
  strcpy(AbsFileName, "/mnt/hd/ProgramFiles/Settings/Fonts/");
  strcat(AbsFileName, FileName);

  FontData->FileHandle = open(AbsFileName, O_RDONLY, 0600);
  if(FontData->FileHandle < 0)
  {
    char                s[120];
    extern char         __tap_program_name__[MAX_PROGRAM_NAME];

    TAP_SPrint(s, "failed to load %s", FileName);
    LogEntryFBLibPrintf(TRUE, "FontManager UC: %s", s);
    ShowMessageWin(__tap_program_name__, s, "Please install the font", 300);

    TRACEEXIT();
    return FALSE;
  }

  //Check the header
  read(FontData->FileHandle, Hdr, 4);
  Hdr[4] = '\0';
  if(strcmp(Hdr, "UFNT"))
  {
    close(FontData->FileHandle);
    FontData->FileHandle = 0;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: '%s' has invalid header", FileName);

    TRACEEXIT();
    return FALSE;
  }

  //Read the size of the FontDef table and allocate the necessary memory
  read(FontData->FileHandle, &FontData->FontDefEntries, sizeof(dword));
  FontData->FontDef = FMUC_ReserveMemory("FMUC_LoadFontFile FontDef", FontData->FontDefEntries * sizeof(tFontDefUC));

  if(FontData->FontDef == NULL)
  {
    close(FontData->FileHandle);
    FontData->FileHandle = 0;
    LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to allocate %d bytes for the FontDef table of '%s'", FontData->FontDefEntries * sizeof(tFontDefUC), FileName);

    TRACEEXIT();
    return FALSE;
  }

  //LogEntryFBLibPrintf(TRUE, "FontManager UC: %d glyphs available in '%s'", FontData->FontDefEntries, FontFileName);

  //Read the FontDef table
  read(FontData->FileHandle, FontData->FontDef, sizeof(tFontDefUC) * FontData->FontDefEntries);

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
