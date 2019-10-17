#include <ectest_master.h>

void tg_test1()
{
    printf("test1\n");
}

void tg_test2()
{
   printf("test2\n");
}


void tg_modsetup()
{
    printf("modsetup\n");
}

void tg_modteardown()
{
    printf("modteardown\n");
}

void tg_testsetup()
{
    printf("testsetup\n");
}

void tg_testteardown()
{
    printf("testteardown\n");
}

ect_export_module(test_module,
    ect_test(tg_test1),
    ect_test(tg_test2),
    ect_module_setup(tg_modsetup),
    ect_module_teardown(tg_modteardown),
    ect_test_setup(tg_testsetup),
    ect_test_teardown(tg_testteardown)
);
