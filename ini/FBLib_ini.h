#ifndef FBLIB_INI_H
#define FBLIB_INI_H

#ifdef _TMSEMU_
  #include "tap_tmsemu.h"
#else
  #include "tap.h"
#endif

extern dword            LangNrStrings;
extern dword            *LangStringPtr;
extern char             *LangStrings;
extern char *INIBuffer, *INICommentBuffer;

extern dword BufferSize;

char *stricstr(char *, char *);
void INIFindStartEnd(char *, char **, char **, dword);

#endif
