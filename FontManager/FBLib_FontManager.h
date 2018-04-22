#ifndef FBLIB_FONTMANAGER_H
#define FBLIB_FONTMANAGER_H

  #include              "../libFireBird.h"

  #define FONTDIR       "/ProgramFiles/Settings/Fonts"

  typedef struct
  {
    byte  r;
    byte  g;
    byte  b;
  } tAlphaLUT;

  extern tAlphaLUT  AlphaLUT[256];

  void           *FMUC_ReserveMemory(char *Requester, dword size);
  void            FMUC_FreeMemory(char *Requester, void *Pointer);

  bool            FM_isValidCharacter(byte Char);
  byte            FM_CharToIndex(byte Char);
  byte            FM_AlphaBlend(byte Alpha, byte FG, byte BG, float AntiAliasFactor);
  void            FM_InitAlphaLUT(dword fgColor, dword bgColor, float AntiAliasFactor);
  dword           FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG, float AntiAliasFactor);

  tGlyphCacheUC  *FMUC_GetGlyphData(tFontDataUC *FontData, byte *UTF8Character, byte *BytesPerChar);
  byte           *FMUC_FindUTF8Start(byte *p);
  byte           *FMUC_FindNextUTF8(byte *p);
  bool            FMUC_IsDiacriticalMark(dword Character);

  typedef struct
  {
    char                 *Requester;
    dword                 Size;
    void                 *Alloc;
  } tFMUC_MemDebug;

  void            FMUC_MemoryDump(dword *NrReservations, dword *NrTotalSize);
  tFMUC_MemDebug *FMUC_MemoryFindFree(void);
  tFMUC_MemDebug *FMUC_MemoryFindPointer(void *Pointer);

#endif
