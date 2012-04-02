#include		"../libFireBird.h"

byte *GetMacAddress(void)
{
  return (byte*)FIS_vMACAddress();
}
