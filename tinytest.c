#include "tinytest.h"

static int tt_passes = 0;
static int tt_fails = 0;
static int tt_current_test_failed = 0;
static const char *tt_current_msg = NULL;
static const char *tt_current_expression = NULL;
static const char *tt_current_file = NULL;
static int tt_current_line = 0;

void tt_execute(const char *name, void (*test_function)())
{
    tt_current_test_failed = 0;
    test_function();
    if (tt_current_test_failed)
    {
        printf("failure: %s:%d: In test %s():\n    %s (%s)\n",
               tt_current_file, tt_current_line, name, tt_current_msg, tt_current_expression);
        tt_fails++;
    }
    else
    {
        tt_passes++;
    }
}

int tt_assert(const char *file, int line, const char *msg, const char *expression, int pass)
{
    tt_current_msg = msg;
    tt_current_expression = expression;
    tt_current_file = file;
    tt_current_line = line;
    tt_current_test_failed = !pass;
    return pass;
}

void tt_reset(void)
{
    tt_passes = 0;
    tt_fails = 0;
    tt_current_test_failed = 0;
    tt_current_msg = NULL;
    tt_current_expression = NULL;
    tt_current_file = NULL;
    tt_current_line = 0;
}

int tt_report(void)
{
    int outcode = 0;

    if (tt_fails)
    {
        printf("%c%sFAILED%c%s [%s] (passed:%d, failed:%d, total:%d)\n",
               TT_COLOR_CODE, TT_COLOR_RED, TT_COLOR_CODE, TT_COLOR_RESET,
               tt_current_file, tt_passes, tt_fails, tt_passes + tt_fails);
        outcode = -1;
    }
    else
    {
        printf("%c%sPASSED%c%s [%s] (total:%d)\n",
               TT_COLOR_CODE, TT_COLOR_GREEN, TT_COLOR_CODE, TT_COLOR_RESET,
               tt_current_file, tt_passes);
    }

    tt_reset();

    return outcode;
}