/**
 *  @file csvreader.c
 *  @version 0.1.1-dev0
 *  @date Wed Jan  1 21:33:23 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "varstr.h"
#include "stringer.h"
#include "csvreader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/* Swallow characters represented in s */
static void
_gobble(FILE *in, char *s)
{
   while (1) {
      int c = fgetc(in);
      if (_IS_NULL(strchr(s, c))) {
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
   struct stringer *fields;
   enum states state;
   FILE       *in;
   struct varstr *tmp;
};

struct csvreader *
csvreader_new(char *fname)
{
   struct csvreader *tp;

   tp = (struct csvreader *) malloc(sizeof(struct csvreader));
   if (_IS_NULL(tp))
      return NULL;

   tp->x = NULL;
   tp->fields = stringer_new();
   tp->state = s_at_start;

   if (_IS_NULL(fname))
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
   stringer_free(&(*pp)->fields);
   _FREE(*pp);
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
   return "0.1.1-dev0";
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

#undef  _IS_NULL
#undef  _FREE
