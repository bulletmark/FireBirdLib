#include                "FBLib_tmsvfd.h"
#include                "VFDSegmentMap.h"
#include                "VFDSegmentMapCyrillic.h"
#include                "VFDSegmentMapHappy.h"

dword VFD_TranslateSegments(byte Character, DISPLAYSTYLE DisplayStyle)
{
  if (CurrentCharset == CS_8859_5)
    switch (DisplayStyle)
    {
      case VFD_7:  return VFDSegmentMap7_c[Character];
      case VFD_14: return VFDSegmentMap14_c[Character];
      case VFD_17: return VFDSegmentMap17_c[Character];

      default:
        break;
    }
  else if (CurrentCharset == CS_8859_1_HAPPY)
    switch (DisplayStyle)
    {
      case VFD_7:  return VFDSegmentMap7_h[Character];
      case VFD_14: return VFDSegmentMap14_h[Character];
      case VFD_17: return VFDSegmentMap17_h[Character];

      default:
        break;
    }
  else
    switch (DisplayStyle)
    {
      case VFD_7:  return VFDSegmentMap7[Character];
      case VFD_14: return VFDSegmentMap14[Character];
      case VFD_17: return VFDSegmentMap17[Character];

      default:
        break;
    }

  return 0;
}
