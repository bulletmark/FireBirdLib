#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMemoInitialize(bool ScrollLoop, const char *TitleLeft, const char *TitleRight, const char *Text)
{
  tMenu                *pMenu;

  TRACEENTER();

  OSDMenuInitialize(FALSE, FALSE, FALSE, ScrollLoop, TitleLeft, TitleRight);
  pMenu = &Menu[CurrentMenuLevel];
  pMenu->OSDMenuDisplayMode = OMDM_Memo;
  pMenu->NrLines = 15;

  if(!Text || !Text[0])
  {
    TRACEEXIT();
    return;
  }

  pMenu->MemoText = TAP_MemAlloc(strlen(Text) + 2);
  memset(pMenu->MemoText, 0, strlen(Text) + 2);
  strcpy(pMenu->MemoText, Text);
  StrReplace(pMenu->MemoText, "\x8d", "\r");
  StrReplace(pMenu->MemoText, "\x8a", "\n");
  StrReplace(pMenu->MemoText, "\r\n", "\n");
  if (pMenu->MemoText[strlen(pMenu->MemoText) - 1] != '\n') strcat(pMenu->MemoText, "\n");

  OSDMemoFormatText();

  TRACEEXIT();
}
