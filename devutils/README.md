## TAP development utilities

### JailBreak

The Topfield TMS TAP runtime environment does not allow TAPs to call
Linux system commands. TAPs are constrained to use only the TAP-API.
While this might be o.k. for most TAPs, there are still a lot of things
which cannot be done because of the limited functionality of the API.

The JailBreak utility modifies the compiled TAP so that it passes the
check upon launch regardless of what you have coded.

Usage: JailBreak filename.tap

Add this to your Makefile/build.


### tapput

    usage: tapput [-h] [-u USER] [-p PASSWORD] [-n] host tapfile [tapfile ...]

    Program to copy one or more TAP files to specified Topfield PVR host.

    positional arguments:
    host                  Topfield PVR IP host name/address
    tapfile               1 or more TAP files to copy

    optional arguments:
    -h, --help            show this help message and exit
    -u USER, --user USER  ftp login user name (default: guest)
    -p PASSWORD, --password PASSWORD
			    ftp login user password (default: 0000)
    -n, --noauto          put tapfile[s] in "/ProgramFiles" dir rather than
			    "/ProgramFiles/AutoStart" (default: False)

I have also include a shell version (that requires ncftp package).
It has the same options and usage.

    tapput.sh toppy my.tap

### tapdebug

    usage: tapdebug [-h] [-u USER] [-p PASSWORD] [-t TIMEOUT] host

    Program to connect to FTP TAP debug port on specfied Topfield TMS PVR host and
    print all diagnostics.

    positional arguments:
    host                  Topfield PVR IP host name/address

    optional arguments:
    -h, --help            show this help message and exit
    -u USER, --user USER  ftp login user name (default: guest)
    -p PASSWORD, --password PASSWORD
			    ftp login user password (default: 0000)
    -t TIMEOUT, --timeout TIMEOUT
			    timeout in secs (default: 4)

### tapfont

When I first used the the TMSOSDMenu functions I found my TAP binary was
huge due to the raw bitmaps included on the font files. I noticed those
font bitmaps had many repeated sequences of 0x00 and 0xff bytes.
Accordingly I re-encoded the font source files with a very primitive
"compression" scheme where I just follow those 2 bytes with a repeat
byte. The code changes to support this are trivial (a few lines in 2
files), impose zero extra runtime overhead, and are backwards compatible
with the original font files (i.e. FM_LoadFontFile.c will still read the
original bitmap files, or the new compressed format). The size changes
in TMSOSDMenu/font are:

    Calibri_10.c:/* Compressed from 18048 to 9269 bytes (-49%) */
    Calibri_12.c:/* Compressed from 27824 to 12490 bytes (-56%) */
    Calibri_14.c:/* Compressed from 40432 to 17197 bytes (-58%) */
    Calibri_16.c:/* Compressed from 50064 to 19738 bytes (-61%) */
    Calibri_18.c:/* Compressed from 64400 to 22001 bytes (-66%) */
    Calibri_20.c:/* Compressed from 81760 to 25887 bytes (-69%) */
    Calibri_20B.c:/* Compressed from 83776 to 25040 bytes (-71%) */

This tapfont program is what I created to convert the above source files.
Linking with this, reduced my small TAP application from 470K to 195K.
The tapfont program will also convert existing uncompressed binary font
files to compressed binary files.

    usage: tapfont [-h] [-i] [-o] [-x] [-t] file

    Topfield FireBird library (FireBirdLib) font file compressor/converter.
    Converts an uncompressed C source font file into a compressed C source font
    file. Or converts an uncompressed binary font file into a compressed binary
    font file. Reads given input file, or standard input, and writes to standard
    output. Can also compress source to binary, or binary to source. Rather than
    compress, you can uncompress, or even just straight translate input to output.
    So all combinations of source/binary input to output
    compression/uncompression/translation are possible.

    positional arguments:
    file              input C source, or binary, file. Or '-' for stdin

    optional arguments:
    -h, --help        show this help message and exit
    -i, --in_binary   read binary input instead of C source
    -o, --out_binary  write binary output instead of C source
    -x, --uncompress  uncompress rather than compress
    -t, --translate   do not compress/uncompress, just translate input to output
