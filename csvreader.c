/**
 *  @file csvreader.c
 *  @version 0.2.0-dev0
 *  @date Sun Feb 16, 2020 04:31:33 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "varstr.h"
#include "sbuf.h"
#include "csvreader.h"

#ifdef  IS_NULL
#undef  IS_NULL
#endif
#define IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  FREE
#undef  FREE
#endif
#define FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/* Swallow characters represented in s */
static void
_gobble(FILE *in, char *s)
{
   while (1) {
      int         c = fgetc(in);
      if (IS_NULL(strchr(s, c))) {
         ungetc(c, in);                          /* not in the list, replace */
         return;
      }
   }
}

enum states { s_at_start, s_at_end, s_in_comment, s_in_quoted_field,
   s_in_unquoted_field
};

struct csvreader {
   void       *x;
   struct sbuf *fields;
   enum states state;
   FILE       *in;
   struct varstr *tmp;
};

struct csvreader *
csvreader_new(char *fname)
{
   struct csvreader *tp;

   tp = (struct csvreader *) malloc(sizeof(struct csvreader));
   if (IS_NULL(tp))
      return NULL;

   tp->x = NULL;
   tp->fields = sbuf_new();
   tp->state = s_at_start;

   if (IS_NULL(fname))
      tp->in = stdin;

   else
      tp->in = fopen(fname, "r");

   tp->tmp = varstr_new();

   return tp;
}

void
csvreader_free(struct csvreader **pp)
{

   varstr_free(&(*pp)->tmp);
   sbuf_free(&(*pp)->fields);
   FREE(*pp);
   *pp = NULL;
}

int
csvreader_init(struct csvreader *p, void *x)
{

   /* Do some magic here ... */
   p->x = x;                                     /* FIXME */

   return 0;
}

const char *
csvreader_version(void)
{
   return "0.2.0-dev0";
}

int
csvreader_next(struct csvreader *p, unsigned *n, char ***cpp)
{
   unsigned    rc = 1;
   int         c;

   varstr_empty(p->tmp);

   if (p->state == s_at_end)
      return 0;

   while ((c = fgetc(p->in)) > 0) {
      switch (p->state) {
         case s_at_start:
            break;
         case s_at_end:
            break;
         case s_in_comment:
            break;
         case s_in_quoted_field:
            break;
         case s_in_unquoted_field:
            break;
         default:
            break;
      }
   }

   return 0;
}

#undef  IS_NULL
#undef  FREE
