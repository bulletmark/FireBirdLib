#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedLoaderSize(byte *pSrc)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("UncompressedLoaderSize");
  #endif

  word                  compSize, uncompSize;
  dword                 outSize = 0;

  if(!pSrc)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  uncompSize = LOAD_WORDLE(pSrc + 0);
  compSize   = LOAD_WORDLE(pSrc + 2);

  while(uncompSize != 0xfefe)
  {
    if(uncompSize > 0x8000)
    {
      //Uncompressed data block size too large
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }
    pSrc += (4 + compSize);
    outSize += uncompSize;

    uncompSize = LOAD_WORDLE(pSrc + 0);
    compSize   = LOAD_WORDLE(pSrc + 2);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return outSize;
}
