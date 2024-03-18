#include "include/main.h"
void error_exit(char *error_msg)
{
    printf("%s\n", error_msg);
    exit(1);
}

void unit_test()
{
    struct criterion_test_set *tests = criterion_initialize();
    int result = criterion_run_all_tests(tests);
    criterion_finalize(tests);
    (void)result;
    error_exit("TEST FONCTION");
}

#define UNIT_TEST 0
int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;
    if (UNIT_TEST == 1)
        unit_test();
    return (0);
}