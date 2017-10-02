#include <stdlib.h>
#include <string.h>
#include "../libFireBird.h"

#undef malloc

bool PSBuffer_Init(tPSBuffer *PSBuffer, word PID, int BufferSize)
{
  TRACEENTER();

  if(!PSBuffer)
  {
    TRACEEXIT();
    return FALSE;
  }

  memset(PSBuffer, 0, sizeof(tPSBuffer));

  PSBuffer->PID = PID;
  PSBuffer->BufferSize = BufferSize;

  PSBuffer->Buffer[0].PSData = malloc(BufferSize * sizeof(byte));
  PSBuffer->Buffer[0].FileOffset = malloc(BufferSize * sizeof(ulong64));

  PSBuffer->Buffer[1].PSData = malloc(BufferSize * sizeof(byte));
  PSBuffer->Buffer[1].FileOffset = malloc(BufferSize * sizeof(ulong64));

  PSBuffer->LastContCounter = 255;

  PSBuffer->pInBuffer = &PSBuffer->Buffer[0];
  PSBuffer->pInBufferData = &PSBuffer->pInBuffer->PSData[0];

  TRACEEXIT();

  //Make sure all buffers have an valid pointer
  return(PSBuffer->Buffer[0].PSData && PSBuffer->Buffer[0].FileOffset && PSBuffer->Buffer[1].PSData && PSBuffer->Buffer[1].FileOffset);
}
