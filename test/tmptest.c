#include "ectest.h"

ECT_DECL_MODULE_SETUPS(ECT_NO_SETUP);
ECT_DECL_MODULE_TEARDOWNS(ECT_NO_TEARDOWN);
ECT_DECL_TEST_SETUPS(ECT_NO_SETUP);
ECT_DECL_TEST_TEARDOWNS(ECT_NO_TEARDOWN);
ECT_DECL_TESTS(
    success,
    successWithMacro,
    skip,
    fail
);

ECT_TEST(success)
{

}

ECT_TEST(successWithMacro)
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

ECT_EXPORT_MODULE(TestModule);
