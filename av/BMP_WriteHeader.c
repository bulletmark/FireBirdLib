#include "FBLib_av.h"
#include "../libFireBird.h"

void BMP_WriteHeader (TYPE_File *pFile, int width, int height )
{
  static struct BMP_HEAD head;
  static struct BMP_INFO info;
  dword                  i, size, rowlength;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("BMP_WriteHeader");
#endif

	// according to spec.: the rowlength must be a multiple of 4 bytes, if necessary fill up with zero-bytes
	rowlength = (width*3%4==0) ? width*3 : ((width*3/4)+1)*4;

 	size = sizeof( head ) + sizeof( info ) + rowlength*height;

  head.id[0]          = 'B';
  head.id[1]          = 'M';
  head.size_l         = LE16( (size & 0xffff) );
  head.size_h         = LE16( (size >> 16) );
  i                   = (sizeof( head ) + sizeof( info ));
  head.offset_l       = LE16( i & 0xffff );
  head.offset_h       = LE16( i >> 16 );

  info.info_size      = LE32( 40 );
  info.width          = LE32( width );
  info.height         = LE32( height );
  info.plane          = LE16( 1 );
  info.bits_per_pixel = LE16( 24 );
  info.compress       = LE32( 0 );
  info.img_size       = LE32( rowlength*height );
  info.x_res          = 0;
  info.y_res          = 0;
  info.color          = 0;
  info.icolor         = 0;

  TAP_Hdd_Fwrite( &head, sizeof( head ), 1, pFile );
  TAP_Hdd_Fwrite( &info, sizeof( info ), 1, pFile );

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

}
