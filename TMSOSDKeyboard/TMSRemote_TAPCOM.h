#ifndef __TMSREMOTETAPCOMH__
#define __TMSREMOTETAPCOMH__

#define TMSREMOTETAPID                    0x8E0A4230

//The following command returns a dword with the status of TMSRemote
//.... .... .... .... .... .... .... ..HC
//C ... 1 if someone is connected
//H ... 1 if OSD is set to hidden

#define TMSREMOTE_TAPCOM_SERVICE_STATUS       0
#define TMSREMOTE_TAPCOM_SERVICE_SETDIRECT    1
#define TMSREMOTE_TAPCOM_SERVICE_CLEARDIRECT  2

#endif
