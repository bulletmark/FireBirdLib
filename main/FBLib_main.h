#ifndef FBLIB_MAIN_H
#define FBLIB_MAIN_H

#include "../libFireBird.h"

#define FIRMWAREDAT   "FirmwareTMS.dat"

typedef struct
{
 dword                  SubCommand;
 dword                  P1;
 dword                  P2;
 dword                  P3;
} tBIOSType;

extern bool             LibInitialized;
extern int              _appl_version;

#endif
