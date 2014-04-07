#include "../libFireBird.h"

#include            <dlfcn.h>

dword TryResolve(char *Function)
{
  TRACEENTER();

  void                *pvr;
  dword               *ret;

  pvr = dlopen(NULL, RTLD_GLOBAL | RTLD_LAZY);
  if(!pvr)
  {
    TRACEEXIT();
    return 0;
  }

  ret = dlsym(pvr, Function);
  if(dlerror() != NULL)
  {
    dlclose(pvr);

    TRACEEXIT();
    return 0;
  }

  dlclose(pvr);

  TRACEEXIT();
  return (dword)ret;
}
