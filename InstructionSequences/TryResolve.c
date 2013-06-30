#include "../libFireBird.h"

#ifdef _TMSEMU_
  #define dlopen      TAP_Linux_dlopen
  #define dlsym       TAP_Linux_dlsym
  #define dlerror     TAP_Linux_dlerror
  #define dlclose     TAP_Linux_dlclose
#endif

#include            <dlfcn.h>

dword TryResolve(char *Function)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TryResolve");
  #endif

  void                *pvr;
  dword               *ret;

  pvr = dlopen(NULL, RTLD_GLOBAL | RTLD_LAZY);
  if(!pvr)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  ret = dlsym(pvr, Function);
  if(dlerror() != NULL)
  {
    dlclose(pvr);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  dlclose(pvr);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (dword)ret;
}
