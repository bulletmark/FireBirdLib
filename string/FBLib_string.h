#ifndef FBLIB_STRING_H
#define FBLIB_STRING_H

#include "libFireBird.h"

//see StrToUTF8
extern char             AnsiUpper[30];
extern char             AnsiLower[30];
extern char             UTF8Upper[64];
extern char             UTF8Lower[64];

bool isLegalChar(byte*, eRemoveChars);
char *stricstr(char *, char *);

#endif
