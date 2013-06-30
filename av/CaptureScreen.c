#include "FBLib_av.h"
#include "../libFireBird.h"

bool CaptureScreen(int BMPwidth, int BMPheight, byte *BMPPixelBuffer, bool bOSD, int Alpha)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("CaptureScreen");
  #endif

  TYPE_VideoFrame       videoFrameMain;
  TYPE_VideoFrame       videoFrameSub;
  TYPE_OsdBaseInfo      osdBaseInfo;
  int                   PIPNorth, PIPSouth, PIPEast, PIPWest;
  bool                  PIPAvail;

  if(!BMPPixelBuffer)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  PIPAvail = GetPIPPosition(&PIPNorth, &PIPSouth, &PIPEast, &PIPWest);

  //Capture main video frame
  memset(&videoFrameMain, 0, sizeof(videoFrameMain));
  videoFrameMain.pixelFormat = OSD_8888;
  videoFrameMain.width = BMPwidth;
  videoFrameMain.height = BMPheight;
  if(!TAP_CaptureScreen(CHANNEL_Main, &videoFrameMain, 0))
  {
    VideoToBMP(&videoFrameMain, BMPwidth, BMPheight, BMPPixelBuffer, 0, 0, BMPwidth, BMPheight);
    TAP_MemFree(videoFrameMain.data);
  }

  if(PIPAvail)
  {
    //Capture PIP
    memset(&videoFrameSub, 0, sizeof(videoFrameSub));
    videoFrameSub.pixelFormat = OSD_8888;
    videoFrameSub.width = BMPwidth;
    videoFrameSub.height = BMPheight;
    if(!TAP_CaptureScreen(CHANNEL_Sub, &videoFrameSub, 0 ))
    {
      VideoToBMP(&videoFrameSub, BMPwidth, BMPheight, BMPPixelBuffer, PIPWest, PIPNorth, PIPEast - PIPWest + 1, PIPSouth - PIPNorth + 1);
      TAP_MemFree(videoFrameSub.data);
    }
  }

  if(bOSD)
  {
    //Capture TAP_PLANE and mix into BMP
    TAP_Osd_GetPlaneBaseInfo(&osdBaseInfo, TAP_PLANE);
    OSDToBMP(&osdBaseInfo, BMPwidth, BMPheight, BMPPixelBuffer, Alpha);

    //Capture SUBT_PLANE and mix into BMP
    TAP_Osd_GetPlaneBaseInfo(&osdBaseInfo, SUBT_PLANE);
    OSDToBMP(&osdBaseInfo, BMPwidth, BMPheight, BMPPixelBuffer, Alpha);

    //Capture BASE_PLANE and mix into BMP
    TAP_Osd_GetPlaneBaseInfo(&osdBaseInfo, BASE_PLANE);
    OSDToBMP(&osdBaseInfo, BMPwidth, BMPheight, BMPPixelBuffer, Alpha);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
