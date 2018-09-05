#ifndef FBLIB_TIME_H
#define FBLIB_TIME_H

  #include "libFireBird.h"

  #define MANUALDSTINI        "DST.ini"

  extern tDSTRule             DSTRule;
  extern dword                DSTStartUTCsaved, DSTEndUTCsaved;

  void  DST_GetDefaultDSTRule(void);
  dword DST_GetNextTransition(byte ruleOrdinal, byte ruleDay, byte ruleMonth, byte ruleHour, byte ruleMin, word ruleYear);
  void  DST_ProcessRule(char *dstRule, dword *dstDate, dword StartDate);
  void  DST_GetTransitions_Manual(dword *DSTStartUTC, dword *DSTEndUTC);
  void  DST_GetTransitions_Europe(dword *DSTStartUTC, dword *DSTEndUTC, dword StartDate);

  typedef struct TYPE_CRONTAB
  {
    bool            active;             //Is this entry active?
    dword           nextExecution;      //Next execution time
    void           *function;           //Function to call when it's time
    int             frequency;          //Frequency of execution
  } TYPE_CRONTAB;

  #define MAX_CRON_EVENTS     10

  extern int                  cronItemCount;
  extern TYPE_CRONTAB         cronTable[MAX_CRON_EVENTS];
  extern bool                 cronInit;

#endif
