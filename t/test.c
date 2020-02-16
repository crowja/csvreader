#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "csvreader.h"
#include "t/tinytest.h"

#ifdef  COLOR_CODE
#undef  COLOR_CODE
#endif
#define COLOR_CODE       0x1B

#ifdef  COLOR_RED
#undef  COLOR_RED
#endif
#define COLOR_RED        "[1;31m"

#ifdef  COLOR_GREEN
#undef  COLOR_GREEN
#endif
#define COLOR_GREEN      "[1;32m"

#ifdef  COLOR_YELLOW
#undef  COLOR_YELLOW
#endif
#define COLOR_YELLOW     "[1;33m"

#ifdef  COLOR_RESET
#undef  COLOR_RESET
#endif
#define COLOR_RESET      "[0m"


static void
printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", COLOR_CODE, COLOR_YELLOW, name, COLOR_CODE, COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}

static int
two_doubles_equal(double x, double y)
{
   double      t = fabs(x) + fabs(y);
   return fabs(x - y) < 4 * DBL_EPSILON * t ? 1 : 0;
}

static void
test_constr(void)
{
   struct csvreader *z;

   printf_test_name("test_constr", "csvreader_new, csvreader_free");

   z = csvreader_new(NULL);
   ASSERT("Constructor test", z);
   csvreader_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 15 yy */
static void
test_stub(void)
{
   struct csvreader *z;
   double      x = 1.23;                    /* TODO */

   printf_test_name("test_stub", NULL);

   z = csvreader_new(NULL);
   ASSERT("Constructor test, pt 1", z);
   ASSERT("Here's a test ...", two_doubles_equal(x, 1.23));

   csvreader_free(&z);
   ASSERT_EQUALS(NULL, z);
}
#endif


int
main(void)
{
   printf("%s\n", csvreader_version());

   RUN(test_constr);

   return TEST_REPORT();
}
