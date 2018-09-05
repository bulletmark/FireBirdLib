#ifndef FBLIB_TAP_H
#define FBLIB_TAP_H

#include "libFireBird.h"

#define MAGIC             0xf1eb1d1b
#define TAPDIR_MAX_STACK  16
#define BATCHMODEKEY      0x15227
#define PARAMBLOCKKEY     0x15228

extern char             TAPDirStack[TAPDIR_MAX_STACK][200];

extern int TAPDirStackDepth;
extern bool LibInitialized;

typedef struct
{
  dword                 magic;
  dword                 id;
  dword                 pParameterBlock;
} TYPE_Parametered_Tap;

extern TYPE_Parametered_Tap *fbl_parametered_tap;

dword HDD_TAP_DisabledEventHandler(word, dword, dword);
dword KeyTranslateHook(word, dword, dword);

#endif
