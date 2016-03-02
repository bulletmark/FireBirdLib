#include                <ctype.h>
#include                "../libFireBird.h"

//Taken from GNU bash-4.3, strtrans.c

/* Convert STRING by expanding the escape sequences specified by the
   ANSI C standard.  If SAWC is non-null, recognize `\c' and use that
   as a string terminator.  If we see \c, set *SAWC to 1 before
   returning.  LEN is the length of STRING.  If (FLAGS&1) is non-zero,
   that we're translating a string for `echo -e', and therefore should not
   treat a single quote as a character that may be escaped with a backslash.
   If (FLAGS&2) is non-zero, we're expanding for the parser and want to
   quote CTLESC and CTLNUL with CTLESC.  If (flags&4) is non-zero, we want
   to remove the backslash before any unrecognized escape sequence. */

#define CTLESC          '\001'
#define CTLNUL          '\177'
#define ESC             '\033'
#define TOUPPER(c)      (islower(c) ? toupper(c) : (c))
#define TOCTRL(x)       (TOUPPER(x) & 037)
#define ISOCTAL(c)      ((c) >= '0' && (c) <= '7')
#define OCTVALUE(c)     ((c) - '0')
#define ISDIGIT(c)      ((c) >= '0' && (c) <= '9')
#define ISXDIGIT(c)     (ISDIGIT((c)) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))

#define HEXVALUE(c) \
  (((c) >= 'a' && (c) <= 'f') \
    ? (c)-'a'+10 \
    : (c) >= 'A' && (c) <= 'F' ? (c)-'A'+10 : (c)-'0')


char *ansicstr (char *string, int len, int flags, int *sawc, int *rlen)
{
  TRACEENTER();

  int                   c, temp;
  char                 *ret, *r, *s;

  if(rlen) *rlen = 0;
  if(sawc) *sawc = 0;

  if((string == 0) || (len == 0) || (*string == '\0'))
  {
    TRACEEXIT();
    return NULL;
  }

  ret = (char*)TAP_MemAlloc(4*len + 1);
  if(ret == NULL)
  {
    TRACEEXIT();
    return NULL;
  }

  for(r = ret, s = string; s && *s;)
  {
    c = *s++;
    if (c != '\\' || *s == '\0')
      *r++ = c;
    else
    {
      switch (c = *s++)
      {
        case 'a': c = '\a'; break;
        case 'v': c = '\v'; break;
        case 'b': c = '\b'; break;
        case 'e':
        case 'E': c = ESC; break;
        case 'f': c = '\f'; break;
        case 'n': c = '\n'; break;
        case 'r': c = '\r'; break;
        case 't': c = '\t'; break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        {
          if(flags & 1)
          {
            *r++ = '\\';
            break;
          }
        }
        /* no break */

        case '0':
        {
          /* If (FLAGS & 1), we're translating a string for echo -e (or
               the equivalent xpg_echo option), so we obey the SUSv3/
               POSIX-2001 requirement and accept 0-3 octal digits after
               a leading `0'. */
          temp = 2 + ((flags & 1) && (c == '0'));
          for (c -= '0'; ISOCTAL (*s) && temp--; s++)
            c = (c * 8) + OCTVALUE (*s);
          c &= 0xFF;
          break;
        }

        case 'x':     /* Hex digit -- non-ANSI */
        {
          if ((flags & 2) && *s == '{')
          {
            flags |= 16;    /* internal flag value */
            s++;
          }
          /* Consume at least two hex characters */
          for (temp = 2, c = 0; ISXDIGIT ((unsigned char)*s) && temp--; s++)
            c = (c * 16) + HEXVALUE (*s);

          /* DGK says that after a `\x{' ksh93 consumes ISXDIGIT chars
               until a non-xdigit or `}', so potentially more than two
               chars are consumed. */

          if (flags & 16)
          {
            for ( ; ISXDIGIT ((unsigned char)*s); s++)
              c = (c * 16) + HEXVALUE (*s);
            flags &= ~16;
            if (*s == '}')
              s++;
          }
          /* \x followed by non-hex digits is passed through unchanged */
          else if (temp == 2)
          {
            *r++ = '\\';
            c = 'x';
          }
          c &= 0xFF;
          break;
        }

        //case 'u':
        //case 'U':
        //{
        //  temp = (c == 'u') ? 4 : 8;  /* \uNNNN \UNNNNNNNN */
        //
        //  for(v = 0; ISXDIGIT((byte)*s) && temp--; s++)
        //    v = (v * 16) + HEXVALUE(*s);
        //
        //  if(temp == ((c == 'u') ? 4 : 8))
        //  {
        //    *r++ = '\\';  /* c remains unchanged */
        //    break;
        //  }
        //  else if(v <= 0x7f) /* <= 0x7f translates directly */
        //  {
        //    c = v;
        //    break;
        //  }
        //  else
        //  {
        //    temp = u32cconv(v, r);
        //    r += temp;
        //    continue;
        //  }
        //}

        case '\\':
          break;

        case '\'':
        case '"':
        case '?':
        {
          if(flags & 1)
            *r++ = '\\';
          break;
        }

        case 'c':
        {
          if(sawc)
          {
            *sawc = 1;
            *r = '\0';
            if(rlen) *rlen = r - ret;
            return ret;
          }
          else if((flags & 1) == 0 && *s == 0)
            ;   /* pass \c through */
          else if((flags & 1) == 0 && (c = *s))
          {
            s++;
            if((flags & 2) && c == '\\' && c == *s)
              s++;  /* Posix requires $'\c\\' do backslash escaping */
            c = TOCTRL(c);
            break;
          }
        }
        /* no break */

        default:
        {
          if((flags & 4) == 0)
            *r++ = '\\';
          break;
        }
      }

      if ((flags & 2) && (c == CTLESC || c == CTLNUL))
        *r++ = CTLESC;
      *r++ = c;
    }
  }

  *r = '\0';
  if(rlen) *rlen = r - ret;

  TRACEEXIT();
  return ret;
}
