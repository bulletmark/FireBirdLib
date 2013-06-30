#include "../libFireBird.h"

inline dword FIS_vMACAddress(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vMACAddress");
  #endif

  static dword          MacAddress;
  dword                 MacAddressSize;

  int (*DevEeprom_GetMacAddr)(unsigned char *pMacAddress, dword *MacAddressSize);

  if(!MacAddress)
  {
    DevEeprom_GetMacAddr = (void*)TryResolve("DevEeprom_GetMacAddr");

    if(DevEeprom_GetMacAddr)
      DevEeprom_GetMacAddr((unsigned char*)&MacAddress, &MacAddressSize);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return MacAddress;
}
