#include                "FBLib_EPG.h"

dword EPGInfo_CountEvents(dword *TreePointer)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_CountEvents");
  #endif

  dword                 i;
  tTreeEntry           *ListStart, *Entry;

  i = 0;

  if(TreePointer)
  {
    ListStart = (tTreeEntry*)*TreePointer;

    //If the list points to itself, no data is available
    if(ListStart == (tTreeEntry*)ListStart->Next)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }

    //Loop until we're back at the beginning of the pool
    Entry = ListStart;
    do
    {
      i++;
      Entry = (tTreeEntry*)Entry->Next;
    } while(Entry && (Entry->Next != ListStart->Prev));
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return i;
}
