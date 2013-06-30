#include "FBLib_FontManager.h"

void FM_MakeFontDir(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_MakeFontDir");
  #endif

  HDD_TAP_PushDir();
  HDD_ChangeDir("/ProgramFiles");
  if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
  HDD_ChangeDir("Settings");
  if(!TAP_Hdd_Exist("Fonts")) TAP_Hdd_Create("Fonts", ATTR_FOLDER);
  HDD_ChangeDir("Fonts");
  HDD_TAP_PopDir();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
