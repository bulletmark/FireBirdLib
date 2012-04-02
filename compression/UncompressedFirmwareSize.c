#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedFirmwareSize(byte *pSrc)
{
  word                  compSize = 0, uncompSize = 0;
  dword                 outSize = 0;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("UncompressedFirmwareSize");
#endif

  compSize   = LOAD_WORD(pSrc + 2);
  uncompSize = LOAD_WORD(pSrc + 0);

  while (uncompSize != 0xfefe)
  {
    if (uncompSize > 0x8000)
    {

#ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
#endif

      return 0;
    }

    pSrc += (6 + compSize);
    outSize += uncompSize;

    compSize   = LOAD_WORD(pSrc + 2);
    uncompSize = LOAD_WORD(pSrc + 0);
  }

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return outSize;
}
