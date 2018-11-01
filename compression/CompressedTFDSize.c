#include                "libFireBird.h"
#include                "FBLib_compression.h"

dword CompressedTFDSize(byte *pSrc, dword SourceBufferSize, void *pPercentFinishedCallback)
{
  TRACEENTER();

  dword ret = CompressTFD(pSrc, SourceBufferSize, NULL, 0, 0, pPercentFinishedCallback);

  TRACEEXIT();
  return ret;
}
