program UCFontList;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils,
  Windows;

type
  tFontDefUC = packed record
    Unicode             : dword;
    FileOffset          : dword;
    Width               : word;
    Height              : word;
  end;

  tUnicodeTable = record
    UnicodeStart        : dword;
    UnicodeEnd          : dword;
    TableName           : String;
  end;

const
  UNICODETABELSIZE      = 261;
  UnicodeTable          : array[0..UNICODETABELSIZE - 1] of tUnicodeTable =
                          ((UnicodeStart: $000000; UnicodeEnd: $00007F; TableName: 'C0 Controls & Basic Latin'),
                           (UnicodeStart: $000080; UnicodeEnd: $0000FF; TableName: 'C1 Controls & Latin-1 Supplement'),
                           (UnicodeStart: $000100; UnicodeEnd: $00017F; TableName: 'Latin Extended-A'),
                           (UnicodeStart: $000180; UnicodeEnd: $00024F; TableName: 'Latin Extended-B'),
                           (UnicodeStart: $000250; UnicodeEnd: $0002AF; TableName: 'IPA Extensions'),
                           (UnicodeStart: $0002B0; UnicodeEnd: $0002FF; TableName: 'Spacing Modifier Letters'),
                           (UnicodeStart: $000300; UnicodeEnd: $00036F; TableName: 'Combining Diacritical Marks'),
                           (UnicodeStart: $000370; UnicodeEnd: $0003FF; TableName: 'Greek & Coptic'),
                           (UnicodeStart: $000400; UnicodeEnd: $0004FF; TableName: 'Cyrillic'),
                           (UnicodeStart: $000500; UnicodeEnd: $00052F; TableName: 'Cyrillic Supplement'),
                           (UnicodeStart: $000530; UnicodeEnd: $00058F; TableName: 'Armenian'),
                           (UnicodeStart: $000590; UnicodeEnd: $0005FF; TableName: 'Hebrew'),
                           (UnicodeStart: $000600; UnicodeEnd: $0006FF; TableName: 'Arabic'),
                           (UnicodeStart: $000700; UnicodeEnd: $00074F; TableName: 'Syriac'),
                           (UnicodeStart: $000750; UnicodeEnd: $00077F; TableName: 'Arabic Supplement'),
                           (UnicodeStart: $000780; UnicodeEnd: $0007BF; TableName: 'Thaana'),
                           (UnicodeStart: $0007C0; UnicodeEnd: $0007FF; TableName: 'NKo'),
                           (UnicodeStart: $000830; UnicodeEnd: $00083F; TableName: 'Samaritan'),
                           (UnicodeStart: $000840; UnicodeEnd: $00085F; TableName: 'Mandaic'),
                           (UnicodeStart: $0008A0; UnicodeEnd: $0008FF; TableName: 'Arabic Extended-A'),
                           (UnicodeStart: $000900; UnicodeEnd: $00097F; TableName: 'Devanagari'),
                           (UnicodeStart: $000980; UnicodeEnd: $0009FF; TableName: 'Bengali'),
                           (UnicodeStart: $000A00; UnicodeEnd: $000A7F; TableName: 'Gurmukhi'),
                           (UnicodeStart: $000A80; UnicodeEnd: $000AFF; TableName: 'Gujarati'),
                           (UnicodeStart: $000B00; UnicodeEnd: $000B7F; TableName: 'Oriya'),
                           (UnicodeStart: $000B80; UnicodeEnd: $000BFF; TableName: 'Tamil'),
                           (UnicodeStart: $000C00; UnicodeEnd: $000C7F; TableName: 'Telugu'),
                           (UnicodeStart: $000C80; UnicodeEnd: $000CFF; TableName: 'Kannada'),
                           (UnicodeStart: $000D00; UnicodeEnd: $000D7F; TableName: 'Malayalam'),
                           (UnicodeStart: $000D80; UnicodeEnd: $000DFF; TableName: 'Sinhala'),
                           (UnicodeStart: $000E00; UnicodeEnd: $000E7F; TableName: 'Thai'),
                           (UnicodeStart: $000E80; UnicodeEnd: $000EFF; TableName: 'Lao'),
                           (UnicodeStart: $000F00; UnicodeEnd: $000FFF; TableName: 'Tibetan'),
                           (UnicodeStart: $001000; UnicodeEnd: $00109F; TableName: 'Myanmar'),
                           (UnicodeStart: $0010A0; UnicodeEnd: $0010FF; TableName: 'Georgian'),
                           (UnicodeStart: $001100; UnicodeEnd: $0011FF; TableName: 'Hangul Jamo'),
                           (UnicodeStart: $001200; UnicodeEnd: $00137F; TableName: 'Ethiopic'),
                           (UnicodeStart: $001380; UnicodeEnd: $00139F; TableName: 'Ethiopic Supplement'),
                           (UnicodeStart: $0013A0; UnicodeEnd: $0013FF; TableName: 'Cherokee'),
                           (UnicodeStart: $001400; UnicodeEnd: $00167F; TableName: 'Unified Canadian Aboriginal Syllabic'),
                           (UnicodeStart: $001680; UnicodeEnd: $00189F; TableName: 'Ogham'),
                           (UnicodeStart: $0016A0; UnicodeEnd: $0016FF; TableName: 'Runic'),
                           (UnicodeStart: $001700; UnicodeEnd: $00171F; TableName: 'Tagalog'),
                           (UnicodeStart: $001720; UnicodeEnd: $00173F; TableName: 'Hanunoo'),
                           (UnicodeStart: $001740; UnicodeEnd: $00175F; TableName: 'Buhid'),
                           (UnicodeStart: $001760; UnicodeEnd: $00177F; TableName: 'Tagbanwa'),
                           (UnicodeStart: $001780; UnicodeEnd: $0017FF; TableName: 'Khmer'),
                           (UnicodeStart: $001800; UnicodeEnd: $0018AF; TableName: 'Mongolian'),
                           (UnicodeStart: $0018B0; UnicodeEnd: $0018FF; TableName: 'Unified Canadian Aboriginal Syllabics Extended'),
                           (UnicodeStart: $001900; UnicodeEnd: $00184F; TableName: 'Limbu'),
                           (UnicodeStart: $001950; UnicodeEnd: $00197F; TableName: 'Tai Le'),
                           (UnicodeStart: $001980; UnicodeEnd: $0019DF; TableName: 'New Tai Lue'),
                           (UnicodeStart: $0019E0; UnicodeEnd: $0019FF; TableName: 'Khmer Symbols'),
                           (UnicodeStart: $001A00; UnicodeEnd: $001A1F; TableName: 'Buginese'),
                           (UnicodeStart: $001A20; UnicodeEnd: $001AAF; TableName: 'Tai Tham'),
                           (UnicodeStart: $001AB0; UnicodeEnd: $001AFF; TableName: 'Combining Diacritical Marks Extended'),
                           (UnicodeStart: $001B00; UnicodeEnd: $001B7F; TableName: 'Balinese'),
                           (UnicodeStart: $001B80; UnicodeEnd: $001BBF; TableName: 'Sundanese'),
                           (UnicodeStart: $001BC0; UnicodeEnd: $001BFF; TableName: 'Batak'),
                           (UnicodeStart: $001C00; UnicodeEnd: $001C4F; TableName: 'Lepcha'),
                           (UnicodeStart: $001C50; UnicodeEnd: $001C7F; TableName: 'Ol Chiki'),
                           (UnicodeStart: $001CC0; UnicodeEnd: $001CCF; TableName: 'Sundanese Supplement'),
                           (UnicodeStart: $001CD0; UnicodeEnd: $001CFF; TableName: 'Vedic Extensions'),
                           (UnicodeStart: $001D00; UnicodeEnd: $001D7F; TableName: 'Phonetic Extensions'),
                           (UnicodeStart: $001D80; UnicodeEnd: $001DBF; TableName: 'Phonetic Extensions Supplement'),
                           (UnicodeStart: $001DC0; UnicodeEnd: $001DFF; TableName: 'Combining Diacritical Marks Supplement'),
                           (UnicodeStart: $001E00; UnicodeEnd: $001EFF; TableName: 'Latin Extended Additional'),
                           (UnicodeStart: $001F00; UnicodeEnd: $001FFF; TableName: 'Greek Extended'),
                           (UnicodeStart: $002000; UnicodeEnd: $00206F; TableName: 'General Punctuation'),
                           (UnicodeStart: $002070; UnicodeEnd: $00209F; TableName: 'Superscripts and Subscripts'),
                           (UnicodeStart: $0020A0; UnicodeEnd: $0020CF; TableName: 'Currency Symbols'),
                           (UnicodeStart: $0020D0; UnicodeEnd: $0020FF; TableName: 'Combining Marks for Symbols'),
                           (UnicodeStart: $002100; UnicodeEnd: $00214F; TableName: 'Letterlike Symbols'),
                           (UnicodeStart: $002150; UnicodeEnd: $00218F; TableName: 'Number Forms'),
                           (UnicodeStart: $002190; UnicodeEnd: $0021FF; TableName: 'Arrows'),
                           (UnicodeStart: $002200; UnicodeEnd: $0022FF; TableName: 'Mathematical Operators'),
                           (UnicodeStart: $002300; UnicodeEnd: $0023FF; TableName: 'Miscellaneous Technical'),
                           (UnicodeStart: $002400; UnicodeEnd: $00243F; TableName: 'Control Pictures'),
                           (UnicodeStart: $002440; UnicodeEnd: $00245F; TableName: 'Optical Character Recognition'),
                           (UnicodeStart: $002460; UnicodeEnd: $0024FF; TableName: 'Enclosed Alphanumerics'),
                           (UnicodeStart: $002500; UnicodeEnd: $00257F; TableName: 'Box Drawing'),
                           (UnicodeStart: $002580; UnicodeEnd: $00259F; TableName: 'Block Elements'),
                           (UnicodeStart: $0025A0; UnicodeEnd: $0025FF; TableName: 'Geometric Shapes'),
                           (UnicodeStart: $002600; UnicodeEnd: $0026FF; TableName: 'Miscellaneous Symbols'),
                           (UnicodeStart: $002700; UnicodeEnd: $0027BF; TableName: 'Dingbats'),
                           (UnicodeStart: $0027C0; UnicodeEnd: $0027EF; TableName: 'Miscellaneous Mathematical Symbols - A'),
                           (UnicodeStart: $0027F0; UnicodeEnd: $0027FF; TableName: 'Supplemental Arrows - A'),
                           (UnicodeStart: $002800; UnicodeEnd: $0028FF; TableName: 'Braille Patterns'),
                           (UnicodeStart: $002900; UnicodeEnd: $00297F; TableName: 'Supplemental Arrows - B'),
                           (UnicodeStart: $002980; UnicodeEnd: $0029FF; TableName: 'Miscellaneous Mathematical Symbols - B'),
                           (UnicodeStart: $002A00; UnicodeEnd: $002AFF; TableName: 'Supplemental Mathematical Operators'),
                           (UnicodeStart: $002B00; UnicodeEnd: $002BFF; TableName: 'Miscellaneous Symbols and Arrows'),
                           (UnicodeStart: $002C00; UnicodeEnd: $002C5F; TableName: 'Glagolitic'),
                           (UnicodeStart: $002C60; UnicodeEnd: $002C7F; TableName: 'Latin Extended-C'),
                           (UnicodeStart: $002C80; UnicodeEnd: $002CFF; TableName: 'Coptic'),
                           (UnicodeStart: $002D00; UnicodeEnd: $002D2F; TableName: 'Georgian Supplement'),
                           (UnicodeStart: $002D30; UnicodeEnd: $002D7F; TableName: 'Tifinagh'),
                           (UnicodeStart: $002D80; UnicodeEnd: $002DDF; TableName: 'Ethiopic Extended'),
                           (UnicodeStart: $002DE0; UnicodeEnd: $002DFF; TableName: 'Cyrillic Extended-A'),
                           (UnicodeStart: $002E00; UnicodeEnd: $002E7F; TableName: 'Supplemental Punctuation'),
                           (UnicodeStart: $002E80; UnicodeEnd: $002EFF; TableName: 'CJK Radicals Supplement'),
                           (UnicodeStart: $002F00; UnicodeEnd: $002FDF; TableName: 'Kangxi Radicals'),
                           (UnicodeStart: $002FF0; UnicodeEnd: $002FFF; TableName: 'Ideographic Description Characters'),
                           (UnicodeStart: $003000; UnicodeEnd: $00303F; TableName: 'CJK Symbols and Punctuation'),
                           (UnicodeStart: $003040; UnicodeEnd: $00309F; TableName: 'Hiragana'),
                           (UnicodeStart: $0030A0; UnicodeEnd: $0030FF; TableName: 'Katakana'),
                           (UnicodeStart: $003100; UnicodeEnd: $00312F; TableName: 'Bopomofo'),
                           (UnicodeStart: $003130; UnicodeEnd: $00318F; TableName: 'Hangul Compatibility Jamo'),
                           (UnicodeStart: $003190; UnicodeEnd: $00319F; TableName: 'Kanbun'),
                           (UnicodeStart: $0031A0; UnicodeEnd: $0031BF; TableName: 'Bopomofo Extended'),
                           (UnicodeStart: $0031C0; UnicodeEnd: $0031EF; TableName: 'CJK Strokes'),
                           (UnicodeStart: $0031F0; UnicodeEnd: $0031FF; TableName: 'Katakana Phonetic Extensions'),
                           (UnicodeStart: $003200; UnicodeEnd: $0032FF; TableName: 'Enclosed CJK Letters and Months'),
                           (UnicodeStart: $003300; UnicodeEnd: $0033FF; TableName: 'CJK Compatibility'),
                           (UnicodeStart: $003400; UnicodeEnd: $004DB5; TableName: 'CJK Unified Ideographs Extension A'),
                           (UnicodeStart: $004DC0; UnicodeEnd: $004DFF; TableName: 'Yijing Hexagram Symbols'),
                           (UnicodeStart: $004E00; UnicodeEnd: $009FD5; TableName: 'CJK Unified Ideographs'),
                           (UnicodeStart: $00A000; UnicodeEnd: $00A48F; TableName: 'Yi Syllables'),
                           (UnicodeStart: $00A490; UnicodeEnd: $00A4CF; TableName: 'Yi Radicals'),
                           (UnicodeStart: $00A4D0; UnicodeEnd: $00A4FF; TableName: 'Lisu'),
                           (UnicodeStart: $00A500; UnicodeEnd: $00A63F; TableName: 'Vai'),
                           (UnicodeStart: $00A640; UnicodeEnd: $00A69F; TableName: 'Cyrillic Extended-B'),
                           (UnicodeStart: $00A6A0; UnicodeEnd: $00A6FF; TableName: 'Bamum'),
                           (UnicodeStart: $00A700; UnicodeEnd: $00A71F; TableName: 'Modifier Tone Letters'),
                           (UnicodeStart: $00A720; UnicodeEnd: $00A7FF; TableName: 'Latin Extended-D'),
                           (UnicodeStart: $000A80; UnicodeEnd: $00A82F; TableName: 'Syloti Nagri'),
                           (UnicodeStart: $00A830; UnicodeEnd: $00A83F; TableName: 'Common Indic Number Forms'),
                           (UnicodeStart: $00A840; UnicodeEnd: $00A87F; TableName: 'Phags-pa'),
                           (UnicodeStart: $00A880; UnicodeEnd: $00A8DF; TableName: 'Saurashtra'),
                           (UnicodeStart: $00A8E0; UnicodeEnd: $00A8FF; TableName: 'Devanagari Extended'),
                           (UnicodeStart: $00A900; UnicodeEnd: $00A92F; TableName: 'Kayah Li'),
                           (UnicodeStart: $00A930; UnicodeEnd: $00A95F; TableName: 'Rejang'),
                           (UnicodeStart: $00A960; UnicodeEnd: $00A97F; TableName: 'Hangul Jamo Extended-A'),
                           (UnicodeStart: $00A980; UnicodeEnd: $00A9DF; TableName: 'Javanese'),
                           (UnicodeStart: $00A9E0; UnicodeEnd: $00A9FF; TableName: 'Myanmar Extended-B'),
                           (UnicodeStart: $00AA00; UnicodeEnd: $00AA5F; TableName: 'Cham'),
                           (UnicodeStart: $00AA60; UnicodeEnd: $00AA7F; TableName: 'Myanmar Extended-A'),
                           (UnicodeStart: $00AA80; UnicodeEnd: $00AADF; TableName: 'Tai Viet'),
                           (UnicodeStart: $00AAE0; UnicodeEnd: $00AAFF; TableName: 'Meetei Mayek Extensions'),
                           (UnicodeStart: $00AB00; UnicodeEnd: $00AB2F; TableName: 'Ethiopic Extended-A'),
                           (UnicodeStart: $00AB30; UnicodeEnd: $00AB6F; TableName: 'Latin Extended-E'),
                           (UnicodeStart: $00AB70; UnicodeEnd: $00ABBF; TableName: 'Cherokee Supplement'),
                           (UnicodeStart: $00ABC0; UnicodeEnd: $00ABFF; TableName: 'Meetei Mayek'),
                           (UnicodeStart: $00AC00; UnicodeEnd: $00D7AF; TableName: 'Hangul Syllables'),
                           (UnicodeStart: $00D7B0; UnicodeEnd: $00D7FF; TableName: 'Hangul Jamo Extended-B'),
                           (UnicodeStart: $00D800; UnicodeEnd: $00DBFF; TableName: 'High Surrogates'),
                           (UnicodeStart: $00DC00; UnicodeEnd: $00DFFF; TableName: 'Low Surrogates'),
                           (UnicodeStart: $00E000; UnicodeEnd: $00F8FF; TableName: 'Private Use Area'),
                           (UnicodeStart: $00F900; UnicodeEnd: $00FAD9; TableName: 'CJK Compatibility Ideographs'),
                           (UnicodeStart: $00FB00; UnicodeEnd: $00FB4F; TableName: 'Alphabetic Presentation Forms'),
                           (UnicodeStart: $00FB50; UnicodeEnd: $00FDFF; TableName: 'Arabic Presentation Forms - A'),
                           (UnicodeStart: $00FE00; UnicodeEnd: $00FE0F; TableName: 'Variation Selectors'),
                           (UnicodeStart: $00FE10; UnicodeEnd: $00FE1F; TableName: 'Vertical Forms'),
                           (UnicodeStart: $00FE20; UnicodeEnd: $00FE2F; TableName: 'Combining Half Marks'),
                           (UnicodeStart: $00FE30; UnicodeEnd: $00FE4F; TableName: 'CJK Compatibility Forms'),
                           (UnicodeStart: $00FE50; UnicodeEnd: $00FE6F; TableName: 'Small Form Variants'),
                           (UnicodeStart: $00FE70; UnicodeEnd: $00FEFF; TableName: 'Arabic Presentation Forms - B'),
                           (UnicodeStart: $00FF00; UnicodeEnd: $00FFEF; TableName: 'Halfwidth and Fullwidth Forms'),
                           (UnicodeStart: $00FFF0; UnicodeEnd: $00FFFF; TableName: 'Specials'),
                           (UnicodeStart: $010000; UnicodeEnd: $01007F; TableName: 'Linear B Syllabary'),
                           (UnicodeStart: $010080; UnicodeEnd: $0100FF; TableName: 'Linear B Ideograms'),
                           (UnicodeStart: $010100; UnicodeEnd: $01013F; TableName: 'Aegean Numbers'),
                           (UnicodeStart: $010140; UnicodeEnd: $01018F; TableName: 'Ancient Greek Numbers'),
                           (UnicodeStart: $010190; UnicodeEnd: $0101CF; TableName: 'Ancient Symbols'),
                           (UnicodeStart: $0101D0; UnicodeEnd: $0101FF; TableName: 'Phaistos Disc'),
                           (UnicodeStart: $010280; UnicodeEnd: $01029F; TableName: 'Lycian'),
                           (UnicodeStart: $0102A0; UnicodeEnd: $0102DF; TableName: 'Carian'),
                           (UnicodeStart: $0102E0; UnicodeEnd: $0102FF; TableName: 'Coptic Epact Numbers'),
                           (UnicodeStart: $010300; UnicodeEnd: $01032F; TableName: 'Old Italic'),
                           (UnicodeStart: $010330; UnicodeEnd: $01034F; TableName: 'Gothic'),
                           (UnicodeStart: $010350; UnicodeEnd: $01037F; TableName: 'Old Permic'),
                           (UnicodeStart: $010380; UnicodeEnd: $01039F; TableName: 'Ugaritic'),
                           (UnicodeStart: $0103A0; UnicodeEnd: $0103DF; TableName: 'Old Persian'),
                           (UnicodeStart: $010400; UnicodeEnd: $01044F; TableName: 'Deseret'),
                           (UnicodeStart: $010450; UnicodeEnd: $01047F; TableName: 'Shavian'),
                           (UnicodeStart: $010480; UnicodeEnd: $0104AF; TableName: 'Osmanya'),
                           (UnicodeStart: $010500; UnicodeEnd: $01052F; TableName: 'Elbasan'),
                           (UnicodeStart: $010530; UnicodeEnd: $01056F; TableName: 'Caucasian Albanian'),
                           (UnicodeStart: $010600; UnicodeEnd: $01077F; TableName: 'Linear A'),
                           (UnicodeStart: $010800; UnicodeEnd: $01083F; TableName: 'Cypriot Syllabary'),
                           (UnicodeStart: $010840; UnicodeEnd: $01085F; TableName: 'Imperial Aramaic'),
                           (UnicodeStart: $010860; UnicodeEnd: $01087F; TableName: 'Palmyrene'),
                           (UnicodeStart: $010880; UnicodeEnd: $0108AF; TableName: 'Nabataean'),
                           (UnicodeStart: $0108E0; UnicodeEnd: $0108FF; TableName: 'Hatran'),
                           (UnicodeStart: $010900; UnicodeEnd: $01091F; TableName: 'Phoenician'),
                           (UnicodeStart: $010920; UnicodeEnd: $01093F; TableName: 'Lydian'),
                           (UnicodeStart: $010980; UnicodeEnd: $01099F; TableName: 'Meroitic Hieroglyphs'),
                           (UnicodeStart: $0109A0; UnicodeEnd: $0109FF; TableName: 'Meroitic Cursive'),
                           (UnicodeStart: $010A00; UnicodeEnd: $010A5F; TableName: 'Kharoshthi'),
                           (UnicodeStart: $010A60; UnicodeEnd: $010A7F; TableName: 'Old South Arabian'),
                           (UnicodeStart: $010A80; UnicodeEnd: $010A9F; TableName: 'Old North Arabian'),
                           (UnicodeStart: $010AC0; UnicodeEnd: $010AFF; TableName: 'Manichaean'),
                           (UnicodeStart: $010B00; UnicodeEnd: $010B3F; TableName: 'Avestan'),
                           (UnicodeStart: $010B40; UnicodeEnd: $010B5F; TableName: 'Inscriptional Parthian'),
                           (UnicodeStart: $010B60; UnicodeEnd: $010B7F; TableName: 'Inscriptional Pahlavi'),
                           (UnicodeStart: $010B80; UnicodeEnd: $010BAF; TableName: 'Psalter Pahlavi'),
                           (UnicodeStart: $010C00; UnicodeEnd: $010C4F; TableName: 'Old Turkic'),
                           (UnicodeStart: $010C80; UnicodeEnd: $010CFF; TableName: 'Old Hungarian'),
                           (UnicodeStart: $010E60; UnicodeEnd: $010E7F; TableName: 'Rumi Numeral Symbols'),
                           (UnicodeStart: $011000; UnicodeEnd: $01107F; TableName: 'Brahmi'),
                           (UnicodeStart: $011080; UnicodeEnd: $0110CF; TableName: 'Kaithi'),
                           (UnicodeStart: $0110D0; UnicodeEnd: $0110FF; TableName: 'Sora Sompeng'),
                           (UnicodeStart: $011100; UnicodeEnd: $01114F; TableName: 'Chakma'),
                           (UnicodeStart: $011150; UnicodeEnd: $01117F; TableName: 'Mahajani'),
                           (UnicodeStart: $011180; UnicodeEnd: $0111DF; TableName: 'Sharada'),
                           (UnicodeStart: $0111E0; UnicodeEnd: $0111FF; TableName: 'Sinhala Archaic Numbers'),
                           (UnicodeStart: $011200; UnicodeEnd: $01124F; TableName: 'Khojki'),
                           (UnicodeStart: $011280; UnicodeEnd: $0112AF; TableName: 'Multani'),
                           (UnicodeStart: $0112B0; UnicodeEnd: $0112FF; TableName: 'Khudawadi'),
                           (UnicodeStart: $011300; UnicodeEnd: $01137F; TableName: 'Grantha'),
                           (UnicodeStart: $011480; UnicodeEnd: $0114DF; TableName: 'Tirhuta'),
                           (UnicodeStart: $011580; UnicodeEnd: $0115FF; TableName: 'Siddham'),
                           (UnicodeStart: $011600; UnicodeEnd: $01165F; TableName: 'Modi'),
                           (UnicodeStart: $011680; UnicodeEnd: $0116CF; TableName: 'Takri'),
                           (UnicodeStart: $011700; UnicodeEnd: $01173F; TableName: 'Ahom'),
                           (UnicodeStart: $0118A0; UnicodeEnd: $0118FF; TableName: 'Warang Citi'),
                           (UnicodeStart: $011AC0; UnicodeEnd: $011AFF; TableName: 'Pau Cin Hau'),
                           (UnicodeStart: $012000; UnicodeEnd: $0123FF; TableName: 'Cuneiform'),
                           (UnicodeStart: $012400; UnicodeEnd: $01247F; TableName: 'Cuneiform Numbers and Punctuation'),
                           (UnicodeStart: $012480; UnicodeEnd: $01254F; TableName: 'Early Dynastic Cuneiform'),
                           (UnicodeStart: $013000; UnicodeEnd: $01342F; TableName: 'Egyptian Hieroglyphs'),
                           (UnicodeStart: $014400; UnicodeEnd: $01467F; TableName: 'Anatolian Hieroglyphs'),
                           (UnicodeStart: $016800; UnicodeEnd: $016A3F; TableName: 'Bamum Supplement'),
                           (UnicodeStart: $016A40; UnicodeEnd: $016A6F; TableName: 'Mro'),
                           (UnicodeStart: $016AD0; UnicodeEnd: $016AFF; TableName: 'Bassa Vah'),
                           (UnicodeStart: $016B00; UnicodeEnd: $016B8F; TableName: 'Pahawh Hmong'),
                           (UnicodeStart: $016F00; UnicodeEnd: $016F9F; TableName: 'Miao'),
                           (UnicodeStart: $01B000; UnicodeEnd: $01B0FF; TableName: 'Kana Supplement'),
                           (UnicodeStart: $01BC00; UnicodeEnd: $01BC9F; TableName: 'Duployan'),
                           (UnicodeStart: $01BCA0; UnicodeEnd: $01BCAF; TableName: 'Shorthand Format Controls'),
                           (UnicodeStart: $01D000; UnicodeEnd: $01D0FF; TableName: 'Byzantine Musical Symbols'),
                           (UnicodeStart: $01D100; UnicodeEnd: $01D1FF; TableName: 'Musical Symbols'),
                           (UnicodeStart: $01D200; UnicodeEnd: $01D24F; TableName: 'Ancient Greek Musical Notation'),
                           (UnicodeStart: $01D300; UnicodeEnd: $01F35F; TableName: 'Tai Xuan Jing Symbols'),
                           (UnicodeStart: $01D360; UnicodeEnd: $01D37F; TableName: 'Counting Rod Numerals'),
                           (UnicodeStart: $01D400; UnicodeEnd: $01D7FF; TableName: 'Mathematical Alphanumeric Symbols'),
                           (UnicodeStart: $01D800; UnicodeEnd: $01DAAF; TableName: 'Sutton SignWriting'),
                           (UnicodeStart: $01E800; UnicodeEnd: $01E8DF; TableName: 'Mende Kikakui'),
                           (UnicodeStart: $01EE00; UnicodeEnd: $01EEFF; TableName: 'Arabic Mathematical Alphabetic Symbols'),
                           (UnicodeStart: $01F000; UnicodeEnd: $01F02F; TableName: 'Mahjong Tiles'),
                           (UnicodeStart: $01F030; UnicodeEnd: $01F09F; TableName: 'Domino Tiles'),
                           (UnicodeStart: $01F0A0; UnicodeEnd: $01F0FF; TableName: 'Playing Cards'),
                           (UnicodeStart: $01F100; UnicodeEnd: $01F1FF; TableName: 'Enclosed Alphanumeric Supplement'),
                           (UnicodeStart: $01F200; UnicodeEnd: $01F2FF; TableName: 'Enclosed Ideographic Supplement'),
                           (UnicodeStart: $01F300; UnicodeEnd: $01F5FF; TableName: 'Miscellaneous Symbols and Pictographs'),
                           (UnicodeStart: $01F600; UnicodeEnd: $01F64F; TableName: 'Emoticons'),
                           (UnicodeStart: $01F650; UnicodeEnd: $01F67F; TableName: 'Ornamental Dingbats'),
                           (UnicodeStart: $01F680; UnicodeEnd: $01F6FF; TableName: 'Transport and Map Symbols'),
                           (UnicodeStart: $01F700; UnicodeEnd: $01F77F; TableName: 'Alchemical Symbols'),
                           (UnicodeStart: $01F780; UnicodeEnd: $01F7FF; TableName: 'Geometric Shapes Extended'),
                           (UnicodeStart: $01F800; UnicodeEnd: $01F8FF; TableName: 'Supplemental Arrows-C'),
                           (UnicodeStart: $01F900; UnicodeEnd: $01F9FF; TableName: 'Supplemental Symbols and Pictographs'),
                           (UnicodeStart: $020000; UnicodeEnd: $02A6D6; TableName: 'CJK Unified Ideographs Extension B'),
                           (UnicodeStart: $02A700; UnicodeEnd: $02B734; TableName: 'CJK Unified Ideographs Extension C'),
                           (UnicodeStart: $02B740; UnicodeEnd: $02B81D; TableName: 'CJK Unified Ideographs Extension D'),
                           (UnicodeStart: $02B820; UnicodeEnd: $02CEA1; TableName: 'CJK Unified Ideographs Extension E'),
                           (UnicodeStart: $02F800; UnicodeEnd: $02FA1F; TableName: 'CJK Compatibility Ideographs Supplement'),
                           (UnicodeStart: $0E0000; UnicodeEnd: $0E007F; TableName: 'Tags'),
                           (UnicodeStart: $0E0100; UnicodeEnd: $0E01EF; TableName: 'Variation Selectors Supplement'),
                           (UnicodeStart: $0F0000; UnicodeEnd: $0FFFFD; TableName: 'Supplementary Private Use Area - A'),
                           (UnicodeStart: $100000; UnicodeEnd: $10FFFD; TableName: 'Supplementary Private Use Area - B'));

function UnicodeToTable(Unicode: dword): integer;

var
  i                     : Integer;

begin
  Result := -1;

  for i := 0 to UNICODETABELSIZE - 1 do
    if (Unicode >= UnicodeTable[i].UnicodeStart) and (Unicode <= UnicodeTable[i].UnicodeEnd) then
    begin
      Result := i;
      exit;
    end;
end;

var
  f                     : file;
  Hdr                   : array[0..4] of AnsiChar;
  NrFontDefEntries      : dword;
  i, t                  : integer;
  FontDefUC             : tFontDefUC;
  UnicodeHits           : array[0..UNICODETABELSIZE - 1] of integer;

begin
  AssignFile(f, paramstr(1));
  Reset(f, 1);
  BlockRead(f, Hdr[0], 4);
  Hdr[4] := #0;

  BlockRead(f, NrFontDefEntries, sizeof(dword));

  for i := 0 to NrFontDefEntries - 1 do
  begin
    BlockRead(f, FontDefUC, sizeof(FontDefUC));
    t := UnicodeToTable(FontDefUC.Unicode);
    if t >= 0 then inc(UnicodeHits[t]);
  end;

  CloseFile(f);

  for i := 0 to UNICODETABELSIZE - 1 do
    if UnicodeHits[i] > 0 then
      Writeln(Format('0x%8.8x: %s', [UnicodeTable[i].UnicodeStart, UnicodeTable[i].TableName]));
end.

