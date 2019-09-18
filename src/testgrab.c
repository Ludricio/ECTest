#include <ectest_master.h>

void tg_testgrab()
{
    printf("yo mother fucker\n");
}

void tg_test()
{
   printf("ASDASDASD\n");
}

ECT_EXPORT_MODULE(module,
    ECT_TEST(tg_testgrab),
    ECT_TEST(tg_test)
);
