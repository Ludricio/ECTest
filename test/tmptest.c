#include "ectest.h"

ECT_DECLARE_AFTER_MODULE(ECT_NO_TEARDOWN);
ECT_DECLARE_AFTER_TEST(ECT_NO_TEARDOWN);
ECT_DECLARE_BEFORE_MODULE(ECT_NO_SETUP);
ECT_DECLARE_BEFORE_TEST(ECT_NO_SETUP);
ECT_DECLARE_TESTS(
    success,
    skip,
    fail
);

ECT_TEST(success)
{
    ECT_SUCCESS();
}

ECT_TEST(skip)
{
    ECT_SKIP();
}

ECT_TEST(fail)
{
    ECT_FAIL("Failed");
}

ECT_EXPORT_MODULE(TestModule)

ect_module *TestModule_import();
