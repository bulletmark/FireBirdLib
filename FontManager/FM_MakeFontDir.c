#include "FBLib_FontManager.h"

void FM_MakeFontDir(void)
{
  TRACEENTER();

  HDD_TAP_PushDir();
  HDD_ChangeDir(DIR_PROGRAMFILES);
  if(!TAP_Hdd_Exist(DIR_SETTINGS)) TAP_Hdd_Create(DIR_SETTINGS, ATTR_FOLDER);
  if(!TAP_Hdd_Exist(DIR_FONTS)) HDD_ChangeDir(DIR_SETTINGS);
  if(!TAP_Hdd_Exist(DIR_FONTS)) TAP_Hdd_Create(DIR_FONTS, ATTR_FOLDER);
  HDD_ChangeDir(DIR_FONTS);
  HDD_TAP_PopDir();

  TRACEEXIT();
}
