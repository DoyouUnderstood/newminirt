#include "include/main.h"
void error_exit(char *error_msg)
{
    printf("%s\n", error_msg);
    exit(1);
}

int main(int argc, char *argv[]) 
{
    (void)argc;
    (void)argv;

    struct criterion_test_set *tests = criterion_initialize();
    int result = criterion_run_all_tests(tests);
    criterion_finalize(tests);

    return result;
}