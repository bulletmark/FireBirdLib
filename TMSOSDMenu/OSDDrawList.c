#include                "FBLib_TMSOSDMenu.h"

void OSDDrawList(void)
{
  TRACEENTER();

  int                   i, YText, hL, dLines;
  dword                 XStart, XEnd, yT, yL;
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

  switch (pMenu->NrLines)
  {
    case 18:
      YText = 96 - (5 + FONTYOFFSET);
      hL = 19;
      break;

    case 15:
      YText = 96 - (5 + FONTYOFFSET);
      hL = 23;
      break;

    default:
      YText = 101 - (5 + FONTYOFFSET);
      hL = 35;
      break;
  }

  dLines = hL + 2;

  //The background
  TAP_Osd_Draw3dBoxFill(OSDRgn, 60, 96, 600, pMenu->NrLines * dLines - 2, RGB(30, 30, 30), RGB(30, 30, 30), RGB(30, 30, 30));

  for(i = 0; i < pMenu->NrLines; i++)
  {
    yL = 96 + (i * dLines);

    TAP_Osd_DrawRectangle(OSDRgn, 60, yL + hL, 600, 2, 1, RGB(16, 16, 16));

    pItem = &pMenu->Item[i + pMenu->CurrentTopIndex];

    if ((i + pMenu->CurrentTopIndex) < pMenu->NrItems)
    {
      //Draw the background or selection bar and the optional value arrows
      if ((i + pMenu->CurrentTopIndex) == pMenu->CurrentSelection)
      {
        OSDMenuDrawCursor(60, yL, 600, hL);

        if (pMenu->HasValueColumn && pItem->ValueArrows)
        {
          TAP_Osd_PutGd(OSDRgn, pMenu->ValueXPos + 20, yL + ((hL - _pfeil_l_Gd.height) >> 1), (MenuCursorType == CT_Standard ? &_pfeil_l_Gd : &_pfeil_l_bright_Gd), TRUE);
          TAP_Osd_PutGd(OSDRgn, 640, yL + ((hL - _pfeil_r_Gd.height) >> 1), (MenuCursorType == CT_Standard ? &_pfeil_r_Gd : &_pfeil_r_bright_Gd), TRUE);
        }
      }

      //Draw line content

      XEnd = (pMenu->HasValueColumn && (pItem->ValueArrows || *pItem->Value) ? pMenu->ValueXPos : 645);
      yT = YText + (i * dLines);

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

        FMUC_PutStringAA(OSDRgn, 71, yT + 5 + FONTYOFFSET, MaxX, s, ItemColor, COLOR_None, pMenu->FontListLineNumber, FALSE, ALIGN_LEFT, 1);
      }
      else
      {
        XStart = 76;
      }

      //Icons on the left column
      if(pItem->pNameIconGd)
        TAP_Osd_PutGd(OSDRgn, XStart, yL + ((hL - pItem->pNameIconGd->height) >> 1), pItem->pNameIconGd, TRUE);

      //The text of the left column
      FMUC_PutStringAA(OSDRgn, XStart + MaxNameIconWidth, yT + 5 + FONTYOFFSET, XEnd, pItem->Name, pItem->Selectable ? pItem->NameColor : ItemColor, COLOR_None, pMenu->FontListNameColumn, TRUE, ALIGN_LEFT, 1);

      if(pMenu->HasValueColumn)
      {
        //The text of the right column
        FMUC_PutStringAA(OSDRgn, pMenu->ValueXPos + 30 + pMenu->ValueXOffset + MaxValueIconWidth, yT + 5 + FONTYOFFSET, 645, pItem->Value, ItemColor, COLOR_None, pMenu->FontListValueColumn, TRUE, ALIGN_LEFT, 1);

        //The color patch or icon of the right column. The former has priority
        if(pItem->ColorPatch)
        {
          TAP_Osd_FillBox(OSDRgn, pMenu->ValueXPos + 30 + pMenu->ValueXOffset, yL + ((hL - 18) >> 1) + 1, 50, 18, (pItem->ColorPatch & 0x00ffffff) | 0xff000000);
          TAP_Osd_DrawRectangle(OSDRgn, pMenu->ValueXPos + 30 + pMenu->ValueXOffset, yL + ((hL - 18) >> 1) + 1, 50, 18, 1, RGB(192,192,192));
        }
        else
        {
          if(pItem->pValueIconGd)
            TAP_Osd_PutGd(OSDRgn, pMenu->ValueXPos + 30 + pMenu->ValueXOffset, yL + ((hL - pItem->pValueIconGd->height) >> 1), pItem->pValueIconGd, TRUE);
        }
      }
    }
  }

  if(CallbackProcedure) CallbackProcedure(OSDCB_List, OSDRgn);

  TRACEEXIT();
}
