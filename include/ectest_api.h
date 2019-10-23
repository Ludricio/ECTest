#ifndef ECTEST_API__
#define ECTEST_API__

/*
 * CPPTOKEN: 
 *      Marks where a C Preprocessor valid token should be passed as an
 *      an argument to a macro.
 * 
 * TYPE: 
 *      Marks where a generic type can be passed as an argument
 *      to a macro.
 *
 * ect_export_module(CPPTOKEN module, void (*functions)(void)...)
 * 
 * ect_test(void (*function)(void))
 * 
 * ect_module_setup(void (*function)(void))
 * 
 * ect_module_teardown(void (*function)(void))
 * 
 * ect_test_setup(void (*function)(void))
 * 
 * ect_test_teardown(void (*function)(void))
 * 
 * ect_import_module(void (*module)(void))
 * 
 * ect_suite_new(CPPTOKEN suitename, void (*modules)(void)...)
 * 
 * ect_suite_free(ect_suite *suite)
 * 
 * ECT_SIZEOF_ARRAY(TYPE array[])
 * 
 * ECT_ARRAY_FOREACH(TYPE item, TYPE array[], size_t size)
 */  

#endif /*ECTEST_API__*/








