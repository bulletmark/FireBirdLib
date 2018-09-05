#ifndef FBLIB_DEBUG_H
#define FBLIB_DEBUG_H

  #include "libFireBird.h"

  #define DEFAULTMAGIC        0xFB1BB100
  #define CTSTACKSIZE         50
  #define CTSTATENTRIES       5000
  #define CRASHCHECKINI       "CrashCheck.ini"

  typedef struct
  {
    char                     *ProcName;
    dword                     MinTime;
    dword                     MaxTime;
    dword                     NrCalls;
    dword                     TotalTime;
  } tCallTraceStats;

  typedef struct
  {
    char                     *ProcName;
    dword                     EntryTime;
  } tCallTraceStack;

  extern dword                CallLevel;
  extern tCallTraceStack      CallTraceStack[CTSTACKSIZE];
  extern bool                 CallTraceEnabled;
  extern bool                 CallTraceInitialized;
  extern tCallTraceStats     *CallTraceStats;
  extern int                  CallTraceStatsEntries;
  extern bool                 CallTraceDoNotReenter;

#endif
