#include                <string.h>
#include                "FBLib_FontManager.h"

void FM_PutStringAA(word rgn, dword x, dword y, dword maxX, char *str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align, float AntiAliasFactor)
{
  TRACEENTER();

  int                   XEnd, YEnd;
  dword                *PixelData;
  byte                 *FontBitmap;
  dword                 i, X, Y;
  dword                 CX, CY, CW, CH;
  dword                 SaveBoxX;
  dword                 dotWidth;
  char                  newstr[256];
  int                   width = 0, newstrlen;
  int                   CharIndex;

  dword                 LastBackgroundPixel = 0;
  byte                  LastForegroundPixel = 0;
  dword                 LastPixel = 0;
  byte                  Grey = 0;
  dword                 repcnt;
  bool                  compressed_font;
  dword                 StrLen;

  if(!str || !str[0] || !FontData || !FontData->pFontData || (maxX <= x))
  {
    TRACEEXIT();
    return;
  }

  if(GetOSDRegionWidth(rgn) && GetOSDRegionWidth(rgn) <= maxX) maxX = GetOSDRegionWidth(rgn) - 1;

  strncpy(newstr, str, sizeof(newstr));
  newstr[sizeof(newstr) - 1] = '\0';

  XEnd = x + FM_GetStringWidth(newstr, FontData) - 1;
  dotWidth = 0;

  switch(bDot)
  {
    case 0:
    {
      char *p;

      p = &newstr[strlen(newstr) - 1];
      if(XEnd > (int)maxX)
      {
        newstrlen = strlen(newstr);
        do
        {
          if(FM_isValidCharacter(*p))
          {
            width = FontData->FontDef[FM_CharToIndex(*p)].Width;
            XEnd -= width;
          }
          *p = '\0';
          p--;
          newstrlen--;
        } while((XEnd > (int)maxX) && (width != 0) && (newstrlen > 0));
      }
      break;
    }

    case 1:
    {
      char *p;

      p = &newstr[strlen(newstr) - 1];
      if(XEnd > (int)maxX)
      {
        dotWidth = FM_GetStringWidth("...", FontData);
        XEnd += dotWidth;
        newstrlen = strlen(newstr);
        do
        {
          if(FM_isValidCharacter(*p))
          {
            width = FontData->FontDef[FM_CharToIndex(*p)].Width;
            XEnd -= width;
          }
          *p = '\0';
          p--;
          newstrlen--;
        } while((XEnd > (int)maxX) && (width != 0) && (newstrlen > 0));
        strcat(newstr, "...");
      }
      break;
    }

    case 2:
    {
      char *p;

      p = newstr;
      if(XEnd > (int)maxX)
      {
        dotWidth = FM_GetStringWidth("...", FontData);
        XEnd += dotWidth;
        newstrlen = strlen(newstr);
        do
        {
          if(FM_isValidCharacter(*p))
          {
            width = FontData->FontDef[FM_CharToIndex(*p)].Width;
            XEnd -= width;
          }
          p++;
          newstrlen--;
        } while((XEnd > (int)maxX) && (width != 0) && (newstrlen > 0));
        DeleteAt(newstr, 0, (int)(p - newstr));
        InsertAt(newstr, 0, "...");
      }

      break;
    }
  }

  if(XEnd > (int)maxX)
  {
    TRACEEXIT();
    return;
  }

  YEnd = y + FM_GetStringHeight(newstr, FontData) - 1;

  switch(align)
  {
    case ALIGN_LEFT:
    {
      SaveBoxX = x;
      break;
    }

    case ALIGN_CENTER:
    {
      SaveBoxX = x + ((maxX - XEnd) >> 1);
      break;
    }

    case ALIGN_RIGHT:
    {
      SaveBoxX = maxX - (XEnd - x);
      break;
    }

    default:
      SaveBoxX = x;
      break;
  }

  if(bcolor & 0xff000000)
  {
    TAP_Osd_FillBox(rgn, x, y, maxX - x + 1, YEnd - y + 1, bcolor);
    FM_InitAlphaLUT(fcolor, bcolor, AntiAliasFactor);
  }

  PixelData = (dword*) TAP_Osd_SaveBox(rgn, SaveBoxX, y, XEnd - x + 1, YEnd - y + 1);
  if(PixelData)
  {
    CX = 0;
    StrLen = strlen(newstr);
    for(i = 0; i < StrLen; i++)
    {
      if(FM_isValidCharacter(newstr[i]))
      {
        CharIndex = FM_CharToIndex(newstr[i]);
        FontBitmap = &FontData->pFontData[CharIndex == 0 ? 0 : FontData->FontDef[CharIndex].BitmapIndex];
        CW = FontData->FontDef[CharIndex].Width;
        CH = FontData->FontDef[CharIndex].Height;
        compressed_font = FontData->FontDef[0].BitmapIndex != 0;

        repcnt = 0;
        for(Y = 0; Y < CH; Y++)
        {
          CY = (XEnd - x + 1) * Y;
          for(X = 0; X < CW; X++)
          {
            if(repcnt == 0)
            {
              Grey = *FontBitmap++;

              /* Compressed fonts have repeat counts after every 0x00
               * and 0xff bytes */
              if(compressed_font && (Grey == 0x00 || Grey == 0xff))
                repcnt = *FontBitmap++ - 1;
            }
            else
              --repcnt;

            if(Grey != 0x00)
            {
              if(Grey == 0xff)
              {
                PixelData[CX + X + CY] = fcolor;
              }
              else
              {
                //Verhalten von bcolor.A
                if(bcolor & 0xff000000)
                {
                  PixelData[CX + X + CY] = (fcolor & 0xff000000) | (AlphaLUT[Grey].r << 16) | (AlphaLUT[Grey].g << 8) | AlphaLUT[Grey].b;
                }
                else
                {
                  if((LastForegroundPixel != Grey) || (LastBackgroundPixel != PixelData[CX + X + CY]))
                  {
                    LastBackgroundPixel = PixelData[CX + X + CY];
                    LastForegroundPixel = Grey;
                    LastPixel = (fcolor & 0xff000000) | FM_AlphaBlendRGB(Grey, fcolor, LastBackgroundPixel, AntiAliasFactor);
                  }

                  PixelData[CX + X + CY] = LastPixel;
                }
              }
            } // if grey else
          } // for x
        } // for y
        CX += CW;
      } // if FM_ValidChar
    } // for i

    TAP_Osd_RestoreBox(rgn, SaveBoxX, y, XEnd - x + 1, YEnd - y + 1, PixelData);
    TAP_MemFree(PixelData);
  } // if PixelData

  TRACEEXIT();
}
