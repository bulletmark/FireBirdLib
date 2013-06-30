#include "../libFireBird.h"

void OSDCopy(word rgn, dword x, dword y, dword w, dword h, word items, eCopyDirection direction)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDCopy");
  #endif

  word                  n;
  dword                 nw, nh;
  dword                 dx, dy;
  dword                 rw, rh;
  dword                 xw, xh;

  nw = w;
  nh = h;
  items++;

  // copy by doubling
  rw = GetOSDRegionWidth(rgn);
  rh = GetOSDRegionHeight(rgn);

  for(n = 1; n <= items >> 1; n <<= 1)
  {
    dx = (direction == X ? x + nw : x);
    dy = (direction == X ? y : y + nh);

    if((dx + nw) <= rw) xw = nw;
                   else xw = rw - dx;

    if((dy + nh) <= rh) xh = nh;
                   else xh = rh - dy;

    TAP_Osd_Copy_Chk("OSDCopy A", rgn, rgn, x, y, xw, xh, dx, dy, TRUE);

    if(direction == X) nw <<= 1;
                  else nh <<= 1;
  }

  n = items - n;

  //copy remaining part
  if(n)
  {
    if(direction == X) w = n * w;
                  else h = n * h;

    dx = (direction == X ? x + nw : x);
    dy = (direction == X ? y : y + nh);

    if((dx + w) <= rw) xw = w;
                  else xw = rw - dx;

    if((dy + h) <= rh) xh = h;
                  else xh = rh - dy;

    TAP_Osd_Copy_Chk("OSDCopy B", rgn, rgn, x, y, xw, xh, dx, dy, TRUE);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
