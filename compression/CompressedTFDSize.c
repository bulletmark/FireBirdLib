#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword CompressedTFDSize(byte *pSrc, dword SourceBufferSize, void *pPercentFinishedCallback)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("CompressedTFDSize");
  #endif

  dword ret = CompressTFD(pSrc, SourceBufferSize, NULL, 0, 0, pPercentFinishedCallback);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
