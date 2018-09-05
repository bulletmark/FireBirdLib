#include                "FBLib_TMSOSDMenu.h"

#include                "graphic/pfeil_l.gd"
#include                "graphic/pfeil_l_bright.gd"
#include                "graphic/pfeil_r.gd"
#include                "graphic/pfeil_r_bright.gd"

void OSDDrawList(void)
{
  TRACEENTER;

  int                   i;
  dword                 XStart, XEnd, Y;
  tMenu                *pMenu;
  tItem                *pItem;
  dword                 ItemColor;
  char                  s[4];
  dword                 MaxNameIconWidth, MaxValueIconWidth;

  pMenu = &Menu[CurrentMenuLevel];

  //Get maximum width of icons
  MaxNameIconWidth = 0;
  MaxValueIconWidth = 0;
  for(i = 0; i < pMenu->NrItems; i++)
  {
    if(pMenu->Item[i].pNameIconGd && (pMenu->Item[i].pNameIconGd->width > MaxNameIconWidth)) MaxNameIconWidth = pMenu->Item[i].pNameIconGd->width;
    if(pMenu->Item[i].pValueIconGd && (pMenu->Item[i].pValueIconGd->width > MaxValueIconWidth)) MaxValueIconWidth = pMenu->Item[i].pValueIconGd->width;
    if(pMenu->Item[i].ColorPatch && (MaxValueIconWidth < 50)) MaxValueIconWidth = 50;
  }

  if(MaxNameIconWidth) MaxNameIconWidth += 8;
  if(MaxValueIconWidth) MaxValueIconWidth += 8;

  //The background
  TAP_Osd_Draw3dBoxFill(OSDRgn, 60, 96, 600, 367, RGB(30, 30, 30), RGB(30, 30, 30), RGB(30, 30, 30));

  for(i = 0; i < 10; i++)
  {
    pItem = &pMenu->Item[i + pMenu->CurrentTopIndex];

    //Draw the background or selection bar and the optional value arrows
    if((i + pMenu->CurrentTopIndex) == pMenu->CurrentSelection)
    {
      OSDMenuDrawCursor(60, 95 + (i * 37), 600);

      if(pMenu->HasValueColumn && pItem->ValueArrows)
      {
        TAP_Osd_PutGd(OSDRgn, pMenu->ValueXPos + 20 , 95 + 10 +(i * 37), (MenuCursorType == CT_Standard ? &_pfeil_l_Gd : &_pfeil_l_bright_Gd), TRUE);
        TAP_Osd_PutGd(OSDRgn, 640 , 95 + 10 +(i * 37), (MenuCursorType == CT_Standard ? &_pfeil_r_Gd : &_pfeil_r_bright_Gd), TRUE);
      }
    }
    else
    {
      TAP_Osd_DrawRectangle(OSDRgn, 60, 130 + (i * 37), 600, 2, 1, RGB(16, 16, 16));
    }

    XEnd = (pMenu->HasValueColumn ? pMenu->ValueXPos : 645);
    Y = 99 + (i * 37);

    if(pItem->Selectable)
      ItemColor = pItem->TextColor;
    else
      ItemColor = RGB(128, 128, 140);

    //Line numbers
    if(pMenu->NumberedItems)
    {
      int MaxX = 100;

      XStart = 101;

      if(pItem->CustomIndex >= 0)
      {
        TAP_SPrint(s, "%2.2d", pItem->CustomIndex);

        if(pItem->CustomIndex > 99)
        {
          XStart += 10;
          MaxX += 10;
        }

        if(pItem->CustomIndex > 999)
        {
          XStart += 10;
          MaxX += 10;
        }
      }
      else
      {
        TAP_SPrint(s, "%2.2d", i + pMenu->CurrentTopIndex + 1);

        if(i + pMenu->CurrentTopIndex + 1 > 99)
        {
          XStart += 10;
          MaxX += 10;
        }

        if(i + pMenu->CurrentTopIndex + 1 > 999)
        {
          XStart += 10;
          MaxX += 10;
        }
      }

      FMUC_PutStringAA(OSDRgn, 71, Y + 5 + FONTYOFFSET, MaxX, s, ItemColor, COLOR_None, pMenu->FontListLineNumber, FALSE, ALIGN_LEFT, 1);
    }
    else
    {
      XStart = 76;
    }

    //Icons on the left column
    if(pItem->pNameIconGd)
      TAP_Osd_PutGd(OSDRgn, XStart, Y + 13 - (pItem->pNameIconGd->height >> 1), pItem->pNameIconGd, TRUE);

    //The text of the left column
    FMUC_PutStringAA(OSDRgn, XStart + MaxNameIconWidth, Y + 5 + FONTYOFFSET, XEnd, pItem->Name, ItemColor, COLOR_None, pMenu->FontListNameColumn, TRUE, ALIGN_LEFT, 1);

    if(pMenu->HasValueColumn)
    {
      //The text of the right column
      FMUC_PutStringAA(OSDRgn, pMenu->ValueXPos + 45 + MaxValueIconWidth, Y + 5 + FONTYOFFSET, 645, pItem->Value, ItemColor, COLOR_None, pMenu->FontListValueColumn, TRUE, ALIGN_LEFT, 1);

      //The color patch or icon of the right column. The former has priority
      if(pItem->ColorPatch)
      {
        TAP_Osd_FillBox(OSDRgn, pMenu->ValueXPos + 45, Y + 5, 50, 18, (pItem->ColorPatch & 0x00ffffff) | 0xff000000);
        TAP_Osd_DrawRectangle(OSDRgn, pMenu->ValueXPos + 45, Y + 5, 50, 18, 1, RGB(192,192,192));
      }
      else
      {
        if(pItem->pValueIconGd)
          TAP_Osd_PutGd(OSDRgn, pMenu->ValueXPos + 45 , Y + 13 - (pItem->pValueIconGd->height >> 1), pItem->pValueIconGd, TRUE);
      }
    }
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_List, OSDRgn);

  TRACEEXIT;
}
