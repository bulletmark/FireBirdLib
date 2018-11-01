#include                "libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedFirmwareSize(byte *pSrc)
{
  TRACEENTER();

  word                  compSize = 0, uncompSize = 0;
  dword                 outSize = 0;

  if(!pSrc)
  {
    TRACEEXIT();
    return 0;
  }

  compSize   = LOAD_WORD(pSrc + 2);
  uncompSize = LOAD_WORD(pSrc + 0);

  while(uncompSize != 0xfefe)
  {
    if(uncompSize > 0x8000)
    {
      //Uncompressed data block size too large
      TRACEEXIT();

      return 0;
    }

    pSrc += (6 + compSize);
    outSize += uncompSize;

    compSize   = LOAD_WORD(pSrc + 2);
    uncompSize = LOAD_WORD(pSrc + 0);
  }

  TRACEEXIT();
  return outSize;
}
