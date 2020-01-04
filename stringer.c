/**
 *  @file stringer.c
 *  @version 0.3.0-dev0
 *  @date Tue Dec 31 08:51:02 CST 2019
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "stringer.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct stringer {
   void       *x;
   char       *buffer;
   char      **list;
   size_t      next;
   size_t      count;
};

struct stringer *
stringer_new(void)
{
   struct stringer *tp;

   tp = (struct stringer *) malloc(sizeof(struct stringer));
   if (_IS_NULL(tp))
      return NULL;

   tp->buffer = NULL;
   tp->list = NULL;
   tp->next = 0;
   tp->count = 0;

   return tp;
}

void
stringer_free(struct stringer **pp)
{
   _FREE((*pp)->buffer);
   _FREE((*pp)->list);
   _FREE(*pp);
   *pp = NULL;
}

const char *
stringer_version(void)
{
   return "0.3.0-dev0";
}

int
stringer_empty(struct stringer *p)
{
   p->next = 0;
   p->count = 0;
   return 0;
}

int
stringer_insert(struct stringer *p, char *s)
{
   if (_IS_NULL(s))
      return 1;
   else {
      size_t      need = p->next + strlen(s) + 1;
      char       *tp = realloc(p->buffer, need * sizeof(char));
      if (_IS_NULL(tp))
         return 0;
      else {
         p->buffer = tp;
         strcpy(p->buffer + p->next, s);
         p->next = need;
         p->count += 1;
         return 1;
      }
   }
}

#if 0
char      **
stringer_strings(struct stringer *p)
{
   unsigned    i, j;
   unsigned    k = 0;

   p->list = realloc(p->list, p->count * sizeof(char *));

   i = 0;
   j = 0;
   while (k < p->count) {
      if (p->buffer[j] == '\0') {
         (p->list)[k] = p->buffer + i;
         j++;
         k++;
         i = j;
      }
      else
         j++;
   }

   return p->list;
}
#endif

int
stringer_strings(struct stringer *p, unsigned *n, char ***cpp)
{
   unsigned    i = 0, j = 0, k = 0;

   /* TODO next has p->count + 1 to allow tacking on a trailing NULL */
   p->list = realloc(p->list, (p->count + 1) * sizeof(char *));
   if (_IS_NULL(p->list))
      return 1;

   while (k < p->count) {
      if (p->buffer[j] == '\0') {
         (p->list)[k] = p->buffer + i;
         j++;
         k++;
         i = j;
      }
      else
         j++;
   }

   (p->list)[p->count] = NULL;
   *n = p->count;
   *cpp = (0 == p->count ? NULL : p->list);

   return 0;
}

#undef  _IS_NULL
#undef  _FREE
