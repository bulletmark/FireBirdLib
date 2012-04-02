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
  void                *pvr;
  dword               *ret;

  pvr = dlopen(NULL, RTLD_GLOBAL | RTLD_LAZY);
  if(!pvr) return 0;

  ret = dlsym(pvr, Function);
  if (dlerror() != NULL)
  {
    dlclose(pvr);
    return 0;
  }

  dlclose(pvr);
  return (dword)ret;
}
