/**
 *  @file csvreader.c
 *  @version 0.0.2-dev0
 *  @date Fri Dec  6 22:26:40 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "varstr.h"
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
   int         c;

   while (1) {
      c = fgetc(in);
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
   unsigned    nfields;
   char      **fields;
   enum states state;
   FILE       *in;
   struct varstr *tmp;
};

/*** csvreader_new() ***/

struct csvreader *
csvreader_new(char *fname)
{
   struct csvreader *tp;

   tp = (struct csvreader *) malloc(sizeof(struct csvreader));
   if (_IS_NULL(tp))
      return NULL;

   tp->x = NULL;
   tp->nfields = 0;
   tp->fields = NULL;
   tp->state = s_at_start;

   if (_IS_NULL(fname))
      tp->in = stdin;

   else
      tp->in = fopen(fname, "r");

   tp->tmp = varstr_new();

   return tp;
}

/*** csvreader_free() ***/

void
csvreader_free(struct csvreader *p)
{

   varstr_free(p->tmp);
   _FREE(p);
}

/*** csvreader_init() ***/

int
csvreader_init(struct csvreader *p, void *x)
{

   /* Do some magic here ... */
   p->x = x;                                     /* FIXME */

   return 0;
}

/*** csvreader_version() ***/

const char *
csvreader_version(void)
{
   return "0.0.2-dev0";
}

/*** csvreader_next() ***/

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
