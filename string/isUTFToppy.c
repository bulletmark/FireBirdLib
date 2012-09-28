#include                "../libFireBird.h"

bool isUTFToppy(void)
{
  return FIS_fwAppl_ConvertToValidUTF8Str() != 0;
}
