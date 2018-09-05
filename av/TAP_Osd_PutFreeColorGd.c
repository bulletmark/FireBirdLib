#include "libFireBird.h"

int TAP_Osd_PutFreeColorGd(word rgn, int x, int y, TYPE_GrData *gd, bool sprite, dword FilterColor)
{
  TRACEENTER;

  int                   ret;
  int                   R, G, B;
  dword                 FR, FG, FB;
  word                  TempRgn;
  dword                 *PixelData = NULL;
  register dword        oy, cx, cy, p, P;

  //Use a temporary memory region
  TempRgn = TAP_Osd_Create_Chk("TAP_Osd_PutFreeColorGd", 0, 0, gd->width, gd->height, 0, OSD_Flag_MemRgn);

  //Copy Gd data into OSD region
  ret = TAP_Osd_PutGd_Chk("TAP_Osd_PutFreeColorGd A", TempRgn, 0, 0, gd, sprite);

  //Save the OSD so we get a memory pointer to the pixel data
  if(!ret) PixelData = (dword *) TAP_Osd_SaveBox_Chk("TAP_Osd_PutFreeColorGd A", TempRgn, 0, 0, gd->width, gd->height);

  if(ret || !PixelData)
  {
    TAP_Osd_Delete(TempRgn);

    TRACEEXIT;
    return(ret ? ret : -1);
  }

  FR = (FilterColor >> 16) & 0xff;
  FG = (FilterColor >>  8) & 0xff;
  FB =  FilterColor        & 0xff;

  //This routine manipulates the RGB data
  for(oy = 0, cy = 0; cy < gd->height; cy++)
  {
    for(cx = 0; cx < gd->width; cx++)
    {
      //Calculate the pixel index out of the X/Y coordinates
      p = cx + oy;

      //Extract the colors and apply the filter function
      P = PixelData[p];

      //This algo subtracts the complementary color
      //OSD_8888
      B = (P & 0xff) - 255 + FB; if(B < 0) B = 0; if(B > 255) B = 255;
      P >>= 8;
      G = (P & 0xff) - 255 + FG; if(G < 0) G = 0; if(G > 255) G = 255;
      P >>= 8;
      R = (P & 0xff) - 255 + FR; if(R < 0) R = 0; if(R > 255) R = 255;
      P >>= 8;
      PixelData[p] = ARGB(P, R, G, B);
    }

    oy += gd->width;
  }

  //Restore the modified OSD
  TAP_Osd_RestoreBox_Chk("TAP_Osd_PutFreeColorGd", TempRgn, 0, 0, gd->width, gd->height, PixelData);
  TAP_Osd_Copy_Chk("TAP_Osd_PutFreeColorGd B", TempRgn, rgn, 0, 0, gd->width, gd->height, x, y, TRUE);
  TAP_MemFree(PixelData);
  TAP_Osd_Delete(TempRgn);

  TRACEEXIT;
  return 0;
}
