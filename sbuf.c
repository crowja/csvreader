/**
 *  @file sbuf.c
 *  @version 0.5.2-dev0
 *  @date Sun Jan  5 21:31:55 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 *  @brief Methods for creating and parsing a buffer of strings.
 *  @details Probably mostly useful for lexers building up a buffer of text
 *  one character at a time. Sbuf_putc() collects characters and sbuf_strings()
 *  returns a list of embedded strings. A goal in this implementation has been
 *  to minimize mallocs and frees.
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME when printf() is gone */
#include "sbuf.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/* Character buffer size extensions */
#ifdef  _EXTEND_BUFSZ
#undef  _EXTEND_BUFSZ
#endif
#define _EXTEND_BUFSZ  1024

/* Character pointer array size extensions, > 1 */
#ifdef  _EXTEND_LSTSZ
#undef  _EXTEND_LSTSZ
#endif
#define _EXTEND_LSTSZ  1024

struct sbuf {
   char      **list;                        /* the array of pointers to strings */
   size_t      lsize;                       /* malloced size of list */
   char       *buffer;                      /* the array of chars */
   size_t      bsize;                       /* malloced size of buffer */
   unsigned    next;                        /* next buffer position to to write to */
};

struct sbuf *
sbuf_new(void)
{
   struct sbuf *tp;

   tp = (struct sbuf *) malloc(sizeof(struct sbuf));
   if (_IS_NULL(tp))
      return NULL;

   tp->list = NULL;
   tp->lsize = 0;
   tp->buffer = NULL;
   tp->bsize = 0;
   tp->next = 0;

   return tp;
}

void
sbuf_free(struct sbuf **pp)
{
   _FREE((*pp)->list);
   _FREE((*pp)->buffer);
   _FREE(*pp);
   *pp = NULL;
}

const char *
sbuf_version(void)
{
   return "0.5.2-dev0";
}

int
sbuf_putc(struct sbuf *p, int c)
{
   /* More space for the buffer? */
   if (p->next + 2 > p->bsize) {
      char       *tp = realloc(p->buffer, sizeof(char) * (p->bsize + _EXTEND_BUFSZ));
      if (_IS_NULL(tp))
         return EOF;                             /* FIXME */
      p->buffer = tp;
      p->bsize += _EXTEND_BUFSZ;
   }

   (p->buffer)[p->next] = c;

   p->next++;

   return c;
}

int
sbuf_reset(struct sbuf *p)
{
   p->next = 0;
   return 0;
}

int
sbuf_strings(struct sbuf *p, unsigned *n, char ***cpp)
{
   unsigned    i = 0, j = 0;                /* span each string */
   unsigned    k = 0;                       /* count strings */

   if (p->next == 0) {
      *n = 0;
      *cpp = NULL;
      return 0;
   }

   if (p->lsize == 0) {
      char      **tp;
      tp = realloc(p->list, sizeof(char *) * _EXTEND_LSTSZ);
      p->list = tp;
      p->lsize = _EXTEND_LSTSZ;
   }

   while (j < p->next) {
      if ((p->buffer)[j] == '\0') {              /* end of string */
         if (k + 2 >= p->lsize) {                /* need to extend p->list? */
            char      **tp;
            tp = realloc(p->list, sizeof(char *) * (p->lsize + _EXTEND_LSTSZ));
            /* FIXME assuming success */
            p->list = tp;
            p->lsize += _EXTEND_LSTSZ;
         }

         (p->list)[k] = p->buffer + i;
         j++;
         k++;
         i = j;
      }
      else
         j++;
   }

   (p->list)[k] = (char *) NULL;                 /* terminal NULL */
   *n = k;
   *cpp = (0 == k ? NULL : p->list);

   return 0;
}

#undef _EXTEND_BUFSZ
#undef _EXTEND_LSTSZ
#undef _IS_NULL
#undef _FREE
