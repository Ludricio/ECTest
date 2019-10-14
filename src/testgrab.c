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

ECT_EXPORT_MODULE(test_module,
    ECT_TEST(tg_test1),
    ECT_TEST(tg_test2),
    ECT_TEST_MODSETUP(tg_modsetup),
    ECT_TEST_MODTEARDOWN(tg_modteardown),
    ECT_TEST_SETUP(tg_testsetup),
    ECT_TEST_TEARDOWN(tg_testteardown)
);
