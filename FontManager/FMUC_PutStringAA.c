#include                <stdlib.h>
#include                <string.h>
#include                "FBLib_FontManager.h"

#undef malloc
#undef free

void FMUC_PutStringAA(word rgn, dword x, dword y, dword maxX, char *str, dword fcolor, dword bcolor, tFontDataUC *FontData, byte bDot, byte align, float AntiAliasFactor)
{
  TRACEENTER();

  dword                 XEnd, YEnd;
  dword                *PixelData;
  byte                 *FontBitmap;
  byte                 *p, *pEnd;
  dword                 X, Y;
  dword                 CX, CY, CW, CH;
  dword                 SaveBoxX;
  dword                 dotWidth;
  char                 *newstr;
  int                   width = 0, newstrlen;
  dword                 LastBackgroundPixel = 0;
  byte                  LastForegroundPixel = 0;
  dword                 LastPixel = 0;
  byte                  Grey;
  tGlyphCacheUC        *GlyphData;
  byte                  BytesPerChar;
  bool                  hasAnsiChars, hasUTFChars;

  //Remember the last position for diacritical marks
  bool                  isDiacriticalMark;
  int                   LastCC, NextCX;

  if(!str || !str[0] || !FontData || (maxX <= x))
  {
    TRACEEXIT();
    return;
  }

  if(GetOSDRegionWidth(rgn) && GetOSDRegionWidth(rgn) <= maxX) maxX = GetOSDRegionWidth(rgn) - 1;

  //Convert to UTF8 if necessary
  GetStringEncoding(str, &hasAnsiChars, &hasUTFChars);
  if(hasAnsiChars && !hasUTFChars)
  {
    newstr = malloc((strlen(str) << 2) + 20);
    if(newstr == NULL)
    {
      TRACEEXIT();
      return;
    }

    StrToUTF8(str, newstr, 9);
  }
  else
  {
    newstrlen = strlen(str) + 20;
    newstr = malloc(newstrlen);
    if(newstr == NULL)
    {
      TRACEEXIT();
      return;
    }

    strncpy(newstr, str, newstrlen);
    newstr[newstrlen - 1] = '\0';
  }
  MakeValidFileName(newstr, ControlChars | LFChars);

  XEnd = x + FMUC_GetStringWidth(newstr, FontData);
  dotWidth = 0;

  switch(bDot)
  {
    case 0:
    {
      char *p;

      if(XEnd > maxX)
      {
        newstrlen = strlen(newstr);
        p = FMUC_FindUTF8Start(&newstr[newstrlen - 1]);

        do
        {
          GlyphData = FMUC_GetGlyphData(FontData, p, NULL);
          if(GlyphData)
          {
            width = GlyphData->Width;
            XEnd -= width;
            *p = '\0';
          }
          p = FMUC_FindUTF8Start(p - 1);
          newstrlen--;
        } while((XEnd > maxX) && (width != 0) && (newstrlen > 0) && (p > newstr));
      }
      break;
    }

    case 1:
    {
      char *p;

      if(XEnd > maxX)
      {
        dotWidth = FMUC_GetStringWidth("... ", FontData);
        XEnd += dotWidth;

        newstrlen = strlen(newstr);
        p = FMUC_FindUTF8Start(&newstr[newstrlen - 1]);
        do
        {
          GlyphData = FMUC_GetGlyphData(FontData, p, NULL);
          if(GlyphData)
          {
            width = GlyphData->Width;
            XEnd -= width;
            *p = '\0';
          }
          p = FMUC_FindUTF8Start(p - 1);
          newstrlen--;
        } while((XEnd > maxX) && (width != 0) && (newstrlen > 0) && (p > newstr));
        strcat(newstr, "...");
      }
      break;
    }

    case 2:
    {
      char *p;

      p = newstr;
      if(XEnd > maxX)
      {
        dotWidth = FMUC_GetStringWidth("...", FontData);
        XEnd += dotWidth;
        newstrlen = strlen(newstr);
        do
        {
          GlyphData = FMUC_GetGlyphData(FontData, p, NULL);
          if(GlyphData)
          {
            width = GlyphData->Width;
            XEnd -= width;
          }
          p = FMUC_FindNextUTF8(p);
          newstrlen--;
        } while((XEnd > maxX) && (width != 0) && (newstrlen > 0));

        DeleteAt(newstr, 0, (int)(p - newstr));
        InsertAt(newstr, 0, "...");
      }
      break;
    }
  }

  if(XEnd > maxX)
  {
    free(newstr);

    TRACEEXIT();
    return;
  }

  YEnd = y + FMUC_GetStringHeight(newstr, FontData);
  if(XEnd > maxX) XEnd = maxX;

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
    TAP_Osd_FillBox(rgn, x, y, maxX - x, YEnd - y + 1, bcolor);
    FM_InitAlphaLUT(fcolor, bcolor, AntiAliasFactor);
  }

  PixelData = (dword*) TAP_Osd_SaveBox(rgn, SaveBoxX, y, XEnd - x + 1, YEnd - y + 1);
  if(PixelData)
  {
    CX = 0;
    LastCC = 0;
    NextCX = 0;
    p = newstr;
    pEnd = p + strlen(p);

    while(p < pEnd)
    {
      GlyphData = FMUC_GetGlyphData(FontData, p, &BytesPerChar);
      if(GlyphData)
      {
        isDiacriticalMark = FMUC_IsDiacriticalMark(GlyphData->Unicode);

        if(isDiacriticalMark)
        {
          //Jump back to the position of the last character based in the width of both glyphs
          NextCX = CX;
          CX = LastCC - (GlyphData->Width >> 1);
        }

        FontBitmap = GlyphData->GlyphData;
        CW = GlyphData->Width;
        CH = GlyphData->Height;

        for(Y = 0; Y < CH; Y++)
        {
          CY = (XEnd - x + 1) * Y;

          dword  *pd = &PixelData[CX + CY];

          for(X = 0; X < CW; X++)
          {
            Grey = *FontBitmap++;
            if(Grey != 0x00)
            {
              if(Grey == 0xff)
              {
                *pd = fcolor;
              }
              else
              {
                if(bcolor & 0xff000000)
                {
                  *pd = (fcolor & 0xff000000) | (AlphaLUT[Grey].r << 16) | (AlphaLUT[Grey].g << 8) | AlphaLUT[Grey].b;
                }
                else
                {
                  if((LastForegroundPixel != Grey) || (LastBackgroundPixel != *pd))
                  {
                    LastBackgroundPixel = *pd;
                    LastForegroundPixel = Grey;
                    LastPixel = (fcolor & 0xff000000) | FM_AlphaBlendRGB(Grey, fcolor, LastBackgroundPixel, AntiAliasFactor);
                  }

                  *pd = LastPixel;
                }
              }
            }
            pd++;
          }
        }

        if(isDiacriticalMark)
        {
          CX = NextCX;
        }
        else
        {
          //Calculate the center of the character
          LastCC = CX + (CW >> 1);
          CX += CW;
        }
      }
      p += BytesPerChar;
    }

    TAP_Osd_RestoreBox(rgn, SaveBoxX, y, XEnd - x + 1, YEnd - y + 1, PixelData);
    TAP_MemFree(PixelData);
  }

  free(newstr);

  TRACEEXIT();
}
