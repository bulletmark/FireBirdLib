#include                "FBLib_tmsvfd.h"
#include                "VFDSegmentMap.h"
#include                "VFDSegmentMapCyrillic.h"
#include                "VFDSegmentMapHappy.h"

dword VFD_TranslateSegments(byte Character, DISPLAYSTYLE DisplayStyle)
{
  TRACEENTER;

  dword ret;

  ret = 0;
  if(CurrentCharset == CS_8859_5)
    switch(DisplayStyle)
    {
      case VFD_7:  ret = VFDSegmentMap7_c[Character]; break;
      case VFD_14: ret = VFDSegmentMap14_c[Character]; break;
      case VFD_17: ret = VFDSegmentMap17_c[Character]; break;

      default:
        break;
    }
  else if(CurrentCharset == CS_8859_1_HAPPY)
    switch(DisplayStyle)
    {
      case VFD_7:  ret = VFDSegmentMap7_h[Character]; break;
      case VFD_14: ret = VFDSegmentMap14_h[Character]; break;
      case VFD_17: ret = VFDSegmentMap17_h[Character]; break;

      default:
        break;
    }
  else
    switch(DisplayStyle)
    {
      case VFD_7:  ret = VFDSegmentMap7[Character]; break;
      case VFD_14: ret = VFDSegmentMap14[Character]; break;
      case VFD_17: ret = VFDSegmentMap17[Character]; break;

      default:
        break;
    }

  TRACEEXIT;
  return ret;
}
