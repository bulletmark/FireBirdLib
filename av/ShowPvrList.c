#include "libFireBird.h"

bool ShowPvrList(tPvrListType PvrListType)
{
  TRACEENTER;

  void (*__Appl_PvrList)(unsigned int, unsigned int);
  void (*__Appl_PvrList_SetListType)(tPvrListType ListType);

  if(PvrListType != PLT_Unchanged)
  {
    //Initialize the _listview variable if necessary
    dword *d;

    d = (dword*)TryResolve("_listView");
    if(d && (*d == 0)) *d = TryResolve("_fileListView");

    //Setup the next file list
    __Appl_PvrList_SetListType = (void*)FIS_fwAppl_PvrList_SetListType();

    if(!__Appl_PvrList_SetListType)
    {
      TRACEEXIT;
      return FALSE;
    }
    __Appl_PvrList_SetListType(PvrListType - 1);
  }

  __Appl_PvrList = (void*)FIS_fwAppl_PvrList();
  if(!__Appl_PvrList)
  {
    TRACEEXIT;
    return FALSE;
  }

  __Appl_PvrList(0, 0xffff);


  TRACEEXIT;
  return TRUE;
}
