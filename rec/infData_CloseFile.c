#include <stdio.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

void infData_CloseFile(void)
{
  TRACEENTER();

  if(infDatainfFile)
  {
    fclose(infDatainfFile);
    infDatainfFile = NULL;
  }

  TRACEEXIT();
}
