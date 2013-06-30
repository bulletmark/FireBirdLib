#include "FBLib_flash.h"

void FlashProgram(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashProgram");
  #endif

  void(*Appl_WriteFlash)(bool);

  Appl_WriteFlash = (void*)FIS_fwAppl_WriteFlash();
  if(!Appl_WriteFlash) Appl_WriteFlash(TRUE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
