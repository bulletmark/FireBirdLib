#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

#define PERCOLATE
/*
NOTE :
   LHArc uses a "percolating" update of its Lempel-Ziv structures.
   If you use the percolating method, the compressor will run slightly faster,
   using a little more memory, and will be slightly less efficient than the
   standard method.
   You can choose either method, and note that the decompressor is not
   affected by this choice and is able To decompress data created by each one
   of the compressors.
*/

typedef short *ARPWord;
typedef byte *ARPByte;

/*
NOTE :
   The following constants are set to the values used by LHArc.
   You can change three of them as follows :

   DICBIT : Lempel-Ziv dictionnary size.
   Lowering this constant can lower the compression efficiency a lot !
   But increasing it (on a 32 bit platform only, i.e. Delphi 2) will not yield
   noticeably better results.
   If you set DICBIT to 15 or more, set PBIT To 5; and if you set DICBIT to 19
   or more, set NPT to NP, too.

   WINBIT : Sliding window size.
   The compression ratio depends a lot of this value.
   You can increase it to 15 to get better results on large files.
   I recommend doing this if you have enough memory, except if you want that
   your compressed data remain compatible with LHArc.
   On a 32 bit platform, you can increase it to 16. Using a larger value will
   only waste time and memory.

   BUFBIT : I/O Buffer size. You can lower it to save memory, or increase it
   to reduce disk access.
*/
#define BITBUFSIZ (16)
#define UCHARMAX  (255)

#define DICBIT    (13)
#define DICSIZ    (1<<DICBIT)

#define MATCHBIT  (8)
#define MAXMATCH  (1<<MATCHBIT)
#define THRESHOLD (3)
#define PERCFLAG  (0x8000)

#define NC        (UCHARMAX+MAXMATCH+2-THRESHOLD)
#define CBIT      (9)
#define CODEBIT   (16)

#define NP        (DICBIT+1)
#define NT        (CODEBIT+3)
#define PBIT      4
#define TBIT      5
#define NPT       NT

#define NUL       (0)
#define MAXHASHVAL (3*DICSIZ+((DICSIZ>>9)+1)*UCHARMAX)

#define WINBIT    (14)
#define WINDOWSIZE (1<<WINBIT)

#define BUFBIT    (15)
#define BUFSIZE   (1<<BUFBIT)

typedef struct {
  int OrigSize, CompSize;

  word BitBuf;
  word SubBitBuf, BitCount;

  word Left[2*NC-1], Right[2*NC-1];

  word PtTable[256];
  byte PtLen[NPT];
  word CTable[4096];
  byte CLen[NC];

  word BlockSize;

// The following variables are used by the compression engine only

  ARPByte Buf;

  word CFreq[2*NC-1];
  word PFreq[2*NP-1];
  word TFreq[2*NT-1];

  word CCode[NC];
  word PtCode[NPT];

  word CPos, OutputMask;
  ARPByte Text, ChildCount;

  word Pos, MatchPos, Avail;
  ARPWord Position, Parent, Prev, Next;

  short Remainder, MatchLen;
  ARPByte Level;

  byte *FileInPtr, *FileOutPtr;
  dword InBufferBytes;
  word Failed;
  dword CBytesWritten;

  word Decode_I;
  short Decode_J;
} ARDATA;

static byte GetC(ARDATA *ar);
static void PutC(ARDATA *ar, byte c);
static int BRead(ARDATA *ar, byte *p, word n);
static void BWrite(ARDATA *ar, byte *p, int n);
static void FillBuf(ARDATA *ar, word n);
static word GetBits(ARDATA *ar, short n);
static void PutBits(ARDATA *ar, word n, word x);
static void InitGetBits(ARDATA *ar);
static void InitPutBits(ARDATA *ar);
static void MakeTable(ARDATA *ar, short nchar, ARPByte bitlen, word tablebits, ARPWord table);
static void ReadPtLen(ARDATA *ar, short nn, short nbit, short ispecial);
static void ReadCLen(ARDATA *ar);
static word DecodeC(ARDATA *ar);
static word DecodeP(ARDATA *ar);
static void InitVars(ARDATA *ar);
static void DecodeBuffer(ARDATA *ar, word count, ARPByte arbuffer);
static void Decode(ARDATA *ar);
static void CountLen(ARDATA *ar, short i, word *lencnt, short nparm);
static void MakeLen(ARDATA *ar, short root, word *lencnt, byte *len, short nparm, ARPWord sortptr);
static void DownHeap(word *heap, short i, short heapsize, ARPWord freqparm);
static void MakeCode(short n, ARPByte len, ARPWord code, word *lencnt);
static short MakeTree(ARDATA *ar, short nparm, ARPWord freqparm, byte *len, ARPWord codeparm);
static void CountTFreq(ARDATA *ar);
static void WritePtLen(ARDATA *ar, short n, short nbit, short ispecial);
static void WriteCLen(ARDATA *ar);
static void EncodeC(ARDATA *ar, short c);
static void EncodeP(ARDATA *ar, word p);
static void SendBlock(ARDATA *ar);
static word Output(ARDATA *ar, word c, word p, word outputpos);
static void InitSlide(ARDATA *ar);
static short Hash(short p, byte c);
static short Child(ARDATA *ar, short q, byte c);
static void MakeChild(ARDATA *ar, short q, byte c, short r);
static void Split(ARDATA *ar, short old);
static void InsertNode(ARDATA *ar);
static void DeleteNode(ARDATA *ar);
static void GetNextMatch(ARDATA *ar);
static int allocate_memory(ARDATA *ar);
static void free_memory(ARDATA *ar);
static void Encode(ARDATA *ar);

/********************************** File I/O **********************************/

static inline byte GetC(ARDATA *ar)
{
  byte c;
  c = *ar->FileInPtr;
  ar->FileInPtr++;
  ar->InBufferBytes--;
  return c;
}

static inline void PutC(ARDATA *ar, byte c)
{
  ar->CBytesWritten++;
  if(ar->CBytesWritten <= 0x7ffa)
  {
    if(ar->FileOutPtr)
    {
      *ar->FileOutPtr = c;
      ar->FileOutPtr++;
    }
  }
}

static int BRead(ARDATA *ar, byte *p, word n)
{
  if(n>ar->InBufferBytes) n = ar->InBufferBytes;
  memcpy(p, ar->FileInPtr, n);
  ar->FileInPtr += n;
  ar->InBufferBytes -= n;
  return n;
}

static void BWrite(ARDATA *ar, byte *p, int n)
{
  if(ar->FileOutPtr)
  {
    memcpy(ar->FileOutPtr, p, n);
    ar->FileOutPtr += n;
  }
}

/**************************** Bit handling routines ***************************/

static void FillBuf(ARDATA *ar, word n)
{
  ar->BitBuf = ar->BitBuf<<n;
  while(n > ar->BitCount)
  {
    n -= ar->BitCount;
    ar->BitBuf |= ar->SubBitBuf<<n;
    if(ar->CompSize)
    {
      ar->CompSize--;
      ar->SubBitBuf = GetC(ar);
    }
    else
      ar->SubBitBuf = 0;
    ar->BitCount = 8;
  }
  ar->BitCount -= n;
  ar->BitBuf |= ar->SubBitBuf>>ar->BitCount;
}

static word GetBits(ARDATA *ar, short n)
{
  word g = ar->BitBuf>>(BITBUFSIZ-n);
  FillBuf(ar, n);
  return g;
}

static void PutBits(ARDATA *ar, word n, word x)
{
  if(n < ar->BitCount)
  {
    ar->BitCount -= n;
    ar->SubBitBuf |= x<<ar->BitCount;
  }
  else
  {
    n -= ar->BitCount;
    PutC(ar, ar->SubBitBuf | (x>>n));
    ar->CompSize++;
    if(n < 8)
    {
      ar->BitCount = 8-n;
      ar->SubBitBuf = x<<ar->BitCount;
    }
    else
    {
      PutC(ar, x>>(n-8));
      ar->CompSize++;
      ar->BitCount = 16-n;
      ar->SubBitBuf = x<<ar->BitCount;
    }
  }
}

static void InitGetBits(ARDATA *ar)
{
  ar->BitBuf = 0;
  ar->SubBitBuf = 0;
  ar->BitCount = 0;
  FillBuf(ar, BITBUFSIZ);
}

static void InitPutBits(ARDATA *ar)
{
  ar->BitCount = 8;
  ar->SubBitBuf = 0;
}

/******************************** Decompression *******************************/


static void MakeTable(ARDATA *ar, short nchar, ARPByte bitlen, word tablebits, ARPWord table)
{
  word count[17], weight[17];
  word start[18];
  ARPWord p;
  word i, k, len, ch, jutbits, avail;
  word nextcode, mask;

  for(i=1; i<=16; i++)
    count[i] = 0;
  for(i=0; i<nchar; i++)
    count[bitlen[i]]++;
  start[1] = 0;
  for(i=1; i<=16; i++)
    start[i+1] = start[i] + (count[i]<<(16-i));
  if(start[17])
  {
    ar->Failed = TRUE;
    return;
  }
  jutbits = 16-tablebits;
  for(i=1; i<=tablebits; i++)
  {
    start[i] >>= jutbits;
    weight[i] = 1<<(tablebits-i);
  }
  i = tablebits+1;
  while(i<=16)
  {
    weight[i] = 1<<(16-i);
    i++;
  }
  i = start[tablebits+1]>>jutbits;
  if(i)
  {
    k = 1<<tablebits;
    while(i != k)
    {
      table[i] = 0;
      i++;
    }
  }
  avail = nchar;
  mask = 1<<(15-tablebits);
  for(ch=0; ch<nchar; ch++)
  {
    len = bitlen[ch];
    if(len == 0)
      continue;
    k = start[len];
    nextcode = k+weight[len];
    if(len <= tablebits)
    {
      for(i=k; i<nextcode; i++)
        table[i] = ch;
    }
    else
    {
      p = &table[k>>jutbits];
      i = len-tablebits;
      while(i)
      {
        if(*p == 0)
        {
          ar->Right[avail] = 0;
          ar->Left[avail] = 0;
          *p = avail;
          avail++;
        }
        if(k & mask)
          p = &ar->Right[*p];
        else
          p = &ar->Left[*p];
        k <<= 1;
        i--;
      }
      *p = ch;
    }
    start[len] = nextcode;
  }
}

static void ReadPtLen(ARDATA *ar, short nn, short nbit, short ispecial)
{
  short i, c, n;
  word mask;
  n = GetBits(ar, nbit);
  if(n == 0)
  {
    c = GetBits(ar, nbit);
    for(i=0; i<nn; i++)
      ar->PtLen[i] = 0;
    for(i=0; i<256; i++)
      ar->PtTable[i] = c;
  }
  else
  {
    i = 0;
    while(i<n)
    {
      c = ar->BitBuf>>(BITBUFSIZ-3);
      if(c == 7)
      {
        mask = 1<<(BITBUFSIZ-4);
        while(mask & ar->BitBuf)
        {
          mask >>= 1;
          c++;
        }
      }
      if(c < 7)
        FillBuf(ar, 3);
      else
        FillBuf(ar, c-3);
      ar->PtLen[i] = c;
      i++;
      if(i == ispecial)
      {
        c = GetBits(ar,2)-1;
        while(c >= 0)
        {
          ar->PtLen[i] = 0;
          i++;
          c--;
        }
      }
    }
    while(i < nn)
    {
      ar->PtLen[i] = 0;
      i++;
    }
    MakeTable(ar, nn, ar->PtLen, 8, ar->PtTable);
  }
}

static void ReadCLen(ARDATA *ar)
{
  short i, c, n;
  word mask;
  n = GetBits(ar, CBIT);
  if(n == 0)
  {
    c = GetBits(ar, CBIT);
    for(i=0; i<NC; i++)
      ar->CLen[i] = 0;
    for(i=0; i<4096; i++)
      ar->CTable[i] = c;
  }
  else
  {
    i = 0;
    while(i < n)
    {
      c = ar->PtTable[ar->BitBuf>>(BITBUFSIZ-8)];
      if(c >= NT)
      {
        mask = 1<<(BITBUFSIZ-9);
        do
        {
          if(ar->BitBuf & mask)
            c = ar->Right[c];
          else
            c = ar->Left[c];
          mask >>= 1;
        } while (c>=NT);
      }
      FillBuf(ar, ar->PtLen[c]);
      if(c <= 2)
      {
        if(c == 1)
          c = 2+GetBits(ar, 4);
        else if (c == 2)
          c = 19+GetBits(ar, CBIT);
        while(c >= 0)
        {
          ar->CLen[i] = 0;
          i++;
          c--;
        }
      }
      else
      {
        ar->CLen[i] = c-2;
        i++;
      }
    }
    while(i < NC)
    {
      ar->CLen[i] = 0;
      i++;
    }
    MakeTable(ar, NC, ar->CLen, 12, ar->CTable);
  }
}

static word DecodeC(ARDATA *ar)
{
  word j, mask;
  if(ar->BlockSize == 0)
  {
    ar->BlockSize = GetBits(ar,16);
    ReadPtLen(ar, NT, TBIT, 3);
    if(ar->Failed)
      return 0;
    ReadCLen(ar);
    if(ar->Failed)
      return 0;
    ReadPtLen(ar, NP, PBIT, -1);
    if(ar->Failed)
      return 0;
  }
  ar->BlockSize--;
  j = ar->CTable[ar->BitBuf>>(BITBUFSIZ-12)];
  if(j >= NC)
  {
    mask = 1<<(BITBUFSIZ-13);
    do
    {
      if(ar->BitBuf & mask)
        j = ar->Right[j];
      else
        j = ar->Left[j];
      mask >>= 1;
    } while(j >= NC);
  }
  FillBuf(ar, ar->CLen[j]);
  return j;
}

static word DecodeP(ARDATA *ar)
{
  word j, mask;
  j = ar->PtTable[ar->BitBuf>>(BITBUFSIZ-8)];
  if(j >= NP)
  {
    mask = 1<<(BITBUFSIZ-9);
    do
    {
      if(ar->BitBuf & mask)
        j = ar->Right[j];
      else
        j = ar->Left[j];
      mask >>= 1;
    } while(j >= NP);
  }
  FillBuf(ar, ar->PtLen[j]);
  if(j)
  {
    j--;
    j = (1<<j)+GetBits(ar,j);
  }
  return j;
}

static void InitVars(ARDATA *ar)
{
  memset(ar, 0, sizeof(ARDATA));
}

static void DecodeBuffer(ARDATA *ar, word count, ARPByte arbuffer)
{
  word c, r;
  r = 0;
  ar->Decode_J--;
  while(ar->Decode_J >= 0)
  {
    arbuffer[r] = arbuffer[ar->Decode_I];
    ar->Decode_I = (ar->Decode_I+1) & (DICSIZ-1);
    r++;
    if(r == count) return;
    ar->Decode_J--;
  }
  while(TRUE)
  {
    c = DecodeC(ar);
    if(ar->Failed) return;
    if(c <= UCHARMAX)
    {
      arbuffer[r] = c;
      r++;
      if(r == count) return;
    }
    else
    {
      ar->Decode_J = c-(UCHARMAX+1-THRESHOLD);
      ar->Decode_I = (r-DecodeP(ar)-1) & (DICSIZ-1);
      ar->Decode_J--;
      while(ar->Decode_J >= 0)
      {
        arbuffer[r] = arbuffer[ar->Decode_I];
        ar->Decode_I = (ar->Decode_I+1) & (DICSIZ-1);
        r++;
        if(r == count) return;
        ar->Decode_J--;
      }
    }
  }
}

static void Decode(ARDATA *ar)
{
  int l;
  word a;
  byte dp[DICSIZ];
  // Initialize decoder variables
  InitGetBits(ar);
  ar->BlockSize = 0;
  ar->Decode_J = 0;
  l = ar->OrigSize;
  while(l > 0)
  {
    if(l > DICSIZ)
      a = DICSIZ;
    else
      a = l;
    DecodeBuffer(ar, a, dp);
    if(ar->Failed) return;
    BWrite(ar, dp, a);
    l -= a;
  }
}

/********************************* Compression ********************************/

// -------------------------------- Huffman part --------------------------------

static void CountLen(ARDATA *ar, short i, word *lencnt, short nparm)
{
  word depth = 0;
  short buf1[NC/2+1], buf2[NC/2+1];
  short *old = buf1, *new = buf2;
  int oldsz, newsz = 1;
  *new = i;
  while(newsz)
  {
    short *t = old;
    int n;
    // Swap old and new buffers
    old = new;     new = t;
    oldsz = newsz; newsz = 0;
    // Scan old, make new
    for(n = 0; n < oldsz; n++)
    {
      short j = old[n];
      if(j < nparm)
      {
        if(depth < 16)
          lencnt[depth]++;
        else
          lencnt[16]++;
      }
      else
      {
        new[newsz] = ar->Left[j];
        new[newsz+1] = ar->Right[j];
        newsz += 2;
      }
    }
    depth++;
  }
}

static void MakeLen(ARDATA *ar, short root, word *lencnt, byte *len, short nparm, ARPWord sortptr)
{
  short i, k;
  word cum;
  for(i=0; i<17; i++)
    lencnt[i] = 0;
  CountLen(ar, root, lencnt, nparm);
  cum = 0;
  for(i=16; i>0; i--)
    cum += lencnt[i]<<(16-i);
  while(cum)
  {
    lencnt[16]--;
    for(i=15; i>0; i--)
    {
      if(lencnt[i])
      {
        lencnt[i]--;
        lencnt[i+1] += 2;
        break;
      }
    }
    cum--;
  }
  for(i=16; i>0; i--)
  {
    k = lencnt[i]-1;
    while(k >= 0)
    {
      k--;
      len[*sortptr] = i;
      sortptr++;
    }
  }
}

static void DownHeap(word *heap, short i, short heapsize, ARPWord freqparm)
{
  short j, k;
  k = heap[i];
  j = i<<1;
  while(j <= heapsize)
  {
    if(j < heapsize && freqparm[heap[j]] > freqparm[heap[j+1]]) j++;
    if(freqparm[k] <= freqparm[heap[j]]) break;
    heap[i] = heap[j];
    i = j;
    j = i<<1;
  }
  heap[i] = k;
}

static void MakeCode(short n, ARPByte len, ARPWord code, word *lencnt)
{
  short i, k;
  word start[18];
  start[1] = 0;
  for(i=1; i<17; i++)
    start[i+1] = (start[i]+lencnt[i]) << 1;
  for(i=0; i<n; i++)
  {
    k = len[i];
    code[i] = start[k];
    start[k]++;
  }
}

static short MakeTree(ARDATA *ar, short nparm, ARPWord freqparm, byte *len, ARPWord codeparm)
{
  short i, j, k, avail;
  word lencnt[17];
  ARPWord sortptr;
  short heapsize = 0;
  word heap[NC+1];
  avail = nparm;
  heap[1] = 0;
  for(i=0; i<nparm; i++)
  {
    len[i] = 0;
    if(freqparm[i])
    {
      heapsize++;
      heap[heapsize] = i;
    }
  }
  if(heapsize < 2)
  {
    codeparm[heap[1]] = 0;
    return heap[1];
  }
  for(i=heapsize/2; i>0; i--) DownHeap(heap, i, heapsize, freqparm);
  sortptr = codeparm;
  do
  {
    i = heap[1];
    if(i < nparm)
    {
      *sortptr = i;
      sortptr++;
    }
    heap[1] = heap[heapsize];
    heapsize--;
    DownHeap(heap, 1, heapsize, freqparm);
    j = heap[1];
    if(j < nparm)
    {
      *sortptr = j;
      sortptr++;
    }
    k = avail;
    avail++;
    freqparm[k] = freqparm[i]+freqparm[j];
    heap[1] = k;
    DownHeap(heap, 1, heapsize, freqparm);
    ar->Left[k] = i;
    ar->Right[k] = j;
  } while(heapsize > 1);
  MakeLen(ar, k, lencnt, len, nparm, codeparm);
  MakeCode(nparm, len, codeparm, lencnt);
  return k;
}

static void CountTFreq(ARDATA *ar)
{
  short i, k, n, count;
  for(i = 0; i<NT; i++) ar->TFreq[i] = 0;
  n = NC;
  while(n>0 && ar->CLen[n-1] == 0)
  {
    n--;
  }
  i = 0;
  while(i < n)
  {
    k = ar->CLen[i];
    i++;
    if(k == 0)
    {
      count = 1;
      while(i<n && ar->CLen[i] == 0)
      {
        i++;
        count++;
      }
      if(count <= 2)
        ar->TFreq[0] += count;
      else if(count <= 18)
        ar->TFreq[1]++;
      else if(count == 19)
      {
        ar->TFreq[0]++;
        ar->TFreq[1]++;
      }
      else
        ar->TFreq[2]++;
    }
    else
      ar->TFreq[k+2]++;
  }
}

static void WritePtLen(ARDATA *ar, short n, short nbit, short ispecial)
{
  short i, k;
  while(n>0 && ar->PtLen[n-1] == 0) n--;
  PutBits(ar, nbit, n);
  i = 0;
  while(i < n)
  {
    k = ar->PtLen[i];
    i++;
    if(k <= 6)
      PutBits(ar, 3, k);
    else
    {
      k -= 3;
      PutBits(ar, k, (1<<k)-2);
    }
    if(i == ispecial)
    {
      while(i<6 && ar->PtLen[i] == 0) i++;
      PutBits(ar, 2, (i-3) & 3);
    }
  }
}

static void WriteCLen(ARDATA *ar)
{
  short i, k, n, count;
  n = NC;
  while(n>0 && ar->CLen[n-1] == 0) n--;
  PutBits(ar, CBIT, n);
  i = 0;
  while(i<n)
  {
    k = ar->CLen[i];
    i++;
    if(k == 0)
    {
      count = 1;
      while(i<n && ar->CLen[i] == 0)
      {
        i++;
        count++;
      }
      if(count <= 2)
      {
        for(k=0; k<count; k++)
          PutBits(ar, ar->PtLen[0], ar->PtCode[0]);
      }
      else if(count <= 18)
      {
        PutBits(ar, ar->PtLen[1], ar->PtCode[1]);
        PutBits(ar, 4, count-3);
      }
      else if(count == 19)
      {
        PutBits(ar, ar->PtLen[0], ar->PtCode[0]);
        PutBits(ar, ar->PtLen[1], ar->PtCode[1]);
        PutBits(ar, 4, 15);
      }
      else
      {
        PutBits(ar, ar->PtLen[2], ar->PtCode[2]);
        PutBits(ar, CBIT, count-20);
      }
    }
    else
      PutBits(ar, ar->PtLen[k+2], ar->PtCode[k+2]);
  }
}

static void EncodeC(ARDATA *ar, short c)
{
  PutBits(ar, ar->CLen[c], ar->CCode[c]);
}

static void EncodeP(ARDATA *ar, word p)
{
  word c, q;
  c = 0;
  q = p;
  while(q)
  {
    q >>= 1;
    c++;
  }
  PutBits(ar, ar->PtLen[c], ar->PtCode[c]);
  if(c > 1) PutBits(ar, c-1, p & (0xFFFF>>(17-c)));
}

static void SendBlock(ARDATA *ar)
{
  word i, k, flags, root, pos, size;
  flags = 0;
  root = MakeTree(ar, NC, ar->CFreq, ar->CLen, ar->CCode);
  size = ar->CFreq[root];
  PutBits(ar, 16, size);
  if(root >= NC)
  {
    CountTFreq(ar);
    root = MakeTree(ar, NT, ar->TFreq, ar->PtLen, ar->PtCode);
    if(root >= NT)
      WritePtLen(ar, NT, TBIT, 3);
    else
    {
      PutBits(ar, TBIT, 0);
      PutBits(ar, TBIT, root);
    }
    WriteCLen(ar);
  }
  else
  {
    PutBits(ar, TBIT, 0);
    PutBits(ar, TBIT, 0);
    PutBits(ar, CBIT, 0);
    PutBits(ar, CBIT, root);
  }
  root = MakeTree(ar, NP, ar->PFreq, ar->PtLen, ar->PtCode);
  if(root >= NP)
    WritePtLen(ar, NP, PBIT, -1);
  else
  {
    PutBits(ar, PBIT, 0);
    PutBits(ar, PBIT, root);
  }
  pos = 0;
  for(i=0; i<size; i++)
  {
    if((i & 7) == 0)
    {
      flags = ar->Buf[pos];
      pos++;
    }
    else
      flags <<= 1;
    if(flags & (1<<7))
    {
      k = ar->Buf[pos] + (1<<8);
      pos++;
      EncodeC(ar, k);
      k = ar->Buf[pos] << 8;
      pos++;
      k += ar->Buf[pos];
      pos++;
      EncodeP(ar, k);
    }
    else
    {
      k = ar->Buf[pos];
      pos++;
      EncodeC(ar, k);
    }
  }
  for(i=0; i<NC; i++) ar->CFreq[i] = 0;
  for(i=0; i<NP; i++) ar->PFreq[i] = 0;
}

static word Output(ARDATA *ar, word c, word p, word outputpos)
{
  ar->OutputMask >>= 1;
  if(ar->OutputMask == 0)
  {
    ar->OutputMask = 1<<7;
    if(outputpos >= WINDOWSIZE-24)
    {
      SendBlock(ar);
      outputpos = 0;
    }
    ar->CPos = outputpos;
    outputpos++;
    ar->Buf[ar->CPos] = 0;
  }
  ar->Buf[outputpos] = c;
  outputpos++;
  ar->CFreq[c]++;
  if(c >= (1<<8))
  {
    ar->Buf[ar->CPos] |= ar->OutputMask;
    ar->Buf[outputpos] = p>>8;
    outputpos++;
    ar->Buf[outputpos] = p;
    outputpos++;
    c = 0;
    while(p)
    {
      p >>= 1;
      c++;
    }
    ar->PFreq[c]++;
  }
  return outputpos;
}

//------------------------------- Lempel-Ziv part ------------------------------

static void InitSlide(ARDATA *ar)
{
  word i;
  for(i=DICSIZ; i<=DICSIZ+UCHARMAX; i++)
  {
    ar->Level[i] = 1;
#ifdef PERCOLATE
    ar->Position[i] = NUL;
#endif
  }
  for(i=DICSIZ; i<2*DICSIZ; i++) ar->Parent[i] = NUL;
  ar->Avail = 1;
  for(i=1; i<DICSIZ-1; i++) ar->Next[i] = i+1;
  ar->Next[DICSIZ-1] = NUL;
  for(i=2*DICSIZ; i<=MAXHASHVAL; i++) ar->Next[i] = NUL;
}

// Hash Function
static inline short Hash(short p, byte c)
{
  return p+(c<<(DICBIT-9))+2*DICSIZ;
}

static inline short Child(ARDATA *ar, short q, byte c)
{
  short r;
  r = ar->Next[Hash(q, c)];
  ar->Parent[NUL] = q;
  while(ar->Parent[r] != q) r = ar->Next[r];
  return r;
}

static inline void MakeChild(ARDATA *ar, short q, byte c, short r)
{
  short h, t;
  h = Hash(q, c);
  t = ar->Next[h];
  ar->Next[h] = r;
  ar->Next[r] = t;
  ar->Prev[t] = r;
  ar->Prev[r] = h;
  ar->Parent[r] = q;
  ar->ChildCount[q]++;
}

static void Split(ARDATA *ar, short old)
{
  short new, t;
  new = ar->Avail;
  ar->Avail = ar->Next[new];
  ar->ChildCount[new] = 0;
  t = ar->Prev[old];
  ar->Prev[new] = t;
  ar->Next[t] = new;
  t = ar->Next[old];
  ar->Next[new] = t;
  ar->Prev[t] = new;
  ar->Parent[new] = ar->Parent[old];
  ar->Level[new] = ar->MatchLen;
  ar->Position[new] = ar->Pos;
  MakeChild(ar, new, ar->Text[ar->MatchPos+ar->MatchLen], old);
  MakeChild(ar, new, ar->Text[ar->Pos+ar->MatchLen], ar->Pos);
}

static void InsertNode(ARDATA *ar)
{
  short q, r, j, t;
  byte c;
  ARPByte t1, t2;
  if(ar->MatchLen >= 4)
  {
    ar->MatchLen--;
    r = (ar->MatchPos+1) | DICSIZ;
    q = ar->Parent[r];
    while(q == NUL)
    {
      r = ar->Next[r];
      q = ar->Parent[r];
    }
    while(ar->Level[q] >= ar->MatchLen)
    {
      r = q;
      q = ar->Parent[q];
    }
    t = q;
#ifdef PERCOLATE
    while(ar->Position[t] < 0)
    {
      ar->Position[t] = ar->Pos;
      t = ar->Parent[t];
    }
    if(t < DICSIZ) ar->Position[t] = ar->Pos | PERCFLAG;
#else
    while(t < DICSIZ)
    {
      ar->Position[t] = ar->Pos;
      t = ar->Parent[t];
    }
#endif
  }
  else
  {
    q = ar->Text[ar->Pos]+DICSIZ;
    c = ar->Text[ar->Pos+1];
    r  = Child(ar, q, c);
    if(r == NUL)
    {
      MakeChild(ar, q, c, ar->Pos);
      ar->MatchLen = 1;
      return;
    }
    ar->MatchLen = 2;
  }
  while(TRUE)
  {
    if(r >= DICSIZ)
    {
      j = MAXMATCH;
      ar->MatchPos = r;
    }
    else
    {
      j = ar->Level[r];
      ar->MatchPos = ar->Position[r] & ~PERCFLAG;
    }
    if(ar->MatchPos >= ar->Pos) ar->MatchPos -= DICSIZ;
    t1 = &ar->Text[ar->Pos+ar->MatchLen];
    t2 = &ar->Text[ar->MatchPos+ar->MatchLen];
    while(ar->MatchLen < j)
    {
      if(*t1 != *t2)
      {
        Split(ar, r);
        return;
      }
      ar->MatchLen++;
      t1++;
      t2++;
    }
    if(ar->MatchLen >= MAXMATCH) break;
    ar->Position[r] = ar->Pos;
    q = r;
    r = Child(ar, q, *t1);
    if(r == NUL)
    {
      MakeChild(ar, q, *t1, ar->Pos);
      return;
    }
    ar->MatchLen++;
  }
  t = ar->Prev[r];
  ar->Prev[ar->Pos] = t;
  ar->Next[t] = ar->Pos;
  t = ar->Next[r];
  ar->Next[ar->Pos] = t;
  ar->Prev[t] = ar->Pos;
  ar->Parent[ar->Pos] = q;
  ar->Parent[r] = NUL;
  ar->Next[r] = ar->Pos;
}

static void DeleteNode(ARDATA *ar)
{
  word r, s, t, u;
#ifdef PERCOLATE
  short q;
#endif
  if(ar->Parent[ar->Pos] == NUL) return;
  r = ar->Prev[ar->Pos];
  s = ar->Next[ar->Pos];
  ar->Next[r] = s;
  ar->Prev[s] = r;
  r = ar->Parent[ar->Pos];
  ar->Parent[ar->Pos] = NUL;
  ar->ChildCount[r]--;
  if(r >= DICSIZ || ar->ChildCount[r] > 1) return;
#ifdef PERCOLATE
  t = ar->Position[r] & ~PERCFLAG;
#else
  t = ar->Position[r];
#endif
  if(t >= ar->Pos) t -= DICSIZ;
#ifdef PERCOLATE
  s = t;
  q = ar->Parent[r];
  u = ar->Position[q];
  while(u & PERCFLAG)
  {
    u &= ~PERCFLAG;
    if(u >= ar->Pos) u -= DICSIZ;
    if(u > s) s = u;
    ar->Position[q] = s | DICSIZ;
    q = ar->Parent[q];
    u = ar->Position[q];
  }
  if(q < DICSIZ)
  {
    if(u >= ar->Pos) u -= DICSIZ;
    if(u > s) s = u;
    ar->Position[q] = s | DICSIZ | PERCFLAG;
  }
#endif
  s = Child(ar, r, ar->Text[t+ar->Level[r]]);
  t = ar->Prev[s];
  u = ar->Next[s];
  ar->Next[t] = u;
  ar->Prev[u] = t;
  t = ar->Prev[r];
  ar->Next[t] = s;
  ar->Prev[s] = t;
  t = ar->Next[r];
  ar->Prev[t] = s;
  ar->Next[s] = t;
  ar->Parent[s] = ar->Parent[r];
  ar->Parent[r] = NUL;
  ar->Next[r] = ar->Avail;
  ar->Avail = r;
}

static void GetNextMatch(ARDATA *ar)
{
  short n;
  ar->Remainder--;
  ar->Pos++;
  if(ar->Pos == 2*DICSIZ)
  {
    memmove(&ar->Text[0], &ar->Text[DICSIZ], DICSIZ+MAXMATCH);
    n = BRead(ar, &ar->Text[DICSIZ+MAXMATCH], DICSIZ);
    ar->Remainder += n;
    ar->Pos = DICSIZ;
  }
  DeleteNode(ar);
  InsertNode(ar);
}

static int allocate_memory(ARDATA *ar)
{
  ar->Text = malloc(2*DICSIZ+MAXMATCH);
  ar->Level = malloc(DICSIZ+UCHARMAX+1);
  ar->ChildCount = malloc(DICSIZ+UCHARMAX+1);
#ifdef PERCOLATE
  ar->Position = malloc((DICSIZ+UCHARMAX+1) << 1);
#else
  ar->Position = malloc(DICSIZ << 1);
#endif
  ar->Parent = malloc((DICSIZ*2) << 1);
  ar->Prev = malloc((DICSIZ*2) << 1);
  ar->Next = malloc((MAXHASHVAL+1) << 1);

  ar->Buf = malloc(WINDOWSIZE);
  return ar->Buf != NULL;
}

#define FREEMEM(p) if(p) {free(p); p = NULL;}

static void free_memory(ARDATA *ar)
{
  FREEMEM(ar->Buf);
  FREEMEM(ar->Next);
  FREEMEM(ar->Prev);
  FREEMEM(ar->Parent);
  FREEMEM(ar->Position);
  FREEMEM(ar->Position);
  FREEMEM(ar->ChildCount);
  FREEMEM(ar->Level);
  FREEMEM(ar->Text);
}

static void Encode(ARDATA *ar)
{
  // initialize encoder variables
  if(!allocate_memory(ar))
  {
    TAP_Print("unable to allocate memory\n");
  }
  else
  {
    short lastmatchlen, lastmatchpos;
    word outputpos = 0;
    InitSlide(ar);
    ar->Buf[0] = 0;
    memset(ar->CFreq, 0, sizeof(ar->CFreq));
    memset(ar->PFreq, 0, sizeof(ar->PFreq));
    ar->OutputMask = 0;
    InitPutBits(ar);
    ar->Remainder = BRead(ar, &ar->Text[DICSIZ], DICSIZ+MAXMATCH);
    ar->MatchLen = 0;
    ar->Pos = DICSIZ;
    InsertNode(ar);
    if(ar->MatchLen > ar->Remainder) ar->MatchLen = ar->Remainder;
    while(ar->Remainder > 0)
    {
      lastmatchlen = ar->MatchLen;
      lastmatchpos = ar->MatchPos;
      GetNextMatch(ar);
      if(ar->MatchLen > ar->Remainder) ar->MatchLen = ar->Remainder;
      if(ar->MatchLen > lastmatchlen || lastmatchlen < THRESHOLD)
        outputpos = Output(ar, ar->Text[ar->Pos-1], 0, outputpos);
      else
      {
        outputpos = Output(ar, lastmatchlen+(UCHARMAX+1-THRESHOLD), (ar->Pos-lastmatchpos-2) & (DICSIZ-1), outputpos);
        lastmatchlen--;
        while(lastmatchlen > 0)
        {
          GetNextMatch(ar);
          lastmatchlen--;
        }
        if(ar->MatchLen > ar->Remainder) ar->MatchLen = ar->Remainder;
      }
    }
    // flush buffers
    SendBlock(ar);
    PutBits(ar, 7,0);
  }
  free_memory(ar);
}

word CompressBlock(byte *inputbuffer, word inputsize, byte *outputbuffer)
{
  if (!inputbuffer || inputsize > 0x7ffa)
    return 0;
  else
  {
    int compsize = 0;
    ARDATA *ar = malloc(sizeof(ARDATA));
    if(ar)
    {
      InitVars(ar);
      ar->FileInPtr = inputbuffer;
      ar->FileOutPtr = outputbuffer;
      ar->InBufferBytes = inputsize;
      Encode(ar);
      compsize = ar->CompSize;
      // Copy the Buffer If encoding failed
      if(compsize == 0 || ar->CBytesWritten > 0x7ffa)
      {
        if(outputbuffer) memcpy(outputbuffer, inputbuffer, inputsize);
        compsize = inputsize;
      }
      free(ar);
    }
    return compsize;
  }
}

word UncompressBlock(byte *inputbuffer, word inputsize, byte *outputbuffer, word outputsize)
{
  ARDATA *ar = malloc(sizeof(ARDATA));
  if(!ar)
    return 0;
  else
  {
    word failed;
    InitVars(ar);
    ar->FileInPtr = inputbuffer;
    ar->FileOutPtr = outputbuffer;
    ar->CompSize = inputsize;
    ar->InBufferBytes = inputsize;
    ar->OrigSize = outputsize;
    Decode(ar);
    failed = ar->Failed;
    free(ar);
    return !failed;
  }
}
