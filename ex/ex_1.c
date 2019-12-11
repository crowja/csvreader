#include <stdlib.h>
#include <stdio.h>
#include "csvreader.h"

int
main(void)
{
   char      **cpp;
   unsigned    n;
   struct csvreader *r = csvreader_new(NULL);

   while (csvreader_next(r, &n, &cpp)) {
      printf("%d fields\n", n);
   }

   csvreader_free(&r);

   return 0;
}
