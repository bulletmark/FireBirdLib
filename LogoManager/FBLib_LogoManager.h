#ifndef FBLIB_LOGOMANAGER_H
#define FBLIB_LOGOMANAGER_H

  #include "tap.h"

  #define MAXLOGONAME         40

  typedef struct
  {
    ulong64             ChannelID;     //(SatLong << 48) | (NetworkID << 32) | (StreamID << 16) | SID
    char                LogoName[MAXLOGONAME+1];
    tLogoStyle          Style;
    tLogoSize           Size;
    tLogoAspect         Aspect;
    dword               CachePosition;
    dword               grDataSize;
    TYPE_GrData        *grData;     //convert pixel data to gdData on the fly
  } tLogoData;

  extern tLogoData     *LogoManager_LogoData;
  extern int            LogoManager_NrLogos;
  extern bool           LogoManager_LUTInitialized;

  extern void (*LogoManager_CB)(int CallbackType, int Param1);
#endif
