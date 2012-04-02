 #ifndef FBLIB_TAPCOM_H
#define FBLIB_TAPCOM_H

#include                "../libFireBird.h"

extern bool             LibInitialized;
extern const dword      __tap_ud__;

#define TAPCOM_SIGNATURE  0x14011965
#define TAPCOM_VERSION    0x0000000E	                // Version 0.14
#define TAPCOM_REQVERSION 0x0000000E                    // Downward compatible with version 0.14


bool isValidChannel (TAPCOM_Channel Channel);


typedef struct
{
  dword                 tapcomSignature;  // Signatur, die TAPCOM identifiziert
  dword                 tapcomVersion;    // TAPCOM-Version
  dword                 ServerAlive;      // Wenn der Server l�nger f�r die Bearbeitung ben�tigt ?
  dword                 FromID;           // Wer ist der Sender der Nachricht?
  dword                 ToID;             // Wer ist der Empf�nger der Nachricht?
  TAPCOM_Status         Status;           // Aktueller Zustand des Befehlsblocks
  dword                 ServiceID;        // Welcher Service wird aufgerufen?
  dword                 ParamBlockVersion;// Version des Server-spezifischen Parameterblocks
  void                  *ParamBlock;      // Zeiger auf den Server-spezifischen Parameterblock
  int                   ReturnVal;        // R�ckgabewert f�r Aufrufer
  dword                 Reserved;         // Reserved for fuure use
} TAPCOM_InternalMesBuf;

#endif
