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

extern byte             FPPatchVersion;
extern byte             FPPatchType;
extern byte             FPPatchAntiFreezeOption;
extern byte             FPPatchPowerRestoreOption;
extern bool             FPPatchInitialized;
extern byte             FPWaitResponse;
extern byte             FPResponse[12];

void Front_TxPacket_hooked(byte *Data);
int  PutMsgQ_hooked(dword *MsgQ, dword *Data);
void UnhookFrontTxPacket(void);
bool HookFrontTxPacket(void);
bool FP_Initialize(void);


#endif
