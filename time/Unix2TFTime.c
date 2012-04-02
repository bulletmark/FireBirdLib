#include                "../libFireBird.h"

dword Unix2TFTime(dword UnixTimeStamp)
{
  return (((int)(UnixTimeStamp / 86400) + 0x9e8b) << 16) | (((int)(UnixTimeStamp / 3600) % 24) << 8) | ((UnixTimeStamp / 60) % 60);
}
