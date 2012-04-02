#ifndef FBLIB_SHUTDOWN_H
#define FBLIB_SHUTDOWN_H

#ifdef _TMSEMU_
  #include "tap_tmsemu.h"
#else
  #include "tap.h"
#endif

#define HDDIDLE         0xe1

extern bool LibInitialized;

#endif
