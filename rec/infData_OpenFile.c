#include <string.h>
#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

FILE                   *infDatainfFile = NULL;

bool infData_OpenFile(char *infFileName)
{
  TRACEENTER();

  char                  AbsFileName[FBLIB_DIR_SIZE];

  infDatainfFile = NULL;
  if(infFileName && *infFileName)
  {
    ConvertPathType(infFileName, AbsFileName, PF_FullLinuxPath);
    if(*AbsFileName) infDatainfFile = fopen(AbsFileName, "r+");
  }

  TRACEEXIT();
  return (infDatainfFile != NULL);
}
