#include                <stdio.h>
#include                <locale.h>
#include                "../libFireBird.h"

dword GetUptime(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetUptime");
  #endif

  dword                 uptime = 0;
  FILE                 *fp;
  double                upsecs;

  fp = fopen("/proc/uptime", "r");
  if(fp != NULL)
  {
    char                buf[BUFSIZ];
    int                 res;
    char               *b;

    b = fgets(buf, BUFSIZ, fp);
    if(b == buf)
    {
      /* The following sscanf must use the C locale.  */
      setlocale(LC_NUMERIC, "C");
      res = sscanf(buf, "%lf", &upsecs);
      setlocale(LC_NUMERIC, "");
      if(res == 1) uptime = (dword)(upsecs * 100);
    }
    fclose(fp);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return uptime;
}
