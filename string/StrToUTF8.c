#include                <string.h>
#include                "libFireBird.h"

//Translates DVB character set table 00 (chars 0xa0 to 0xff) to Unicode
word UTFLookupISO6937[] =  {0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x20AC, 0x00A5, 0x0000, 0x00A7, 0x00A4, 0x2018, 0x201c, 0x00AB, 0x2190, 0x2191, 0x2192, 0x2193,
                            0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00D7, 0x00B5, 0x00B6, 0x00B7, 0x00F7, 0x2019, 0x201D, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
                            0x0000, 0x0300, 0x0301, 0x0302, 0x0303, 0x0304, 0x0306, 0x0307, 0x0308, 0x0000, 0x030A, 0x0327, 0x0000, 0x030b, 0x0328, 0x030c,
                            0x2015, 0x00b9, 0x00ae, 0x00a9, 0x2122, 0x266a, 0x00ac, 0x00a6, 0x0000, 0x0000, 0x0000, 0x0000, 0x215b, 0x215c, 0x215d, 0x215e,
                            0x2126, 0x00c6, 0x0110, 0x00aa, 0x0126, 0x0000, 0x0132, 0x013f, 0x0141, 0x00d8, 0x0152, 0x00ba, 0x00de, 0x0166, 0x014a, 0x0149,
                            0x0138, 0x00e6, 0x0111, 0x03b4, 0x0127, 0x0131, 0x0133, 0x0140, 0x0142, 0x00f8, 0x0153, 0x00df, 0x00fe, 0x0167, 0x014b, 0x00ad};

//ISO8859-1
word UTFLookupISO8859_1[] =  {0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
                              0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
                              0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF};

//ISO8859-2
word UTFLookupISO8859_2[] =  {0x00A0, 0x0104, 0x02D8, 0x0141, 0x00A4, 0x013D, 0x015A, 0x00A7, 0x00A8, 0x0160, 0x015E, 0x0164, 0x0179, 0x00AD, 0x017D, 0x017B,
                              0x00B0, 0x0105, 0x02DB, 0x0142, 0x00B4, 0x013E, 0x015B, 0x02C7, 0x00B8, 0x0161, 0x015F, 0x0165, 0x017A, 0x02DD, 0x017E, 0x017C,
                              0x0154, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E,
                              0x0110, 0x0143, 0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7, 0x0158, 0x016E, 0x00DA, 0x0170, 0x00DC, 0x00DD, 0x0162, 0x00DF,
                              0x0155, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A, 0x0107, 0x00E7, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
                              0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7, 0x0159, 0x016F, 0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9};

//ISO8859-3
word UTFLookupISO8859_3[] =  {0x00A0, 0x0126, 0x02D8, 0x00A3, 0x00A4, 0x0000, 0x0124, 0x00A7, 0x00A8, 0x0130, 0x015E, 0x011E, 0x0134, 0x00AD, 0x0000, 0x017B,
                              0x00B0, 0x0127, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x0125, 0x00B7, 0x00B8, 0x0131, 0x015F, 0x011F, 0x0135, 0x00BD, 0x0000, 0x017C,
                              0x00C0, 0x00C1, 0x00C2, 0x0000, 0x00C4, 0x010A, 0x0108, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x0000, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x0120, 0x00D6, 0x00D7, 0x011C, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x016C, 0x015C, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x0000, 0x00E4, 0x010B, 0x0109, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x0000, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x0121, 0x00F6, 0x00F7, 0x011D, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x016D, 0x015D, 0x02D9};

//ISO8859-4
word UTFLookupISO8859_4[] =  {0x00A0, 0x0104, 0x0138, 0x0156, 0x00A4, 0x0128, 0x013B, 0x00A7, 0x00A8, 0x0160, 0x0112, 0x0122, 0x0166, 0x00AD, 0x017D, 0x00AF,
                              0x00B0, 0x0105, 0x02DB, 0x0157, 0x00B4, 0x0129, 0x013C, 0x02C7, 0x00B8, 0x0161, 0x0113, 0x0123, 0x0167, 0x014A, 0x017E, 0x014B,
                              0x0100, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x012A,
                              0x0110, 0x0145, 0x014C, 0x0136, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x0172, 0x00DA, 0x00DB, 0x00DC, 0x0168, 0x016A, 0x00DF,
                              0x0101, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x012F, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x012B,
                              0x0111, 0x0146, 0x014D, 0x0137, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x0173, 0x00FA, 0x00FB, 0x00FC, 0x0169, 0x016B, 0x02D9};

//ISO8859-5
word UTFLookupISO8859_5[] =  {0x00A0, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x00AD, 0x040E, 0x040F,
                              0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
                              0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F,
                              0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F,
                              0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F,
                              0x2116, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x00A7, 0x045E, 0x045F};

//ISO8859-6
word UTFLookupISO8859_6[] =  {0x00A0, 0x0000, 0x0000, 0x0000, 0x00A4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x060C, 0x00AD, 0x0000, 0x0000,
                              0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x061B, 0x0000, 0x0000, 0x0000, 0x061F,
                              0x0000, 0x0621, 0x0622, 0x0623, 0x0624, 0x0625, 0x0626, 0x0627, 0x0628, 0x0629, 0x062A, 0x062B, 0x062C, 0x062D, 0x062E, 0x062F,
                              0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637, 0x0638, 0x0639, 0x063A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                              0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646, 0x0647, 0x0648, 0x0649, 0x064A, 0x064B, 0x064C, 0x064D, 0x064E, 0x064F,
                              0x0650, 0x0651, 0x0652, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

//ISO8859-7
word UTFLookupISO8859_7[] = {0x00A0, 0x2018, 0x2019, 0x00A3, 0x0000, 0x0000, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x0000, 0x00AB, 0x00AC, 0x00AD, 0x0000, 0x2015,
                             0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x0384, 0x0385, 0x0386, 0x00B7, 0x0388, 0x0389, 0x038A, 0x00BB, 0x038C, 0x00BD, 0x038E, 0x038F,
                             0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F,
                             0x03A0, 0x03A1, 0x0000, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x03AC, 0x03AD, 0x03AE, 0x03AF,
                             0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF,
                             0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0x0000};

//ISO8859-8
word UTFLookupISO8859_8[] = {0x00A0, 0x0000, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00D7, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
                             0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00F7, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x0000,
                             0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                             0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2017,
                             0x05D0, 0x05D1, 0x05D2, 0x05D3, 0x05D4, 0x05D5, 0x05D6, 0x05D7, 0x05D8, 0x05D9, 0x05DA, 0x05DB, 0x05DC, 0x05DD, 0x05DE, 0x05DF,
                             0x05E0, 0x05E1, 0x05E2, 0x05E3, 0x05E4, 0x05E5, 0x05E6, 0x05E7, 0x05E8, 0x05E9, 0x05EA, 0x0000, 0x0000, 0x200E, 0x200F, 0x0000};

//ISO8859-9
word UTFLookupISO8859_9[] =  {0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
                              0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
                              0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x011E, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x0130, 0x015E, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x011F, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x0131, 0x015F, 0x00FF};

//ISO8859-10
word UTFLookupISO8859_10[] = {0x00A0, 0x0104, 0x0112, 0x0122, 0x012A, 0x0128, 0x0136, 0x00A7, 0x013B, 0x0110, 0x0160, 0x0166, 0x017D, 0x00AD, 0x016A, 0x014A,
                              0x00B0, 0x0105, 0x0113, 0x0123, 0x012B, 0x0129, 0x0137, 0x00B7, 0x013C, 0x0111, 0x0161, 0x0167, 0x017E, 0x2015, 0x016B, 0x014B,
                              0x0100, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x00CF,
                              0x00D0, 0x0145, 0x014C, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x0168, 0x00D8, 0x0172, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
                              0x0101, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x012F, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x00EF,
                              0x00F0, 0x0146, 0x014D, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x0169, 0x00F8, 0x0173, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x0138};

//ISO8859-11
word UTFLookupISO8859_11[] = {0x00A0, 0x0E01, 0x0E02, 0x0E03, 0x0E04, 0x0E05, 0x0E06, 0x0E07, 0x0E08, 0x0E09, 0x0E0A, 0x0E0B, 0x0E0C, 0x0E0D, 0x0E0E, 0x0E0F,
                              0x0E10, 0x0E11, 0x0E12, 0x0E13, 0x0E14, 0x0E15, 0x0E16, 0x0E17, 0x0E18, 0x0E19, 0x0E1A, 0x0E1B, 0x0E1C, 0x0E1D, 0x0E1E, 0x0E1F,
                              0x0E20, 0x0E21, 0x0E22, 0x0E23, 0x0E24, 0x0E25, 0x0E26, 0x0E27, 0x0E28, 0x0E29, 0x0E2A, 0x0E2B, 0x0E2C, 0x0E2D, 0x0E2E, 0x0E2F,
                              0x0E30, 0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37, 0x0E38, 0x0E39, 0x0E3A, 0x0000, 0x0000, 0x0000, 0x0000, 0x0E3F,
                              0x0E40, 0x0E41, 0x0E42, 0x0E43, 0x0E44, 0x0E45, 0x0E46, 0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D, 0x0E4E, 0x0E4F,
                              0x0E50, 0x0E51, 0x0E52, 0x0E53, 0x0E54, 0x0E55, 0x0E56, 0x0E57, 0x0E58, 0x0E59, 0x0E5A, 0x0E5B, 0x0000, 0x0000, 0x0000, 0x0000};

//ISO8859-13
word UTFLookupISO8859_13[] = {0x00A0, 0x201D, 0x00A2, 0x00A3, 0x00A4, 0x201E, 0x00A6, 0x00A7, 0x00D8, 0x00A9, 0x0156, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00C6,
                              0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x201C, 0x00B5, 0x00B6, 0x00B7, 0x00F8, 0x00B9, 0x0157, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00E6,
                              0x0104, 0x012E, 0x0100, 0x0106, 0x00C4, 0x00C5, 0x0118, 0x0112, 0x010C, 0x00C9, 0x0179, 0x0116, 0x0122, 0x0136, 0x012A, 0x013B,
                              0x0160, 0x0143, 0x0145, 0x00D3, 0x014C, 0x00D5, 0x00D6, 0x00D7, 0x0172, 0x0141, 0x015A, 0x016A, 0x00DC, 0x017B, 0x017D, 0x00DF,
                              0x0105, 0x012F, 0x0101, 0x0107, 0x00E4, 0x00E5, 0x0119, 0x0113, 0x010D, 0x00E9, 0x017A, 0x0117, 0x0123, 0x0137, 0x012B, 0x013C,
                              0x0161, 0x0144, 0x0146, 0x00F3, 0x014D, 0x00F5, 0x00F6, 0x00F7, 0x0173, 0x0142, 0x015B, 0x016B, 0x00FC, 0x017C, 0x017E, 0x2019};

//ISO8859-14
word UTFLookupISO8859_14[] = {0x00A0, 0x1E02, 0x1E03, 0x00A3, 0x010A, 0x010B, 0x1E0A, 0x00A7, 0x1E80, 0x00A9, 0x1E82, 0x1E0B, 0x1EF2, 0x00AD, 0x00AE, 0x0178,
                              0x1E1E, 0x1E1F, 0x0120, 0x0121, 0x1E40, 0x1E41, 0x00B6, 0x1E56, 0x1E81, 0x1E57, 0x1E83, 0x1E60, 0x1EF3, 0x1E84, 0x1E85, 0x1E61,
                              0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x0174, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x1E6A, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x0176, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x0175, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x1E6B, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x0177, 0x00FF};

//ISO8859-15
word UTFLookupISO8859_15[] = {0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x20AC, 0x00A5, 0x0160, 0x00A7, 0x0161, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
                              0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x017D, 0x00B5, 0x00B6, 0x00B7, 0x017E, 0x00B9, 0x00BA, 0x00BB, 0x0152, 0x0153, 0x0178, 0x00BF,
                              0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF};

//ISO8859-16
word UTFLookupISO8859_16[] = {0x00A0, 0x0104, 0x0105, 0x0141, 0x20AC, 0x201E, 0x0160, 0x00A7, 0x0161, 0x00A9, 0x0218, 0x00AB, 0x0179, 0x00AD, 0x017A, 0x017B,
                              0x00B0, 0x00B1, 0x010C, 0x0142, 0x017D, 0x201D, 0x00B6, 0x00B7, 0x017E, 0x010D, 0x0219, 0x00BB, 0x0152, 0x0153, 0x0178, 0x017C,
                              0x00C0, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0106, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
                              0x0110, 0x0143, 0x00D2, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x015A, 0x0170, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x0118, 0x021A, 0x00DF,
                              0x00E0, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x0107, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
                              0x0111, 0x0144, 0x00F2, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x015B, 0x0171, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x0119, 0x021B, 0x00FF};

char                    AnsiUpper[30] = "�����������������������������";
char                    AnsiLower[30] = "�����������������������������";

char                    UTF8Upper[64] = "\u00c0\u00c1\u00c2\u00c3\u00c4\u00c5\u00c6\u00c7\u00c8\u00c9\u00ca\u00cb\u00cc\u00cd\u00ce\u00cf\u00d0\u00d1\u00d2\u00d3\u00d4\u00d5\u00d6\u00d8\u00d9\u00da\u00db\u00dc\u00dd\u00de";
char                    UTF8Lower[64] = "\u00e0\u00e1\u00e2\u00e3\u00e4\u00e5\u00e6\u00e7\u00e8\u00e9\u00ea\u00eb\u00ec\u00ed\u00ee\u00ef\u00f0\u00f1\u00f2\u00f3\u00f4\u00f5\u00f6\u00f8\u00f9\u00fa\u00fb\u00fc\u00fd\u00fe";

typedef struct
{
  word                  Big5DBCS;
  word                  UTF16;
}tBig5Translation;

#include "Big5Data.h"

bool StrToUTF8(const byte *SourceString, byte *DestString, byte DefaultISO8859CharSet)
{
  TRACEENTER();

  bool                  ret;
  byte                  BytesPerCharacter;
  dword                 UTF32;
  word                 *UTFLookup;
  byte                  CharSet, SourceChar;

  if(!SourceString || !DestString)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!SourceString[0])
  {
    DestString[0] = '\0';

    TRACEEXIT();
    return TRUE;
  }

  ret = FALSE;

  //Is there any encoding marker at the beginning of the text?
  CharSet = DefaultISO8859CharSet;

  if(SourceString[0] < ' ')
  {
    switch(SourceString[0])
    {
      case 0x01: CharSet = 5; break;
      case 0x02: CharSet = 6; break;
      case 0x03: CharSet = 7; break;
      case 0x04: CharSet = 8; break;
      case 0x05: CharSet = 9; break;
      case 0x06: CharSet = 10; break;
      case 0x07: CharSet = 11; break;
      case 0x08: CharSet = 12; break;
      case 0x09: CharSet = 13; break;
      case 0x0a: CharSet = 14; break;
      case 0x0b: CharSet = 15; break;
      case 0x10:
      {
        //3 char �bersetzung
        CharSet = SourceString[2];
        SourceString += 2;
        break;
      }

      case 0x14:
      {
        //Big5 Traditional Chinese
        //Caller needs to make sure that the source string is terminated by 2 NULL chars
        word           *pDBCS, w;
        byte            hb, lb;
        bool            hbok, lbok;

        pDBCS = (word*)&SourceString[1];
        while(*pDBCS != 0)
        {
          w = (*pDBCS >> 8) | (*pDBCS << 8);

          //is the char inside of the allowed Big5 range?
          hb = w >> 8;
          lb = w & 0xff;
          hbok = ((hb >= 0xA1) && (hb <= 0xC7)) || ((hb >= 0xC9) && (hb <= 0xF9));
          lbok = ((lb >= 0x40) && (lb <= 0x7E)) || ((lb >= 0xA1) && (lb <= 0xFE));

          if(hbok && lbok)
          {
            tBig5Translation  *p;
            bool                Found;

            //Passed Big5 range check. Look up for Big5 and convert to Unicode
            p = Big5Translation;

            Found = FALSE;
            while(p->Big5DBCS != 0)
            {
              if(w == p->Big5DBCS)
              {
                Found = TRUE;
                break;
              }
              p++;
            }

            if(Found)
            {
              //Found the associated Unicode character. Convert to UTF-8 and copy
              UTF32ToUTF8((dword)p->UTF16, DestString, &BytesPerCharacter);
              DestString += BytesPerCharacter;
            }
            else
            {
              //There's no associated Unicode character. Use an *
              *DestString = '*';
              DestString++;
            }
          }
          else
          {
            //out of Big5 range. Just copy the word and convert to UTF-8
            UTF32ToUTF8((dword)w, DestString, &BytesPerCharacter);
            DestString += BytesPerCharacter;
          }

          pDBCS++;
        }


        TRACEEXIT();
        return TRUE;
      }

      case 0x15:
      {
        //According to EN300468, this is already in UTF8 encoding
        strcpy(DestString, &SourceString[1]);

        TRACEEXIT();
        return TRUE;
      }

      case 0x1f:
      {
        SourceString++;
        break;
      }
    }
    SourceString++;
  }
  else
  {
    //LogEntryFBLibPrintf(TRUE, "StrToUTF8: using default lookup table 8859-%d", CharSet);
  }

  switch(CharSet)
  {
    case 1: UTFLookup = UTFLookupISO8859_1; break;
    case 2: UTFLookup = UTFLookupISO8859_2; break;
    case 3: UTFLookup = UTFLookupISO8859_3; break;
    case 4: UTFLookup = UTFLookupISO8859_4; break;
    case 5: UTFLookup = UTFLookupISO8859_5; break;
    case 6: UTFLookup = UTFLookupISO8859_6; break;
    case 7: UTFLookup = UTFLookupISO8859_7; break;
    case 8: UTFLookup = UTFLookupISO8859_8; break;
    case 9: UTFLookup = UTFLookupISO8859_9; break;
    case 10: UTFLookup = UTFLookupISO8859_10; break;
    case 11: UTFLookup = UTFLookupISO8859_11; break;
    case 13: UTFLookup = UTFLookupISO8859_13; break;
    case 14: UTFLookup = UTFLookupISO8859_14; break;
    case 15: UTFLookup = UTFLookupISO8859_15; break;
    case 16: UTFLookup = UTFLookupISO8859_16; break;

    default: UTFLookup = UTFLookupISO6937; break;
  }

  while(*SourceString)
  {
    if(*SourceString < 0x80)
    {
      //ASCII: just copy
      *DestString = *SourceString;
      SourceString++;
      DestString++;
    }
    else
    {
      if(isUTF8Char(SourceString, &BytesPerCharacter))
      {
        //Already UTF8: just copy
        memcpy(DestString, (void *) SourceString, BytesPerCharacter);
        SourceString += BytesPerCharacter;
        DestString += BytesPerCharacter;
      }
      else
      {
        //Seems to be an ANSI character: conversion is needed
        if((CharSet == 0) && (*SourceString >= 0xc0)  && (*SourceString <= 0xcf))
        {
          //if ISO6937 is used, replace diactricital characters with their single entity counterparts

                        //         �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �        �
          char         *ISO6937 = "\xc1\x41 \xc2\x41 \xc3\x41 \xc4\x41 \xc8\x41 \xca\x41 \xcb\x43 \xc1\x45 \xc2\x45 \xc3\x45 \xc8\x45 \xc1\x49 \xc2\x49 \xc3\x49 \xc8\x49 \xc4\x4e \xc1\x4f \xc2\x4f \xc3\x4f \xc4\x4f \xc8\x4f \xc1\x55 \xc2\x55 \xc3\x55 \xc8\x55 \xc2\x59 \xc1\x61 \xc2\x61 \xc3\x61 \xc4\x61 \xc8\x61 \xca\x61 \xcb\x63 \xc1\x65 \xc2\x65 \xc3\x65 \xc8\x65 \xc1\x69 \xc2\x69 \xc3\x69 \xc8\x69 \xc4\x6e \xc1\x6f \xc2\x6f \xc3\x6f \xc4\x6f \xc8\x6f \xc1\x75 \xc2\x75 \xc3\x75 \xc8\x75 \xc2\x79 \xc8\x79";
          char         *UTF8    = "\xc3\x80 \xc3\x81 \xc3\x82 \xc3\x83 \xc3\x84 \xc3\x85 \xc3\x87 \xc3\x88 \xc3\x89 \xc3\x8a \xc3\x8b \xc3\x8c \xc3\x8d \xc3\x8e \xc3\x8f \xc3\x91 \xc3\x92 \xc3\x93 \xc3\x94 \xc3\x95 \xc3\x96 \xc3\x99 \xc3\x9a \xc3\x9b \xc3\x9c \xc3\x9d \xc3\xa0 \xc3\xa1 \xc3\xa2 \xc3\xa3 \xc3\xa4 \xc3\xa5 \xc3\xa7 \xc3\xa8 \xc3\xa9 \xc3\xaa \xc3\xab \xc3\xac \xc3\xad \xc3\xae \xc3\xaf \xc3\xb1 \xc3\xb2 \xc3\xb3 \xc3\xb4 \xc3\xb5 \xc3\xb6 \xc3\xb9 \xc3\xba \xc3\xbb \xc3\xbc \xc3\xbd \xc3\xbf";

          char          Dia[3], *p;
          int           Index;

          memcpy(Dia, (void *) SourceString, 2);
          Dia[2] = '\0';
          p = strstr(ISO6937, Dia);
          if(p)
          {
            Index = (dword)p - (dword)ISO6937;
            memcpy(DestString, &UTF8[Index], 2);
            DestString += 2;
          }
          else
          {
            LogEntryFBLibPrintf(TRUE, "StrToUTF8: ISO6937 diacritical char %2.2x %2.2x has been ignored", SourceString[0], SourceString[1]);
          }
          SourceString++;
        }
        else
        {
          SourceChar = * SourceString;
          if(SourceChar >= 0xa0)
            UTF32 = UTFLookup[SourceChar - 0xa0];
          else
            UTF32 = SourceChar;

          UTF32ToUTF8(UTF32, DestString, &BytesPerCharacter);
          DestString += BytesPerCharacter;
        }

        ret = TRUE;
        SourceString++;
      }
    }
  }
  *DestString = '\0';

  TRACEEXIT();
  return ret;
}
