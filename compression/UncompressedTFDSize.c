#include                "libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedTFDSize(byte *pSrc)
{
  TRACEENTER;

  word                  compSize = 0, uncompSize = 0, NrBlocks = 0;
  dword                 outSize = 0, i;

  if(!pSrc)
  {
    TRACEEXIT;
    return 0;
  }

  if(LOAD_WORD(pSrc) != 8)
  {
    //Invalid header
    TRACEEXIT;
    return 0;
  }

  if(CRC16 (0, pSrc + 4, 6) != LOAD_WORD(pSrc + 2))
  {
    //Invalid header CRC
    TRACEEXIT;
    return 0;
  }

  if(LOAD_WORD(pSrc + 6) != 1)
  {
    //Invalid file version
    TRACEEXIT;
    return 0;
  }

  NrBlocks = LOAD_WORD(pSrc + 8);

  pSrc += 10;

  for(i = 0; i < NrBlocks; i++)
  {
    compSize   = LOAD_WORD(pSrc) - 6;
    uncompSize = LOAD_WORD(pSrc + 6);

    if(uncompSize > 0x7ffa)
    {
      //Uncompressed data block size too large
      TRACEEXIT;

      return 0;
    }

    pSrc += compSize + 8;
    outSize += uncompSize;
  }

  TRACEEXIT;
  return outSize;
}
