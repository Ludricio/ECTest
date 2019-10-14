#ifndef ECTEST_API__
#define ECTEST_API__

#define ECT_EXPORT_MODULE(module, functions...)                                 \
        ECT_EXPORT_MODULE__(module, functions)
    
#define ECT_TEST(func)                                                          \
        ECT_TEST__(func)

#define ECT_TEST_MODSETUP(func)                                                 \
        ECT_TEST_MODSETUP__(func)

#define ECT_TEST_MODTEARDOWN(func)                                              \
        ECT_TEST_MODTEARDOWN__(func)

#define ECT_TEST_SETUP(func)                                                    \
        ECT_TEST_SETUP__(func)

#define ECT_TEST_TEARDOWN(func)                                                 \
        ECT_TEST_TEARDOWN__(func)
    
#define ECT_IMPORT_MODULE(module)                                               \
        ECT_IMPORT_MODULE__(module)
        
#define ECT_SUITE_NEW(suitname, modules...)                                      \
        ECT_SUITE_NEW__(suitname, modules)

#define ECT_SUITE_FREE(suit)                                                     \
        ect_suite_free(suit)         
        
        
#define ECT_SIZEOF_ARRAY(array)                                                 \
        ECT_SIZEOF_ARRAY__(array)

#define ECT_ARRAY_FOREACH(item, array, size)                                    \
        ECT_ARRAY_FOREACH__(item, array, size)   

#endif /*ECTEST_API__*/

