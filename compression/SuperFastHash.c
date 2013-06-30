#include "../libFireBird.h"

#undef get16bits
#if(defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const word *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((const byte *)(d))[1] << (dword)(8))\
                      +((const byte *)(d))[0])
#endif

dword SuperFastHash(register unsigned char * data, int len, dword hash)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("SuperFastHash");
  #endif

  register dword tmp, tmp2;
  int rem;

  if(len <= 0 || data == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  rem = len & 3;
  len >>= 2;

  /* Main loop */
  while(len>0)
  {
    tmp    = get16bits(data);
    data  += 2;
    tmp2   = get16bits(data);
    data  += 2;
    if(tmp || tmp2)
    {
      hash  += tmp;
      tmp2 <<= 11;
      tmp2  ^= hash;
      hash <<= 16;
      hash  ^= tmp2;
      hash  += hash >> 11;
    }
    len -= 4;
  }

  /* Handle end cases */
  switch(rem)
  {
    case 3:
      hash += get16bits(data);
      hash ^= hash << 16;
      hash ^= data[sizeof(word)] << 18;
      hash += hash >> 11;
      break;

    case 2:
      hash += get16bits(data);
      hash ^= hash << 11;
      hash += hash >> 17;
      break;

    case 1:
      hash += *data;
      hash ^= hash << 10;
      hash += hash >> 1;
      break;
  }

  /* Force "avalanching" of final 127 bits */
  hash ^= hash << 3;
  hash += hash >> 5;
  hash ^= hash << 2;
  hash += hash >> 15;
  hash ^= hash << 10;
  hash += (hash << 16) | (hash >> 16);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return hash;
}
