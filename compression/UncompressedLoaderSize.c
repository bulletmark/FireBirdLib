#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedLoaderSize(byte *pSrc)
{
  TRACEENTER();

  word                  compSize, uncompSize;
  dword                 outSize = 0;

  if(!pSrc)
  {
    TRACEEXIT();
    return 0;
  }

  uncompSize = LOAD_WORDLE(pSrc + 0);
  compSize   = LOAD_WORDLE(pSrc + 2);

  while(uncompSize != 0xfefe)
  {
    if(uncompSize > 0x8000)
    {
      //Uncompressed data block size too large
      TRACEEXIT();

      return 0;
    }
    pSrc += (4 + compSize);
    outSize += uncompSize;

    uncompSize = LOAD_WORDLE(pSrc + 0);
    compSize   = LOAD_WORDLE(pSrc + 2);
  }

  TRACEEXIT();
  return outSize;
}
