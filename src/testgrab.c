#include <ectest_master.h>

void tg_testgrab()
{
    printf("yo mother fucker\n");
    float x = 2/0;
}

void tg_test()
{
   printf("ASDASDASD\n");
}

ECT_EXPORT_MODULE(module,
    ECT_TEST(tg_testgrab),
    ECT_TEST(tg_test)
);