#include "libFireBird.h"

bool PSBuffer_ProcessTSPacket(tPSBuffer *PSBuffer, byte *TSBuffer, ulong64 FileOffset)
{
  TRACEENTER();

  word                  PID;
  byte                  PointerField;
  bool                  AdaptationField;
  byte                  AdaptationFieldLen;
  bool                  CCError;
  bool                  TSError;
  bool                  Crypted;
  bool                  Result;

  //Removed all memset() because they are really slow

  static void CopyPayload(int PayloadOffset, int PayloadLen)
  {
    int                   i;
    ulong64              *pi64;
    ulong64               fo;

    memcpy(PSBuffer->pInBufferData, &TSBuffer[PayloadOffset], PayloadLen);

    fo = FileOffset + PayloadOffset;
    pi64 = &PSBuffer->pInBuffer->FileOffset[PSBuffer->InBufferDataIndex];
    for(i = 0; i < PayloadLen; i++)
    {
      *pi64 = fo;
      pi64++;
      fo++;
    }
    PSBuffer->pInBufferData += PayloadLen;
    PSBuffer->InBufferDataIndex += PayloadLen;
  }

  Result = FALSE;
  //Adaptation field gibt es nur bei PES-Paketen, werden hier aber ignoriert
  //PointerField gibt es nur bei PSI-Paketen

  //Stimmt die PID?
  PID = ((TSBuffer[1] & 0x1f) << 8) | TSBuffer[2];
  AdaptationFieldLen = 0;

  //Nur weitermachen, wenn PID stimmt und Payload vorhanden ist
  if((PID == PSBuffer->PID) && ((TSBuffer[3] & 0x10) != 0))
  {
    if(PSBuffer->InBufferDataIndex >= PSBuffer->BufferSize)
    {
      if((PSBuffer->ErrorFlag & 0x01) == 0)
      {
        TAP_Print("  PS buffer overflow while parsing PID 0x%4.4x", PSBuffer->PID);
        PSBuffer->ErrorFlag = PSBuffer->ErrorFlag | 1;
      }
    }
    else
    {
      //Continuity Counter ok? Falls nicht Buffer komplett verwerfen
      if(PSBuffer->LastContCounter != 255)
        PSBuffer->LastContCounter = (PSBuffer->LastContCounter + 1) & 0x0f;

      TSError = (TSBuffer[1] & 0x80) != 0;
      Crypted = (TSBuffer[3] & 0xc0) != 0;
      CCError = ((TSBuffer[3] & 0x0f) != PSBuffer->LastContCounter) && (PSBuffer->LastContCounter != 255);

      if(!TSError && !Crypted && !CCError)
      {
        if((TSBuffer[3] & 0x20) != 0)
        {
          AdaptationField = TRUE;
          AdaptationFieldLen = TSBuffer[4];
        }
        else
        {
          AdaptationField = FALSE;
        }

        //Startet ein neues Paket?
        if((TSBuffer[1] & 0x40) != 0)
        {
          if(PID <= 0x001f)
            PointerField = TSBuffer[4];
          else
            PointerField = 0;

          if(PSBuffer->InBufferDataIndex != 0)
          {
            //Restliche Bytes umkopieren
            if(PointerField != 0)
              CopyPayload(5, PointerField);

            //Puffer mit den abfragbaren Daten zuweisen
            PSBuffer->pOutBuffer = &PSBuffer->Buffer[PSBuffer->InBufferIndex];
            PSBuffer->pOutBuffer->DataLen = PSBuffer->InBufferDataIndex;
            Result = TRUE;

            PSBuffer->InBufferIndex = 1 - PSBuffer->InBufferIndex;
            PSBuffer->PSFileCtr++;
          }

          //Neuen Puffer aktivieren und initialisieren
          PSBuffer->pInBuffer = &PSBuffer->Buffer[PSBuffer->InBufferIndex];
          PSBuffer->pInBufferData = &PSBuffer->pInBuffer->PSData[0];
          PSBuffer->InBufferDataIndex = 0;
          //memset(PSBuffer->pInBufferData, 0, PSBuffer->BufferSize);

          //Erste Daten kopieren
          if(PID <= 0x001f)
            CopyPayload(5 + PointerField, 183 - PointerField);                  //PSI Data mit PointerField
          else
          {
            if(AdaptationField)
              CopyPayload(5 + AdaptationFieldLen, 183 - AdaptationFieldLen);    //PES-Paket mit zu ignorierendem Adaptation-Field
            else
              CopyPayload(4, 184);                                              //PES-Paket ohne Adaptation-Field
          }
        }
        else
        {
          //Weiterkopieren
          if(PSBuffer->InBufferDataIndex != 0)
          {
            if(AdaptationField)
              CopyPayload(5 + AdaptationFieldLen, 183 - AdaptationFieldLen);    //PES-Paket mit zu ignorierendem Adaptation-Field
            else
              CopyPayload(4, 184);                                              //PES-Paket ohne Adaptation-Field
          }
        }
      }
      else
      {
        if(CCError)
        {
          //WriteLog(Format('  CC error while parsing PID 0x%4.4x, file offset 0x%8.8x', [PSBuffer->PID, FileOffset]), 1);

          PSBuffer->pInBufferData = &PSBuffer->pInBuffer->PSData[0];
          //memset(PSBuffer->pInBufferData, 0, PSBuffer->BufferSize);
          PSBuffer->InBufferDataIndex = 0;
        }

        if(TSError)
        {
          //WriteLog(Format('  TransporStreamError error while parsing PID 0x%4.4x, file offset 0x%8.8x', [PSBuffer->PID, FileOffset]), 1);

          PSBuffer->pInBufferData = &PSBuffer->pInBuffer->PSData[0];
          //memset(PSBuffer->pInBufferData, 0, PSBuffer->BufferSize);
          PSBuffer->InBufferDataIndex = 0;
        }

        if(Crypted)
        {
          //WriteLog(Format('  packet marked as crypted while parsing PID 0x%4.4x, file offset 0x%8.8x', [PSBuffer->PID, FileOffset]), 1);

          PSBuffer->pInBufferData = &PSBuffer->pInBuffer->PSData[0];
          //memset(PSBuffer->pInBufferData, 0, PSBuffer->BufferSize);
          PSBuffer->InBufferDataIndex = 0;
        }
      }
    }

    PSBuffer->LastContCounter = TSBuffer[3] & 0x0f;
  }

  TRACEEXIT();
  return Result;
}
