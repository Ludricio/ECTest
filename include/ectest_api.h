#ifndef ECTEST_API__
#define ECTEST_API__

#define ECT_EXPORT_MODULE(module, X...)                                         \
        ECT_EXPORT_MODULE__(module, X)
    
#define ECT_TEST(test)                                                          \
        ECT_TEST__(test)
    
#define ECT_IMPORT_MODULE(module)                                               \
        ECT_IMPORT_MODULE__(module)
        
#endif /*ECTEST_API__*/

