#include "../libFireBird.h"

void FlushCache(dword *pAddr, int Size)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlushCache");
  #endif

  //Unsupported in the TMSEmu environment
  #ifdef _TMSEMU_
    (void)pAddr;
    (void)Size;

  #else
    dword *pEnd = pAddr + Size;

    do
    {
      __asm__(
      "  .set mips3\n"
      "  cache 0x10,0(%0)\n" // invalidate instruction cache
      "  cache 0x15,0(%0)\n" // flush data cache
      : : "r" (pAddr));
      pAddr += 4;
    } while(pAddr < pEnd);
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
