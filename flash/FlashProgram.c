#include "FBLib_flash.h"

void FlashProgram(void)
{
  TRACEENTER();

  void(*Appl_WriteFlash)(bool);

  Appl_WriteFlash = (void*)FIS_fwAppl_WriteFlash();
  if(!Appl_WriteFlash) Appl_WriteFlash(TRUE);

  TRACEEXIT();
}
