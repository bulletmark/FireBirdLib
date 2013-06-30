#include                "FBLib_tmsvfd.h"

void VFD_SetDisplayDigit(byte* DisplayBuffer, byte Character, DISPLAYSTYLE DisplayStyle, byte Digit)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_SetDisplayDigit");
  #endif

  switch(DisplayStyle)
  {
    case VFD_7:
    {
      if(Digit < 4) DisplayBuffer[Digit] = VFD_TranslateSegments(Character, VFD_7);
      break;
    }

    case VFD_14:
    {
      dword s = VFD_TranslateSegments(Character, VFD_14);

      //	7	6	5	4	3	2	1	0
      //01			                1d	1e	1c	1l
      //02	1m	1k	1g1	1g2	1b	1f	1j	1h
      //03	1i	1a	2d	2e	2c	2l	2m	2k       2d<>2l
      //04	2g1	2g2	2b	2f	2j	2h	2i	2a
      //05		3d	3e	3c	3l	3m	3k	3g1
      //06	3g2	3b	3f	3j	3h	3i	3a
      //07			4d	4e	4c	4l	4m	4k
      //08	4g1	4g2	4b	4f	4j	4h	4i	4a

      switch(Digit)
      {
        //Source: m l   k j i h   g2 g1 f e   d c b a
        case 0:
        {
          DisplayBuffer[33] = (DisplayBuffer[33] & 0xf0) |
                              ((s >> 12) & 0x01) |
                              ((s >>  1) & 0x02) |
                              ((s >>  2) & 0x04) |
                              ( s        & 0x08);

          DisplayBuffer[34] = ((s >>  8) & 0x01) |
                              ((s >>  9) & 0x02) |
                              ((s >>  3) & 0x04) |
                              ((s <<  2) & 0x08) |
                              ((s >>  3) & 0x10) |
                              ((s >>  1) & 0x20) |
                              ((s >>  5) & 0x40) |
                              ((s >>  6) & 0x80);

          DisplayBuffer[35] = (DisplayBuffer[35] & 0x3f) |
                              ((s <<  6) & 0x40) |
                              ((s >>  2) & 0x80);

          break;
        }

        case 1:
        {
          DisplayBuffer[35] = (DisplayBuffer[35] & 0xc0) |
                             ((s >> 11) & 0x01) |
                             ((s >> 12) & 0x02) |
                             ((s >> 10) & 0x04) |
                             ((s <<  1) & 0x08) |
                             ( s        & 0x10) |
                             ((s <<  2) & 0x20);

          DisplayBuffer[36] = ( s        & 0x01) |
                              ((s >>  8) & 0x02) |
                              ((s >>  6) & 0x04) |
                              ((s >>  7) & 0x08) |
                              ((s >>  1) & 0x10) |
                              ((s <<  4) & 0x20) |
                              ((s >>  1) & 0x40) |
                              ((s <<  1) & 0x80);

          break;
        }

        case 2:
        {
          DisplayBuffer[37] = (DisplayBuffer[37] & 0x80) |
                             ((s >>  6) & 0x01) |
                             ((s >> 10) & 0x02) |
                             ((s >> 11) & 0x04) |
                             ((s >>  9) & 0x08) |
                             ((s <<  2) & 0x10) |
                             ((s <<  1) & 0x20) |
                             ((s <<  3) & 0x40);

          DisplayBuffer[38] = (DisplayBuffer[6] & 0x01) |
                             ((s <<  1) & 0x02) |
                             ((s >>  7) & 0x04) |
                             ((s >>  5) & 0x08) |
                             ((s >>  6) & 0x10) |
                             ( s        & 0x20) |
                             ((s <<  5) & 0x40) |
                             ( s        & 0x80);

          break;
        }

        case 3:
        {
          DisplayBuffer[39] = (DisplayBuffer[39] & 0xc0) |
                             ((s >> 11) & 0x01) |
                             ((s >> 12) & 0x02) |
                             ((s >> 10) & 0x04) |
                             ((s <<  1) & 0x08) |
                             ( s        & 0x10) |
                             ((s <<  2) & 0x20);

          DisplayBuffer[40] = ( s        & 0x01) |
                              ((s >>  8) & 0x02) |
                              ((s >>  6) & 0x04) |
                              ((s >>  7) & 0x08) |
                              ((s >>  1) & 0x10) |
                              ((s <<  4) & 0x20) |
                              ((s >>  1) & 0x40) |
                              ((s <<  1) & 0x80);

          break;
        }

        default:
          ;


      }

      break;
    }

    case VFD_17:
    {

      dword s = VFD_TranslateSegments(Character, VFD_17);

      //Source: m   l k j i   h g3 g2 g1   f e d2 d1   c b a2 a1
      switch(Digit)
      {
        case 0:
        {
          DisplayBuffer[1] = (DisplayBuffer[1] & 0xd5) |
                              ((s >>  5) & 0x02) |
                              ((s >>  2) & 0x08) |
                              ((s <<  1) & 0x20);

          DisplayBuffer[2] = (DisplayBuffer[2] & 0x55) |
                              ((s >> 13) & 0x02) |
                              ((s >> 13) & 0x08) |
                              ((s >> 10) & 0x20) |
                              ((s <<  4) & 0x80);

          DisplayBuffer[3] = (DisplayBuffer[3] & 0x55) |
                              ((s >>  1) & 0x02) |
                              ((s >>  7) & 0x08) |
                              ((s >>  4) & 0x20) |
                              ((s >>  1) & 0x80);

          DisplayBuffer[4] = (DisplayBuffer[4] & 0x55) |
                              ((s >> 11) & 0x02) |
                              ((s >>  8) & 0x08) |
                              ((s >>  8) & 0x20) |
                              ( s        & 0x80);

          DisplayBuffer[5] = (DisplayBuffer[5] & 0x55) |
                              ((s <<  4) & 0x20) |
                              ((s <<  7) & 0x80);
          break;
        }

        case 1:
        {
          DisplayBuffer[17] = (DisplayBuffer[17] & 0xd5) |
                              ((s >>  5) & 0x02) |
                              ((s >>  2) & 0x08) |
                              ((s <<  1) & 0x20);

          DisplayBuffer[18] = (DisplayBuffer[18] & 0x55) |
                              ((s >> 13) & 0x02) |
                              ((s >> 13) & 0x08) |
                              ((s >> 10) & 0x20) |
                              ((s <<  4) & 0x80);

          DisplayBuffer[19] = (DisplayBuffer[19] & 0x55) |
                              ((s >>  1) & 0x02) |
                              ((s >>  7) & 0x08) |
                              ((s >>  4) & 0x20) |
                              ((s >>  1) & 0x80);

          DisplayBuffer[20] = (DisplayBuffer[20] & 0x55) |
                              ((s >> 11) & 0x02) |
                              ((s >>  8) & 0x08) |
                              ((s >>  8) & 0x20) |
                              ( s        & 0x80);

          DisplayBuffer[21] = (DisplayBuffer[21] & 0x55) |
                              ((s <<  4) & 0x20) |
                              ((s <<  7) & 0x80);
          break;
        }

        case 2:
        {
          DisplayBuffer[17] = (DisplayBuffer[17] & 0xea) |
                              ((s >>  6) & 0x01) |
                              ((s >>  3) & 0x04) |
                              ( s        & 0x10);

          DisplayBuffer[18] = (DisplayBuffer[18] & 0xaa) |
                              ((s >> 14) & 0x01) |
                              ((s >> 14) & 0x04) |
                              ((s >> 11) & 0x10) |
                              ((s <<  3) & 0x40);

          DisplayBuffer[19] = (DisplayBuffer[19] & 0xaa) |
                              ((s >>  2) & 0x01) |
                              ((s >>  8) & 0x04) |
                              ((s >>  5) & 0x10) |
                              ((s >>  2) & 0x40);

          DisplayBuffer[20] = (DisplayBuffer[20] & 0xaa) |
                              ((s >> 12) & 0x01) |
                              ((s >>  9) & 0x04) |
                              ((s >>  9) & 0x10) |
                              ((s >>  1) & 0x40);

          DisplayBuffer[21] = (DisplayBuffer[21] & 0xaf) |
                              ((s <<  3) & 0x10) |
                              ((s <<  6) & 0x40);
          break;
        }

        case 3:
        {
          DisplayBuffer[5] = (DisplayBuffer[5] & 0xf5) |
                            ((s >>  4) & 0x02) |
                            ((s >>  1) & 0x08);

          DisplayBuffer[6] = (DisplayBuffer[6] & 0x55) |
                            ((s >> 15) & 0x02) |
                            ((s >> 12) & 0x08) |
                            ((s <<  2) & 0x20) |
                            ((s <<  1) & 0x80);

          DisplayBuffer[7] = (DisplayBuffer[7] & 0x55) |
                            ((s >>  9) & 0x02) |
                            ((s >>  6) & 0x08) |
                            ((s >>  3) & 0x20) |
                            ((s >>  7) & 0x80);

          DisplayBuffer[8] = (DisplayBuffer[8] & 0x55) |
                            ((s >> 10) & 0x02) |
                            ((s >> 10) & 0x08) |
                            ((s >>  2) & 0x20) |
                            ((s <<  5) & 0x80);

          DisplayBuffer[9] = (DisplayBuffer[9] & 0x57) |
                            ((s <<  2) & 0x08) |
                            ((s <<  5) & 0x20) |
                            ((s >>  5) & 0x80);
          break;
        }

        case 4:
        {
          DisplayBuffer[5] = (DisplayBuffer[5] & 0xfa) |
                            ((s >>  5) & 0x01) |
                            ((s >>  2) & 0x04);

          DisplayBuffer[6] = (DisplayBuffer[6] & 0xaa) |
                            ((s >> 16) & 0x01) |
                            ((s >> 13) & 0x04) |
                            ((s <<  1) & 0x10) |
                            ( s        & 0x40);

          DisplayBuffer[7] = (DisplayBuffer[7] & 0xaa) |
                            ((s >> 10) & 0x01) |
                            ((s >>  7) & 0x04) |
                            ((s >>  4) & 0x10) |
                            ((s >>  8) & 0x40);

          DisplayBuffer[8] = (DisplayBuffer[8] & 0xaa) |
                            ((s >> 11) & 0x01) |
                            ((s >> 11) & 0x04) |
                            ((s >>  3) & 0x10) |
                            ((s <<  4) & 0x40);

          DisplayBuffer[9] = (DisplayBuffer[9] & 0xab) |
                            ((s <<  1) & 0x04) |
                            ((s <<  4) & 0x10) |
                            ((s >>  6) & 0x40);

          break;
        }

        case 5:
        {
          DisplayBuffer[21] = (DisplayBuffer[21] & 0xf5) |
                              ((s >>  4) & 0x02) |
                              ((s >>  1) & 0x08);

          DisplayBuffer[22] = (DisplayBuffer[22] & 0x55) |
                              ((s >> 15) & 0x02) |
                              ((s >> 12) & 0x08) |
                              ((s <<  2) & 0x20) |
                              ((s <<  1) & 0x80);

          DisplayBuffer[23] = (DisplayBuffer[23] & 0x55) |
                              ((s >>  9) & 0x02) |
                              ((s >>  6) & 0x08) |
                              ((s >>  3) & 0x20) |
                              ((s >>  7) & 0x80);

          DisplayBuffer[24] = (DisplayBuffer[24] & 0x55) |
                              ((s >> 10) & 0x02) |
                              ((s >> 10) & 0x08) |
                              ((s >>  2) & 0x20) |
                              ((s <<  5) & 0x80);

          DisplayBuffer[25] = (DisplayBuffer[25] & 0x57) |
                              ((s <<  2) & 0x08) |
                              ((s <<  5) & 0x20) |
                              ((s >>  5) & 0x80);
          break;
        }

        case 6:
        {
          DisplayBuffer[21] = (DisplayBuffer[21] & 0xfa) |
                              ((s >>  5) & 0x01) |
                              ((s >>  2) & 0x04);

          DisplayBuffer[22] = (DisplayBuffer[22] & 0xaa) |
                              ((s >> 16) & 0x01) |
                              ((s >> 13) & 0x04) |
                              ((s <<  1) & 0x10) |
                              ( s        & 0x40);

          DisplayBuffer[23] = (DisplayBuffer[23] & 0xaa) |
                              ((s >> 10) & 0x01) |
                              ((s >>  7) & 0x04) |
                              ((s >>  4) & 0x10) |
                              ((s >>  8) & 0x40);

          DisplayBuffer[24] = (DisplayBuffer[24] & 0xaa) |
                              ((s >> 11) & 0x01) |
                              ((s >> 11) & 0x04) |
                              ((s >>  3) & 0x10) |
                              ((s <<  4) & 0x40);

          DisplayBuffer[25] = (DisplayBuffer[25] & 0xab) |
                              ((s <<  1) & 0x04) |
                              ((s <<  4) & 0x10) |
                              ((s >>  6) & 0x40);
          break;
        }

        case 7:
        {
          DisplayBuffer[1] = (DisplayBuffer[1] & 0xea) |
                            ((s >>  6) & 0x01) |
                            ((s >>  3) & 0x04) |
                            ( s        & 0x10);

          DisplayBuffer[2] = (DisplayBuffer[2] & 0xaa) |
                            ((s >> 14) & 0x01) |
                            ((s >> 14) & 0x04) |
                            ((s >> 11) & 0x10) |
                            ((s <<  3) & 0x40);

          DisplayBuffer[3] = (DisplayBuffer[3] & 0xaa) |
                            ((s >>  2) & 0x01) |
                            ((s >>  8) & 0x04) |
                            ((s >>  5) & 0x10) |
                            ((s >>  2) & 0x40);

          DisplayBuffer[4] = (DisplayBuffer[4] & 0xaa) |
                            ((s >> 12) & 0x01) |
                            ((s >>  9) & 0x04) |
                            ((s >>  9) & 0x10) |
                            ((s >>  1) & 0x40);

          DisplayBuffer[5] = (DisplayBuffer[5] & 0xaf) |
                            ((s <<  3) & 0x10) |
                            ((s <<  6) & 0x40);

          break;
        }
      }

      break;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
