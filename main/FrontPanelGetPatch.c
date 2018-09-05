#include                <unistd.h>
#include                "FBLib_main.h"

bool FrontPanelGetPatch(byte *Version, byte *Type)
{
  TRACEENTER;

  FP_Initialize();

  if(Version) *Version = FPPatchVersion;
  if(Type) *Type = FPPatchType;

  TRACEEXIT;
  return (FPPatchVersion != 0);
}
