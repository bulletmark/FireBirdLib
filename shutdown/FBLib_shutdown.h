#ifndef FBLIB_SHUTDOWN_H
#define FBLIB_SHUTDOWN_H

#include "tap.h"

#define HDDIDLE         0xe1

extern bool LibInitialized;

void CreateRootDir(void);
void WriteLog(char *);
void Hooked_ApplEvent_CallHandler(unsigned int, unsigned int);
bool SetHandler(dword, void *, void **);

#endif
