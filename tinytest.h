/* TinyTest: A really really really tiny and simple no-hassle C unit-testing framework.
 *
 * Features:
 *   - No library dependencies. Not even itself. Just a header file.
 *   - Simple ANSI C. Should work with virtually every C or C++ compiler on
 *     virtually any platform.
 *   - Reports assertion failures, including expressions and line numbers.
 *   - Stops test on first failed assertion.
 *   - ANSI color output for maximum visibility.
 *   - Easy to embed in apps for runtime tests (e.g. environment tests).
 *
 * Example Usage:
 *
 *    #include "tinytest.h"
 *    #include "mylib.h"
 *
 *    void test_sheep()
 *    {
 *      ASSERT("Sheep are cool", are_sheep_cool());
 *      ASSERT_EQUALS(4, sheep.legs);
 *    }
 *
 *    void test_cheese()
 *    {
 *      ASSERT("Cheese is tangy", cheese.tanginess > 0);
 *      ASSERT_STRING_EQUALS("Wensleydale", cheese.name);
 *    }
 *
 *    int main()
 *    {
 *      RUN(test_sheep);
 *      RUN(test_cheese);
 *      return TEST_REPORT();
 *    }
 *
 * To run the tests, compile the tests as a binary and run it.
 *
 * Project home page: http://github.com/joewalnes/tinytest
 * Project home page: https://github.com/anaximeno/tinytest
 *
 * 2010, -Joe Walnes <joe@walnes.com> http://joewalnes.com
 * 2022, -Anaxímeno Brito <anaximenobrito@gmail.com> https://github.com/anaximeno
 */

#ifndef _TINYTEST_INCLUDED
#define _TINYTEST_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* Main assertion method */
#define ASSERT(msg, expression)                                                   \
  if (!tt_assert(__FILE__, __LINE__, (msg), (#expression), (expression) ? 1 : 0)) \
  return

/* Convenient assertion methods */
/* TODO: Generate readable error messages for assert_equals or assert_str_equals */
#define ASSERT_EQUALS(expected, actual) ASSERT((#actual), (expected) == (actual))
#define ASSERT_NOT_EQUALS(expected, actual) ASSERT((#actual), (expected) != (actual))
#define ASSERT_STRING_EQUALS(expected, actual) ASSERT((#actual), strcmp((expected), (actual)) == 0)
#define ASSERT_STRING_NOT_EQUALS(expected, actual) ASSERT((#actual), strcmp((expected), (actual)) != 0)

#define ASSERT_EQ(expected, actual) ASSERT_EQUALS(expected, actual)
#define ASSERT_NE(expected, actual) ASSERT_NOT_EQUALS(expected, actual)
#define ASSERT_STR_EQ(expected, actual) ASSERT_STRING_EQUALS(expected, actual)
#define ASSERT_STR_NE(expected, actual) ASSERT_STRING_EQUALS(expected, actual)

/* Run a test() function */
#define RUN(test_function) tt_execute((#test_function), (test_function))
#define TEST_REPORT() tt_report()

#define TT_COLOR_CODE 0x1B
#define TT_COLOR_RED "[1;31m"
#define TT_COLOR_GREEN "[1;32m"
#define TT_COLOR_RESET "[0m"

void tt_execute(const char *name, void (*test_function)());

int tt_assert(const char *file, int line, const char *msg, const char *expression, int pass);

void tt_reset(void);

int tt_report(void);

#endif
