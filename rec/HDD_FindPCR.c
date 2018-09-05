#include "libFireBird.h"

int HDD_FindPCR(byte *pBuffer, dword BufferSize, word PID)
{
  TRACEENTER;

  dword		        i = 0;
  dword		        PCR;

  if(PID > 0x1ffe)
  {
    TRACEEXIT;
    return -1;
  }

  do
  {
    if((pBuffer[i + 0] == 0x47) && ((((pBuffer[i + 1] & 0x1f) == (PID >> 8)) && (pBuffer[i + 2] == (PID & 0xff))) || PID == 0) && ((pBuffer[i + 3] & 0x20) != 0) && (pBuffer[i + 4] > 0) && ((pBuffer[i + 5] & 0x10) != 0))
    {
      //Extract the time out of the PCR bit pattern
      //The PCR is clocked by a 90kHz generator. To convert to minutes
      //the 33 bit number can be shifted right 6 times and divided by 84375
      PCR = (pBuffer[i + 6] << 19) | (pBuffer[i + 7] << 11) | (pBuffer[i + 8] << 3) | (pBuffer[i + 9] >> 5);
      PCR /= 84375;

      TRACEEXIT;
      return (int) PCR;
    }
    i += 188;
  } while(i < (BufferSize - 188));

  TRACEEXIT;
  return -1;
}
