#include <string.h>
#include "FBLib_TMSOSDMenu.h"

#define HORSPACE 568

void OSDMemoFormatText (void)
{
  tMenu *pMenu;
  dword spW, Width = 0;
  char *buffer, *from, *upto, *p, c;

  TRACEENTER();

  pMenu = &Menu[CurrentMenuLevel];

  if (!pMenu->MemoText)
  {
    TRACEEXIT();
    return;
  }

  OSDMenuItemsClear();

  spW = FMUC_GetStringWidth(" ", pMenu->FontMemo);

  buffer = TAP_MemAlloc(strlen(pMenu->MemoText) + 1);
  strcpy(buffer, pMenu->MemoText);

  from = buffer;
  upto = from - 1;

  while ((p = strpbrk(upto + 1, " \n")))
  {
    c = *p;
    *p = 0;

    Width += FMUC_GetStringWidth(upto + 1, pMenu->FontMemo) + (c == ' ' ? spW : 0);

    if (Width > HORSPACE)
    {
      if (upto < from) upto = p;

      *upto = 0;
      OSDMenuItemAdd(from, NULL, NULL, NULL, TRUE, FALSE, 0);
      from = upto + 1;
      Width = 0;
    }
    else
    {
      if (c == '\n')
      {
        OSDMenuItemAdd(*from ? from : " ", NULL, NULL, NULL, TRUE, FALSE, 0);
        from = p + 1;
        Width = 0;
      }

      upto = p;
    }

    *p = c;
  }

  TAP_MemFree(buffer);

  TRACEEXIT();
}
