#ifndef _ECTEST_H__
#define _ECTEST_H__

/*TODO FOR TEST FRAMEWORK
 *
 * 1. increase number of TEST_ARG_N__ and TEST_RSEQ_N__ instances.
 * 2. increase number of TEST_EXPORT_FUNC__ and TEST_DECLEXPORT_FUNC__ iterations.
 * 4. Write quick doc for how to setup testing modules. (readme)
 * 5. Setup CI
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file ectest.h
 * @brief Contains everything needed for use of the ECTest testing framework.
 *
 * This files contains all macros, data structures and functionality that make up the ECTest testing framework.
 * To use ECTest, include this file and utilize the macros defined under the public section.
 *
 * @note Do not use anything under the internal section, those are for internal usage of the ECTest implementation.
 * Use of internal macros, functions or data structures within test modules and runners are considered undefined
 * behaviour in the context of the ECTest testing framework. Functionality under the internal section may be changed
 * at any time without notification, unless the changes affect the public interfaces.
 */

/* COMPILE DEFINE INFO
 *
 * ETC_ABORT_ON_FAIL
 * To abort testing upon test case failure, compile with -DETC_ABORT_ON_FAIL=1
 *
 * ECT_LOG_LEVEL
 * Choose what level of test completion logging should be done (success/skipped/failed).
 * Compile with -DETC_LOG_LEVEL=3 for all (default)
 * Compile with -DETC_LOG_LEVEL=2 for failed and skipped only.
 * Compile with -DETC_LOG_LEVEL=1 for failed only.
 * Compile with -DETC_LOG_LEVEL=0 for only module run notifications and summaries.
 */

/* PUBLIC
 *
 * This section contains macros for public use within test modules and runners.
 *
 * Some macros have a variant that is provides a @ref printf style format string, and takes a variable amount of
 * arguments, instead of a fixed message. These macros has the same name as their fixed message equivalents, with the
 * exception that they start with ECT_F<rest of name> instead of ECT_<rest of name>. These macros are not documented
 * as they follow the same behaviour as their fixed message equivalents.
 *
 * Only use macros within this section when writing tests, the usage of macros/functions/data structures under the
 * internal section is considered undefined behaviour in the context of using the ECTest testing framework.
 */

/**
 * @defgroup TESTRUNCREATE Test Module Runner macros
 * @brief These macros are used to create test module runners.
 * @{
 */
/**
 * @def ECT_RUNNER(...)
 * @brief A full pre-implemented test module runner.
 * @param ... The names of the test modules to import and run. (Do not quote as strings)
 *
 * A full pre-implemented test module runner, combining the usage of @ref ECT_IMPORT_MODULES, @ref ECT_RUNNER_START,
 * @ref ECT_RUN_MODULE (for each module) and @ref ECT_RUNNER_END. This macro will generate a test program entry point,
 * i.e. a @c main function.
 *
 * @note It is preferred that this macro be used to create test module runners, unless custom run behaviour is needed.
 */
#define ECT_RUNNER() ECT_RUNNER__()

typedef struct {
    struct ect_stack__ *modules;
    struct ect_stack__ *results;
}ect_testsuite;

static inline ect_testsuite *ect_testsuite_create();
static inline void ect_testsuite_destroy(void *testsuite);
static inline void ect_export_results(ect_testsuite *testsuite);

#define ECT_PREPARE_MODULES(testsuite) ECT_PREPARE_MODULES__(testsuite)

#define ECT_RUN_TESTSUITE(testsuite) ECT_RUN_TESTSUITE__(testsuite)

#define ECT_EXECUTE_MODULE(module, resultstack, abortrun) ECT_EXECUTE_MODULE__(module, resultstack, abortrun)

#define ECT_EVAL_TESTRUN(resultstack, abortrun) ECT_EVAL_TESTRUN__(resultstack, abortrun)

/**
 *  @def ECT_IMPORT_MODULES(...)
 *  @brief Imports test modules, making them visible within a test runner.
 *  @param ... The names of the modules to import (Do not quote as strings)
 *  @note Modules must be imported before the definition of the test program entry point, i.e. the @c main function.
 */
#define ECT_IMPORT_MODULES(...) ECT_IMPORT_MODULES__(__VA_ARGS__)

/**@}*/

/**
 * @defgroup TESTMODCREATE Test Module Macros
 * @brief Macros for defining test module components.
 * @{
 */
 /**
  * @ðef ECT_EXPORT_MODULE(modulename)
  * @brief Exports the module, along with all declared tests/setups/teardowns, making it visible for test runners.
  * @param modulename The name of the module. (Do not quote as string)
  *
  * Exports the module, making it visible for external usage. This is required within a test module to make it a valid
  * test module, since test runners won't be able to use it else. Must occur AFTER test/setup/teardown declarations.
  */
#define ECT_EXPORT_MODULE(modulename) ECT_EXPORT_MODULE__(modulename)

/**
 * @defgroup TESTDECL Test Function Declaration Macros
 * @{
 */
/**
 * @def ECT_DECL_TESTS(...)
 * @brief Declares which tests in the test module should be visible to test runners.
 * @param ... The names of the tests (Do not quote as strings)
 * @note This macro is required in a valid test module, and should be placed before @ref ECT_EXPORT_MODULE.
 */
#define ECT_DECL_TESTS(...) ECT_DECL_TESTS__(__VA_ARGS__)

/**
 * @def ECT_DECL_MODULE_SETUPS(...)
 * @brief Declares which module setups in the test module should be visible to test runners.
 * @param ... The names of the module setups. (Do not quote as strings)
 * @note This macro is required in a valid test module, and should be placed before @ref ECT_EXPORT_MODULE.
 * @note If no module setups is to be used, supply @ref ECT_NO_SETUP as argument.
 */
#define ECT_DECL_MODULE_SETUPS(...) ECT_DECL_MODULE_SETUPS__(__VA_ARGS__)

/**
 * @def ECT_DECL_MODULE_TEARDOWNS(...)
 * @brief Declares which module teardowns in the test module should be visible to test runners.
 * @param ... The names of the module teardowns. (Do not quote as strings)
 * @note This macro is required in a valid test module, and should be placed before @ref ECT_EXPORT_MODULE.
 * @note If no module teardowns is to be used, supply @ref ECT_NO_TEARDOWN as argument.
 */
#define ECT_DECL_MODULE_TEARDOWNS(...) ECT_DECL_MODULE_TEARDOWNS__(__VA_ARGS__)

/**
 * @def ECT_DECL_TEST_SETUPS(...)
 * @brief Declares which test setups in the test module should be visible to test runners.
 * @param ... The names of the test setups. (Do not quote as strings)
 * @note This macro is required in a valid test module, and should be placed before @ref ECT_EXPORT_MODULE.
 * @note If no test setups is to be used, supply @ref ECT_NO_SETUP as argument.
 */
#define ECT_DECL_TEST_SETUPS(...) ECT_DECL_TEST_SETUPS__(__VA_ARGS__)

/**
 * @def ECT_DECL_TEST_TEARDOWNS(...)
 * @brief Declares which test teardowns in the test module should be visible to test runners.
 * @param ... The names of the test teardowns. (Do not quote as strings)
 * @note This macro is required in a valid test module, and should be placed before @ref ECT_EXPORT_MODULE.
 * @note If no test teardowns is to be used, supply @ref ECT_NO_TEARDOWN as argument.
 */
#define ECT_DECL_TEST_TEARDOWNS(...) ECT_DECL_TEST_TEARDOWNS__(__VA_ARGS__)
/**@}*/

/**
 * @defgroup TESTDEF Test Function Definition Macros
 * @{
 */
/**
 * @def ECT_TEST(funcname)
 * @brief Defines a function suitable for use as an ECTest test case.
 * @param funcname The name of the function (Do not quote as string)
 */
#define ECT_TEST(funcname) ECT_TEST__(funcname)

/**
 * @def ECT_TEST_SETUP(funcname)
 * @brief Defines a function suitable for use as an ECTest setup function to be ran before each test case.
 * @param funcname The name of the function (Do not quote as string)
 */
#define ECT_TEST_SETUP(funcname) ECT_TEST_SETUP__(funcname)

/**
 * @def ECT_TEST_TEARDOWN(funcname)
 * @brief Defines a function suitable for use as an ECTest teardown function to be ran after each test case.
 * @param funcname The name of the function (Do not quote as string)
 */
#define ECT_TEST_TEARDOWN(funcname) ECT_TEST_TEARDOWN__(funcname)

/**
 * @def ECT_MODULE_SETUP(funcname)
 * @brief Defines a function suitable for use as an ECTest setup function to be ran before any of the test cases in
 *        a test module.
 * @param funcname The name of the function (Do not quote as string)
 */
#define ECT_MODULE_SETUP(funcname) ECT_MODULE_SETUP__(funcname)

/**
 * @def ECT_MODULE_TEARDOWN(funcname)
 * @brief Defines a function suitable for use as an ECTest teardown function to be ran after any of the test cases in
 *        a test module.
 * @param funcname The name of the function (Do not quote as string)
 */
#define ECT_MODULE_TEARDOWN(funcname) ECT_MODULE_TEARDOWN__(funcname)
/**@}*/

/**
 * @defgroup TESTRESULT Test Result Macros
 * @{
 */
/**
 * @def ECT_SUCCESS()
 * @brief Use to mark a test case as successful.
 *
 * Use to mark a test case as successful and immediately terminatest the test.
 * @note This macro yields the same result as a test that runs to the end of the function, except that it terminates it
 *       immediately.
 */
#define ECT_SUCCESS() ECT_SUCCESS__()

/**
 * @def ECT_FAIL()
 * @brief Use to mark a test case as failed, providing a message.
 *
 * Use to mark a test case as failed and immediately terminatest the test with a provided message
 */
#define ECT_FAIL(msg) ECT_FAIL__(msg)
#define ECT_FFAIL(fmt, ...) ECT_FFAIL__(fmt, __VA_ARGS__)

/**
 * @def ECT_SKIP()
 * @brief Use to mark a test case as skipped.
 *
 * Use to mark a test case as skipped and immediately terminates the test.
 */
#define ECT_SKIP() ECT_SKIP__()
/**@}*/

/**
 * @defgroup ASSERT Test Assert Macros
 * @{
 */
/**
 * @def ECT_ASSERT(expr, msg)
 * @brief Evaluates the expression. If it evaluates to true, the test continues, else it fails as if @ref ECT_FAIL had
 * been called.
 * @param expr The expression to evaluate.
 * @param msg The message to print on failed assert.
 */
#define ECT_ASSERT(expr, msg) ECT_ASSERT__(expr, msg)
//TODO remove all ECT_FASSERT into ECT_ASSERT, remove the "fmt" argument and document the first arg in __VA_ARGS__ as the format string.
#define ECT_FASSERT(expr, fmt, ...) ECT_FASSERT__(expr, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_TRUE(expr, msg)
 * @brief Alias for @ref ECT_ASSERT.
 */
#define ECT_ASSERT_TRUE(expr, msg) ECT_ASSERT(expr, msg)
#define ECT_FASSERT_TRUE(expr, fmt, ...) ECT_FASSERT(expr, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_FALSE(expr, msg)
 * @brief Evaluates the expression. If it evaluates to false, the test continues, else it fails as if @ref ECT_FAIL had
 * been called.
 * @param expr The expression to evaluate.
 * @param msg The message to print on failed assert.
 */
#define ECT_ASSERT_FALSE(expr, msg) ECT_ASSERT(!(expr), msg)
#define ECT_FASSERT_FALSE(expr, fmt, ...) ECT_FASSERT(!(expr), fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_CONTAINS(array, item, cmpfunc, msg)
 * @brief Checks whether the array contains the item, using the compare function.
 * @param array The array to check.
 * @param item The item to look for.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @param msg The message to print on failed assert.
 *
 * Checks whether the array contains the item, using the compare function. If not, it fails the test case and
 * prints the message specified.
 */
#define ECT_ASSERT_CONTAINS(array, item, cmpfunc, msg) ECT_ASSERT_CONTAINS__(array, item, cmpfunc, msg)
#define ECT_FASSERT_CONTAINS(array, item, cmpfunc, fmt, ...) ECT_FASSERT_CONTAINS__(array, item, cmpfunc, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_NOT_CONTAINS(array, item, cmpfunc, msg)
 * @brief Checks whether the array contains the item, using the compare function.
 * @param array The array to check.
 * @param item The item to look for.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @param msg The message to print on failed assert.
 *
 * Checks whether the array contains the item, using the compare function. If it does, it fails the test case and
 * prints the message specified.
 */
#define ECT_ASSERT_NOT_CONTAINS(array, item, cmpfunc, msg) ECT_ASSERT_NOT_CONTAINS__(array, item, cmpfunc, msg)
#define ECT_FASSERT_NOT_CONTAINS(array, item, cmpfunc, fmt, ...) ECT_FASSERT_NOT_CONTAINS__(array, items, cmpfunc, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_CONTAINSN(array, item, noccurence, cmpfunc, msg)
 * @brief Checks whether the array contains N occurences of the item, using the compare function.
 * @param array The array to check.
 * @param item The item to look for.
 * @param noccurence The number of times that the item must occur to validate the test.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @param msg The message to print on failed assert.
 *
 * Checks whether the array contains N occurences of the item, using the compare function. If it does not, it fails the
 * test case and prints the message specified.
 */
#define ECT_ASSERT_CONTAINSN(array, item, noccurence, cmpfunc, msg) ECT_ASSERT_CONTAINSN__(array, item, noccurence, cmpfunc, msg)
#define ECT_FASSERT_CONTAINSN(array, item, noccurence, cmpfunc, fmt, ...) ECT_FASSERT_CONTAINSN__(array, item, noccurence, cmpfunc, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_DCONTAINS(array, size, item, cmpfunc, msg)
 * @brief Checks whether the dynamic/pointer array contains the item, using the compare function.
 * @param array The array to check (dynamic or pointer to array).
 * @param nelem The number of elements in @p array.
 * @param item The item to look for.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @msg The message to print on failed assert.
 *
 * Checks whether the dynamic/pointer array contains the item, using the compare function. If it does not, it fails the
 * test case and prints the message specified.
 */
#define ECT_ASSERT_DCONTAINS(array, nelem, item, cmpfunc, msg) ECT_ASSERT_DCONTAINS__(array, nelem, item, cmpfunc, msg)
#define ECT_FASSERT_DCONTAINS(array, nelem, item, cmpfunc, fmt, ...) ECT_FASSERT_DCONTAINS__(array, nelem, item, cmpfunc, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_NOT_DCONTAINS(array, size, item, cmpfunc, msg)
 * @brief Checks whether the dynamic/pointer array contains the item, using the compare function.
 * @param array The array to check (dynamic or pointer to array).
 * @param nelem The number of elements in @p array.
 * @param item The item to look for.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @msg The message to print on failed assert.
 *
 * Checks whether the dynamic/pointer array contains the item, using the compare function. If it does, it fails the
 * test case and prints the message specified.
 */
#define ECT_ASSERT_NOT_DCONTAINS(array, nelem, item, cmpfunc, msg) ECT_ASSERT_NOT_DCONTAINS__(array, nelem, item, cmpfunc, msg)
#define ECT_FASSERT_NOT_DCONTAINS(array, nelem, item, cmpfunc, fmt, ...) ECT_FASSERT_NOT_DCONTAINS__(array, nelem, item, cmpfunc, fmt, __VA_ARGS__)

/**
 * @def ECT_ASSERT_DCONTAINSN(array, nelem, item, noccurence, cmpfunc, msg)
 * @brief Checks whether the dynamic/pointer array contains N occurences of the item, using the compare function.
 * @param array The array to check (dynamic or pointer to array).
 * @param nelem The number of elements in @p array.
 * @param item The item to look for.
 * @param noccurence The number of times that the item must occur to validate the test.
 * @param cmpfunc The comparator function. Must be a function that takes two items of the type of @item and returns a
 *                integer. The function should return 1 if the items compare equal; else 0.
 * @param msg The message to print on failed assert.
 *
 * Checks whether the dynamic/pointer array contains N occurences of the item, using the compare function. If it does
 * not, it fails the test case and prints the message specified.
 */
#define ECT_ASSERT_DCONTAINSN(array, nelem, item, noccurence, cmpfunc, msg) ECT_ASSERT_DCONTAINSN__(array, nelem, item, noccurence, cmpfunc, msg)
#define ECT_FASSERT_DCONTAINSN(array, nelem, item, noccurence, cmpfunc, fmt, ...) ECT_FASSERT_DCONTAINSN__(array, nelem, item, noccurence, cmpfunc, fmt, __VA_ARGS__)

/**@}*/
/**@}*/

/**
 * @defgroup UTILITIES Testing Utility Macros
 * @{
 */
/**
 * @def ECT_NO_SETUP
 * @brief Used in @ref ECT_DECL_TEST_SETUPS and @ref ECT_DECL_MODULE_SETUPS when there are no setup functions.
 * @ingroup TESTMODCREATE
 */
#define ECT_NO_SETUP ECT_NO_SETUP__

/**
 * @def ECT_NO_TEARDOWN
 * @brief Used in @ref ECT_DECL_TEST_TEARDOWNS and @ref ECT_DECL_MODULE_TEARDOWNS when there are no teardown functions.
 * @ingroup TESTMODCREATE
 */
#define ECT_NO_TEARDOWN ECT_NO_TEARDOWN__

/**
 * @def ECT_ARRAY_FOREACH(item, array)
 * @brief Utility macro for looping over each element in an array.
 * @param item The item yielded for each iteration.
 * @param array The array to loop over.
 *
 * Loops over each element in an array. Note that it has to be an array, for pointers to arrays/dynamic arrays, see
 * @ref ECT_DARRAY_FOREACH.
 */
#define ECT_ARRAY_FOREACH(item, array) ECT_FOREACH__(item, array)

/**
 * @def ECT_DARRAY_FOREACH(item, array, size)
 * @brief Utility macro for looping over each element in an dynamic array or a pointer to a array.
 * @param item The item yielded for each iteration.
 * @param array The array to loop over.
 * @param nelem The number of elements in @p array.
 */
//TODO IMPLEMENT
#define ECT_DARRAY_FOREACH(item, array, nelem) ECT_DFOREACH__(item, array, nelem)

/**
 * @def ECT_LLIST_FOREACH(item, list, nextname)
 * @brief Utility macro to walk through each node in a non circular linked list.
 * @param node The list node yielded for each iteration.
 * @param list The list to walk through
 * @param nextname The name of the member that points ot the next node.
 *
 * Walks through each node in a non circular linked list. In case of lists with a head-specific structure, the first
 * actual item-node must be supplied as @p list.
 *
 * @note @p nextname should be the name of the member, in a list node, that points ot the next node.
 */
//TODO IMPLEMENT
#define ECT_LLIST_FOREACH(type, node, list, nextname) ECT_LLIST_FOREACH__(type, node, list, nextname)
#define ECT_LLIST_FOREACH__(type, node, list, nextname)\
        for(type node = list; node != NULL; node = node->nextname)
 
/**@}*/

/* END PUBLIC MACROS */







/// @cond INTERNAL
/* INTERNAL
 *
 * This section contains macros/functions/data structures for internal usage within the ECTest framework. Do NOT use
 * these macros when writing test modules and runners. See the public section for macros to use when writing test
 * modules and runners.
 *
 * Using these macros/functions/data structures for test modules and runners are considered undefined behaviour in
 * the context of using the ECTest framework.
 */

#ifndef ECT_LOG_LEVEL
#   define ECT_LOG_LEVEL 3
#endif

#ifdef __unix__
#   define ECT_USE_ANSI_ESCAPE__
#endif

#if defined(__unix__)
#   define ECT_OPTION_DELIM__ -
#elif defined(_WIN32)
#   define ECT_OPTION_DELIM__ /
#endif

#if defined(__GNUC__)
#   define ETC_UNUSED__ __attribute__((__unused__))
#elif defined(_MSC_VER)
#   define ETC_MSVC_DISABLE_UNUSED__\
    __pragma(warning(push))\
    __pragma(warning(disable:4100))
#   define ETC_MSVC_RESET_UNUSED__\
    __pragma(wraning(pop))
#endif
#ifndef ETC_UNUSED__
#define ETC_UNUSED__
#endif
#ifndef ETC_MSVC_DISABLE_UNUSED__
#   define ETC_MSVC_DISABLE_UNUSED__
#endif
#ifndef ETC_MSVC_RESET_UNUSED__
#   define ETC_MSVC_RESET_UNUSED__
#endif


#ifndef ECT_ABORT_ON_FAIL
#   define ECT_ABORT_ON_FAIL 0
#else
#   undef ECT_ABORT_ON_FAIL
#   define ECT_ABORT_ON_FAIL 1
#endif

#ifndef ECT_EXPORT_RESULTS
#   define ECT_EXPORT_RESULTS 0
#else
#   undef ECT_EXPORT_RESULTS
#   define ECT_EXPORT_RESULTS 1
#endif

//TODO Look into if uniqueness can be achieved without conc array
#define ECT_DFOREACH__(type, item, array, nelem)\
    for(int ECT_CONC__(item,keep__) = 1, \
            ECT_CONC__(item,count__) = 0,\
            ECT_CONC__(item,size__) = nelem; \
        ECT_CONC__(item,keep__) && ECT_CONC__(item,count__) != ECT_CONC__(item,size__); \
        ECT_CONC__(item,keep__) = !ECT_CONC__(item,keep__), ECT_CONC__(item,count__)++) \
      for(type item = (array)[ECT_CONC__(item,count__)]; ECT_CONC__(item,keep__); ECT_CONC__(item,keep__) = !ECT_CONC__(item,keep__))

#define ECT_FOREACH__(type, item, array) ECT_DFOREACH__(type, item, array, ECT_SIZEOFARRAY__(array))

#define ECT_ARG_CHECK_FOR_LIST__(argc, argv, testsuite)\
    ECT_DFOREACH__(char *, ect_arg_, argv, argc){\
        if(strcmp(ect_arg_, ECT_STRINGIZE__(ECT_OPTION_DELIM__)"l") == 0){\
            ECT_LLIST_FOREACH__(struct ect_stack_node__ *, ect_node_, testsuite->modules->head, next){\
                ect_module__ *ect_mod_ = ect_node_->data;\
                ECT_DFOREACH__(ect_test__ , ect_test_, ect_mod_->tests->array, ect_mod_->tests->count){\
                    printf("%s.%s\n", ect_mod_->name, ect_test_.name);\
                }\
            }\
            return 0;\
        }\
    }

#define ECT_RUNNER__()\
    int main(int argc, char **argv)\
    {\
        (void)argc;(void)argv;/*TODO remove*/\
        ect_testsuite *ect_testsuite_ = ect_testsuite_create();\
        ECT_PERPARE_ALL_MODULES__(ect_testsuite_);\
        \
        if(argc > 0){\
            ECT_ARG_CHECK_FOR_LIST__(argc, argv, ect_testsuite_)\
          /*TODO check if only specific tests/modules should be ran*/ /*ECT_ARG_MARK_FOR_RUN__(argc, argv)*/\
        }\
        \
        ECT_RUN_TESTSUITE__(ect_testsuite_);\
        ECT_WHEN__(ECT_EXPORT_RESULTS,\
            ect_export_results(ect_testsuite_->results);\
        )\
        return 0;\
    }struct ect_dummy__/*forward declare to swallow semicolon*/
    
#define ECT_RUN_TESTSUITE__(testsuite)\
    do{\
        /*ECT_RUN_TESTS__*/\
        _Bool ect_abort_testrun_ = 0;\
        ECT_STACK_FOREACH_POP__(ect_module__ *, ect_curmodule_, testsuite->modules){\
            if(!ect_curmodule_->run){\
                free(ect_curmodule_);\
                continue;\
            }\
            ECT_EXECUTE_MODULE__(ect_curmodule_, testsuite->results, ect_abort_testrun_);\
        }\
        \
        /*TODO evaluate test run (ECT_EVAL_TESTRUN__)*/\
        ECT_EVAL_TESTRUN__(testsuite->results, ect_abort_testrun_);\
    }while(0)
        
#define ECT_PERPARE_ALL_MODULES__(testsuite)\
    do{\
        ect_module__ *(*ect_importer_)(void);\
        ECT_FOREACH__(, ect_importer_, ect_module_importers__){\
            ect_stack_push__(testsuite->modules, ect_importer_());/*TODO Change to map structure*/\
        }\
    }while(0)

#define ECT_BUILD_MODULE_ARRAY__(x) ECT_STRINGIZE__(x), 
#define ECT_PREPARE_MODULES__(testsuite, ...)\
    do{\
        ect_module__ *(*ect_importer_)(void);\
        char *ect_modulenames_[] = {ECT_LOOP__(ECT_BUILD_MODULE_ARRAY__, __VA_ARGS__)};\
        ect_module__ *ect_modules_[ECT_SIZEOFARRAY__(ect_modulenames_)] = {0};\
        int ect_cur_offset_ = 0;\
        ECT_FOREACH__(, ect_importer_, ect_module_importers__){\
            ect_module__ *ect_module_ = ect_importer_();\
            ECT_FOREACH__(char *, ect_req_name_, ect_modulenames_){\
                if(strcmp(ect_req_name_, ect_module_->name) == 0){\
                    ect_modules_[ect_cur_offset_++] = ect_module_;\
                }\
            }\
        }\
        ECT_FOREACH__(ect_module__ *, ect_module_, ect_modules_){ect_stack_push__(testsuite->modules, ect_module_);}\
    }while(0)
        
#define ECT_EXECUTE_MODULE__(module, resultstack, abortrun)\
    do{\
        ect_moduleresult__ ect_modresult_ = {\
            .count = module->tests->count,\
            .failed = 0,\
            .success = 0,\
            .skipped = module->tests->count,\
        };\
        \
        ECT_DFOREACH__(ect_setup__, ect_msfunc_, module->modsetup->array, module->modsetup->count){ect_msfunc_();}\
        ECT_DFOREACH__(ect_test__, ect_test_, module->tests->array, module->tests->count){\
        if(!ect_test_.run) break;\
        \
        ECT_EXECUTE_TEST__(ect_test_, module, ect_modresult_, resultstack, abortrun);\
        \
        ECT_WHEN__(ECT_ABORT_ON_FAIL, if(abortrun) goto ect_goto_module_cleanup_;)\
        }\
        ect_goto_module_cleanup_:\
        ECT_DFOREACH__(ect_setup__, ect_mtdfunc_, module->modteardown->array, module->modteardown->count){ect_mtdfunc_();}\
        ECT_FLOG__("[Module Summary] Module '%s' | Tests: %zu Success: %zu Failed: %zu Skipped: %zu\n",\
                   ect_curmodule_->name,\
                   ect_modresult_.count,\
                   ect_modresult_.success,\
                   ect_modresult_.failed,\
                   ect_modresult_.skipped);\
        free(module);\
        ECT_WHEN__(ECT_ABORT_ON_FAIL, if(abortrun) goto ect_goto_test_eval_;)\
    }while(0)
        
#define ECT_EVAL_TESTRUN__(resultstack, abortrun)\
    do{\
        ECT_WHEN__(ECT_ABORT_ON_FAIL, if(abortrun){\
            ect_goto_test_eval_:\
            ECT_LOG__("[Test Summary] Test run aborted due to failing module with ECT_ABORT_ON_FAIL defined...");\
        })\
    }while(0)

#define ECT_EXECUTE_TEST__(test, module, moduleresult, resultstack, abortrun)\
    do{\
        ECT_DFOREACH__(ect_setup__, ect_tsfunc_, module->testsetup->array, module->testsetup->count){ect_tsfunc_();}\
        ect_caseresult__ ect_result_ = {.msg = NULL, .result = ECT_CASERES_SUCCESS};\
        test.func(&ect_result_);\
        ect_stack_push__(resultstack, ect_testresult_new__(ect_result_.result,\
                                                         module->name,\
                                                         test.name));\
        switch(ect_result_.result){\
            case ECT_CASERES_SUCCESS:{\
                moduleresult.success++;\
                moduleresult.skipped--;\
                ECT_WHEN__(ETC_LOG_SUCCESS__, ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KGRN__,"SUCCESS")"]\t%s.%s\n",\
                    module->name,\
                    test.name);)\
            }break;\
            \
            case ECT_CASERES_FAILED:{\
                moduleresult.failed++;\
                moduleresult.skipped--;\
                ECT_WHEN__(ETC_LOG_FAIL__,\
                    ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KRED__, "FAILED")"]\t%s.%s | %s\n",\
                        module->name,\
                        test.name,\
                        ect_result_.msg);\
                    free(ect_result_.msg);)\
                ECT_WHEN__(ECT_ABORT_ON_FAIL,\
                    ECT_LOG_SEP__();\
                    ECT_FLOG__("[Module Summary] Module '%s' failed, aborting test...\n\n", ect_curmodule_->name);\
                    abortrun = 1;)\
            }break;\
            case ECT_CASERES_SKIPPED: {\
                ECT_WHEN__(ETC_LOG_SKIP__, ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KYEL__,"SKIPPED")"]\t%s.%s\n",\
                    module->name,\
                    test.name);)\
            }break;\
        }\
        ECT_DFOREACH__(ect_teardown__, ect_ttdfunc_, module->testteardown->array, module->testteardown->count){ect_ttdfunc_();}\
    }while(0)

/*** UTILITY MACROS ***/
#define ECT_PCON__(x, y) x##y
#define ECT_CONC__(x, y) ECT_PCON__(x, y)
#define ECT_PCONCWU__(x, y) x##_##y
#define ECT_CONCWU__(x, y) ECT_PCONCWU__(x,y)
#define ECT_ESC_PAR__(...) __VA_ARGS__
#define ECT_IF___1(t, f) t
#define ECT_IF___0(t, f) f
#define ECT_IF__(c, t, f) ECT_CONCWU__(ECT_IF__, c)(ECT_ESC_PAR__(t),ECT_ESC_PAR__(f))
#define ECT_WHEN__(c, t) ECT_IF__(c, t, )
#define ECT_PSTRINGIZE__(x) #x
#define ECT_STRINGIZE__(x) ECT_PSTRINGIZE__(x)
#define ECT_ADDRESSOF__(x) &x,

/*** LOOP BASE MACRO ***/
#define ECT_EXPAND__(x) x
#define ECT_FIRSTARG__(x, ...) (x)
#define ECT_RESTARGS__(x, ...) (__VA_ARGS__)

#define ECT_NUM_ARGS___(X100, X99, X98, X97, X96, X95, X94, X93, X92, X91, X90, X89, X88, X87, X86, X85, X84, X83, X82,\
                        X81, X80, X79, X78, X77, X76, X75, X74, X73, X72, X71, X70, X69, X68, X67, X66, X65, X64, X63,\
                        X62, X61, X60, X59, X58, X57, X56, X55, X54, X53, X52, X51, X50, X49, X48, X47, X46, X45, X44,\
                        X43, X42, X41, X40, X39, X38, X37, X36, X35, X34, X33, X32, X31, X30, X29, X28, X27, X26, X25,\
                        X24, X23, X22, X21, X20, X19, X18, X17, X16, X15, X14, X13, X12, X11, X10, X9, X8, X7, X6, X5,\
                        X4, X3, X2, X1, N, ...)   N

#define ECT_NUM_ARGS__(...) ECT_NUM_ARGS___(__VA_ARGS__,\
                        100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78,\
                        77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55,\
                        54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,\
                        31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9,\
                        8, 7, 6, 5, 4, 3, 2, 1)

#define ECT_MLOOP__1(m, list)
#define ECT_MLOOP__2(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__1(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__3(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__2(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__4(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__3(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__5(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__4(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__6(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__5(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__7(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__6(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__8(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__7(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__9(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__8(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__10(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__9(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__11(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__10(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__12(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__11(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__13(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__12(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__14(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__13(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__15(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__14(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__16(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__15(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__17(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__16(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__18(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__17(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__19(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__18(m, ECT_RESTARGS__ list)
#define ECT_MLOOP__20(m, list) ECT_EXPAND__(m ECT_FIRSTARG__ list) ECT_MLOOP__19(m, ECT_RESTARGS__ list)
//TODO remove loops constructs that arent neccessary and can be replaced by this.
#define ECT_MLOOP3__(n, m, list) ECT_MLOOP__##n(m, list)
#define ECT_MLOOP2__(n, m, list) ECT_MLOOP3__(n, m, list)

#define ECT_MLOOP__(macro, list) ECT_MLOOP2__(ECT_NUM_ARGS__ list, macro, list)

#define ECT_LOOP__(macro, ...) ECT_MLOOP__(macro, (__VA_ARGS__,))

/*** END LOOP BASE MACRO ***/
/*** END UTILITY MACROS ***/

/*** FUNCTION POINTER DEFINES ***/
#define ECT_SIZEOFARRAY__(arrname) \
    (sizeof(arrname)/sizeof(*(arrname)))

#define ECT_FUNC_PTR__(type, name) void(*name)(type)
#define ECT_FUNC_PTR_ARRAY__(type, arrayname) ECT_FUNC_PTR__(type, arrayname[])
/*** END FUNCTION POINTER DEFINES ***/

/*** TEST/SETUP/TEARDOWN DECLARES AND DEFINES ***/
#define ECT_DECLFUNC__(type, name) static void name(type)

#define ECT_DECL_TESTS__(...) ECT_EXPORT_TESTS__(__VA_ARGS__)
//#define ECT_DECL_TESTS__(...) ECT_EXPORT_FUNCS__(ect_tarray, ect_testarray__, void *, __VA_ARGS__)
#define ECT_DECL_MODULE_SETUPS__(...) ECT_EXPORT_FUNCS__(ect_bmarray, ect_setuparray__, void, __VA_ARGS__)
#define ECT_DECL_MODULE_TEARDOWNS__(...) ECT_EXPORT_FUNCS__(ect_amarray, ect_teardownarray__, void, __VA_ARGS__)
#define ECT_DECL_TEST_SETUPS__(...) ECT_EXPORT_FUNCS__(ect_btarray, ect_setuparray__, void, __VA_ARGS__)
#define ECT_DECL_TEST_TEARDOWNS__(...) ECT_EXPORT_FUNCS__(ect_atarray, ect_teardownarray__, void, __VA_ARGS__)


#define ECT_TEST__(funcname) \
    ETC_MSVC_DISABLE_UNUSED__\
    ECT_DECLFUNC__(ETC_UNUSED__ void *state, funcname)\
    ETC_MSVC_RESET_UNUSED__
#define ECT_TEST_SETUP__(funcname) ECT_DECLFUNC__(void, funcname)
#define ECT_TEST_TEARDOWN__(funcname) ECT_DECLFUNC__(void, funcname)
#define ECT_MODULE_SETUP__(funcname) ECT_DECLFUNC__(void, funcname)
#define ECT_MODULE_TEARDOWN__(funcname) ECT_DECLFUNC__(void, funcname)

/*** END TEST/SETUP/TEARDOWN DECLARES AND DEFINES ***/

/*** MODULE IMPORT ***/
#define ECT_IMPORT_MODULE__(modulename)\
    extern ect_module__ *ECT_CONCWU__(modulename, import)(void);

#define ECT_BUILD_IMPORTER__(arg) &ECT_CONCWU__(arg, import),
#define ECT_IMPORT_MODULES__(...)\
    ECT_LOOP__(ECT_IMPORT_MODULE__, __VA_ARGS__)\
    ect_module__* (*ect_module_importers__[])(void) = {ECT_LOOP__(ECT_BUILD_IMPORTER__, __VA_ARGS__)}

/*** END MODULE IMPORT ***/

#define ECT_BUILD_TESTARRAY__(x) { .name = ECT_STRINGIZE__(x), .func = &x, .run = 1},

/*** MODULE EXPORT ***/
#define ECT_EXPORT_TEST__(func) static void func(void *state);
#define ECT_EXPORT_TESTS__(...)\
    ECT_LOOP__(ECT_EXPORT_TEST__, __VA_ARGS__)\
    static ect_test__ ect_tarray_static_[] = {\
        ECT_LOOP__(ECT_BUILD_TESTARRAY__, __VA_ARGS__)\
    };\
    static ect_testarray__ ect_tarray_ = {\
        .array = ect_tarray_static_,\
        .count = ECT_SIZEOFARRAY__(ect_tarray_static_)\
    }

#define ECT_EXPORT_SETUPTEARDOWN__(func) static void func(void);
#define ECT_EXPORT_FUNCS__(arrname, arrtype, type, ...)\
    ECT_LOOP__(ECT_EXPORT_SETUPTEARDOWN__, __VA_ARGS__)\
    static ECT_FUNC_PTR_ARRAY__(type, ECT_CONC__(arrname,static_)) = {\
        ECT_LOOP__(ECT_ADDRESSOF__, __VA_ARGS__)\
    };\
    static arrtype arrname = {\
        .array = ECT_CONC__(arrname,static_),\
        .count = ECT_SIZEOFARRAY__(ECT_CONC__(arrname,static_))\
    }

#define ECT_EXPORT_MODULE__(modulename) \
    ect_module__ *ECT_CONCWU__(modulename, import)(void)\
    {\
        ect_module__ ect_modinit_ = {\
            .name = ECT_STRINGIZE__(modulename),\
            .run = 1,\
            .modteardown = &ect_amarray,\
            .modsetup = &ect_bmarray,\
            .testteardown = &ect_atarray,\
            .testsetup = &ect_btarray,\
            .tests = &ect_tarray_\
        };\
        ect_module__ *ect_modptr_ = malloc(sizeof *ect_modptr_);\
        if(ect_modptr_ == NULL) abort(); /*FIXME better handling*/\
        memcpy(ect_modptr_, &ect_modinit_, sizeof *ect_modptr_);\
        return ect_modptr_;\
    }struct ect_dummy__/*forward declare to swallow semicolon*/

/*** END MODULE EXPORT ***/

/*** LOGGING ***/

#ifdef ECT_USE_ANSI_ESCAPE__
#   define ECT_PRINT_WITH_COLOR__(color, txt) color txt ECT_KNRM__
#   define ECT_KNRM__  "\x1B[0m"
#   define ECT_KRED__  "\x1B[31m"
#   define ECT_KGRN__  "\x1B[32m"
#   define ECT_KYEL__  "\x1B[33m"
#   define ECT_KBLU__  "\x1B[34m"
#   define ECT_KMAG__  "\x1B[35m"
#   define ECT_KCYN__  "\x1B[36m"
#   define ECT_KWHT__  "\x1B[37m"
#else
#   define ECT_PRINT_WITH_COLOR__(color, txt) txt
#endif

#define ECT_FLOG__(fmt, ...) printf(fmt, __VA_ARGS__)
#define ECT_LOG__(msg) ECT_FLOG__("%s", msg)
#define ECT_LOG_SEP__()\
    ECT_LOG__("------------------------------------------------------------------\n")
/*** END LOGGING ***/

/*** TEST CASE EXITS ***/
#define ECT_CASERES__(caseresult, resmsg) (ect_caseresult){.result = caseresult, .testname = __func__, .msg = resmsg}

#if ECT_LOG_LEVEL >= 1
#   define ETC_LOG_FAIL__ 1
#   ifdef _GNU_SOURCE
#       define ECT_FFAIL__(fmt, ...) \
            do{\
                caseresult__ *ect_result_ = state;\
                asprintf(&ect_result_->msg, fmt, __VA_ARGS__);\
                ect_result_->result = ECT_CASERES_FAILED;
                return;\
            }while(0)
#   else
#       define ECT_FFAIL__(fmt, ...) \
            do{\
                ect_caseresult__ *ect_result_ = state;\
                int ect_failmsgsize_ = snprintf(NULL, 0, fmt, __VA_ARGS__);\
                ect_result_->msg = malloc(ect_failmsgsize_+1);\
                snprintf(ect_result_->msg, ect_failmsgsize_+1, fmt, __VA_ARGS__);\
                ect_result_->result = ECT_CASERES_FAILED;\
                return;\
            }while(0)
#   endif
#else
#   define ETC_LOG_FAIL__ 0
#   define ECT_FFAIL__(fmt, ...) return ECT_CASERES__(ECT_CASERES_FAILED, NULL)
#endif

#define ECT_FAIL__(msg) ECT_FFAIL__("%s", msg)

#if ECT_LOG_LEVEL >= 2
#   define ETC_LOG_SKIP__ 1
#else
#   define ETC_LOG_SKIP__ 0
#endif
#define ECT_SKIP__()\
    do{\
        ((ect_caseresult__*)(state))->result = ECT_CASERES_SKIPPED;\
        return;\
    }while(0)

#if ECT_LOG_LEVEL >= 3
#   define ETC_LOG_SUCCESS__ 1
#else
#   define ETC_LOG_SUCCESS__ 0
#endif
#define ECT_SUCCESS__() return
/*** END TEST CASE EXITS ***/

/*** ASSERT ***/
#define ECT_FASSERT__(cond, failfmt, ...)            \
    do{                                         \
        if(!(cond)){                            \
            ECT_FFAIL(failfmt, __VA_ARGS__);        \
        }                                       \
    }while(0)

#define ECT_ASSERT__(cond, failmsg) ECT_FASSERT__(cond, "%s", failmsg)

#define ECT_FASSERT_DCONTAINS__(array, nelem, item, cmpfunc, fmt, ...)\
    do{\
        size_t ect_ac_arrsize_ = nelem;\
        int ect_ac_found_ = 0;\
        for(size_t ect_ac_ind_ = 0; ect_ac_ind_ < ect_ac_arrsize_; ect_ac_ind_++){\
            if(cmpfunc(item, array[i])){\
                ect_ac_found_ = 1;\
                break;\
            }\
        }\
        if(!ect_ac_found_){\
            ECT_FFAIL(fmt, __VA_ARGS__);\
        }\
    }
#define ECT_ASSERT_DCONTAINS__(array, nelem, item, cmpfunc, msg) ECT_FASSERT_DCONTAINS__(array, nelem, item, cmpfunc, "%s", msg)
#define ECT_FASSERT_CONTAINS__(array, item, cmpfunc, fmt, ...) ECT_FASSERT_DCONTAINS__(array, ECT_SIZEOFARRAY__(array), item, cmpfunc, fmt, __VA_ARGS__)
#define ECT_ASSERT_CONTAINS__(array, item, cmpfunc, msg) ECT_FASSERT_CONTAINS__(array, item, cmpfunc, "%s", msg)

#define ECT_FASSERT_NOT_DCONTAINS__(array, nelem, item, cmpfunc, fmt, ...)\
    do{\
        size_t ect_ac_arrsize_ = nelem;\
        int ect_ac_found_ = 0;\
        for(size_t ect_ac_ind_ = 0; ect_ac_ind_ < ect_ac_arrsize_; ect_ac_ind_++){\
            if(cmpfunc(item, array[i])){\
                ect_ac_found_ = 1;\
                break;\
            }\
        }\
        if(ect_ac_found_){\
            ECT_FFAIL(fmt, __VA_ARGS__);\
        }\
    }
#define ECT_ASSERT_NOT_DCONTAINS__(array, nelem, item, cmpfunc, msg) ECT_FASSERT_NOT_DCONTAINS__(array, nelem, item, cmpfunc, "%s", msg)
#define ECT_FASSERT_NOT_CONTAINS__(array, item, cmpfunc, fmt, ...) ECT_FASSERT_NOT_DCONTAINS__(array, ECT_SIZEOFARRAY__(array), item, cmpfunc, fmt, __VA_ARGS__)
#define ECT_ASSERT_NOT_CONTAINS__(array, item, cmpfunc, msg) ECT_FASSERT_NOT_CONTAINS__(array, item, cmpfunc, "%s", ...)

#define ECT_FASSERT_DCONTAINSN__(array, nelem, item, noccurence, cmpfunc, fmt, ...)\
    do{\
        size_t ect_ac_arrsize_ = nelem;\
        int ect_ac_found_ = 0;\
        for(size_t ect_ac_ind_ = 0; ect_ac_ind_ < ect_ac_arrsize_; ect_ac_ind_++){\
            if(cmpfunc(item, array[i])){\
                ect_ac_found_++;\
                break;\
            }\
        }\
        if(ect_ac_found_ != noccurence){\
            ECT_FFAIL(fmt, __VA_ARGS__);\
        }\
    }
#define ECT_ASSERT_DCONTAINSN__(array, nelem, item, noccurence, cmpfunc, msg) ECT_FASSERT_DCONTAINSN__(array, nelem, item, noccurence, cmpfunc, "%s", msg)
#define ECT_FASSERT_CONTAINSN__(array, item, noccurence, cmpfunc, fmt, ...) ECT_FASSERT_DCONTAINSN__(array, ECT_SIZEOFARRAY__(array), item, noccurence, fmt, __VA_ARGS__)
#define ECT_ASSERT_CONTAINSN__(array, item, noccurence, cmpfunc, msg) ECT_FASSERT_CONTAINSN__(array, item, noccurence, cmpfunc, "%s", msg)

/*** END ASSERT ***/

/*** DATA STRUCTURES ***/
typedef void(*ect_testfunc)(void *state);
typedef void(*ect_setup__)(void);
typedef void(*ect_teardown__)(void);

typedef struct {
    size_t count;
    size_t success;
    size_t failed;
    size_t skipped;
}ect_moduleresult__;

typedef enum{
    ECT_CASERES_SUCCESS,
    ECT_CASERES_FAILED,
    ECT_CASERES_SKIPPED
}ect_caseresenum__;

typedef struct {
    ect_caseresenum__ result;
    const char *modulename;
    const char *testname;
}ect_testresult__;

static inline ect_testresult__ *ect_testresult_new__(ect_caseresenum__ result, const char *modulename, const char *testname)
{
    ect_testresult__ *res = malloc(sizeof *res);
    res->result = result;
    res->modulename = modulename;
    res->testname = testname;
    return res;
}

typedef struct{
    ect_caseresenum__ result;
    char *msg;
}ect_caseresult__;

typedef void(*ect_freefunc)(void *item);

struct ect_stack_node__{
    void *data;
    struct ect_stack_node__ *next;
};

typedef struct ect_stack__{
    ect_freefunc freefunc;
    struct ect_stack_node__ *head;
}ect_stack__;

static inline ect_stack__ *ect_stack_create__(ect_freefunc freefunc)
{
    ect_stack__ *stack = malloc(sizeof *stack);
    if(stack == NULL) return NULL;
    stack->head = NULL;
    stack->freefunc = freefunc;
    return stack;
}

static inline int ect_stack_push__(ect_stack__ *stack, void *data)
{
    if(stack == NULL) return -1;
    struct ect_stack_node__ *node = malloc(sizeof *node);
    if(node == NULL) return -2;
    node->data = data;
    node->next = stack->head;
    stack->head = node;
    return 0;
}

static inline void *ect_stack_pop__(ect_stack__ *stack)
{
    if(stack == NULL || stack->head == NULL) return NULL;
    struct ect_stack_node__ *node = stack->head;
    stack->head = stack->head->next;
    void *data = node->data;
    free(node);
    return data;
}

#define ECT_STACK_FOREACH_POP__(type, item, stack)\
    for(type item = ect_stack_pop__(stack); item != NULL; item = ect_stack_pop__(stack))

static inline void ect_stack_destroy__(void *stack)
{
    if(stack == NULL) return;
    ect_stack__ *s = stack;
    void *data;
    while(s->head != NULL){
        data = ect_stack_pop__(s);
        if(s->freefunc != NULL) s->freefunc(data);
    }
    free(s);
}

typedef struct{
    const char *name;
    ect_testfunc func;
    _Bool run;
}ect_test__;

#define ECT_DEFINE_ARRAYTYPE__(type, name)\
    typedef struct name{\
        size_t count;\
        type *array;\
    }name

ECT_DEFINE_ARRAYTYPE__(ect_setup__, ect_setuparray__);
ECT_DEFINE_ARRAYTYPE__(ect_teardown__, ect_teardownarray__);
ECT_DEFINE_ARRAYTYPE__(ect_test__, ect_testarray__);

typedef struct ect_module__{
    const char *name;
    _Bool run;
    ect_setuparray__ *testsetup;
    ect_teardownarray__ *testteardown;
    ect_setuparray__ *modsetup;
    ect_teardownarray__ *modteardown;
    ect_testarray__ *tests;
}ect_module__;

static inline ect_testsuite *ect_testsuite_create()
{
    ect_testsuite *ts = malloc(sizeof *ts);
    ts->modules = ect_stack_create__(NULL);
    ts->results = ect_stack_create__(NULL);
    return ts;
}

static inline void ect_testsuite_destroy(void *testsuite)
{
    if(testsuite == NULL) return;
    ect_testsuite *suite = testsuite;
    ECT_STACK_FOREACH_POP__(ect_module__ *, module, suite->results){free(module);}
    ect_stack_destroy__(suite->modules);
    ECT_STACK_FOREACH_POP__(ect_testresult__ *, result, suite->results){free(result);}
    ect_stack_destroy__(suite->results);
    free(suite);
}

static inline void ect_export_results(ect_testsuite *testsuite)
{
    (void)testsuite; //TODO Implement
}
/*** END DATA STRUCTURES ***/

static inline void ect_nosetupteardown__(void){}
#define ECT_NO_SETUP__ ect_nosetupteardown__
#define ECT_NO_TEARDOWN__ ect_nosetupteardown__

/// @endcond
#endif // _ECTEST_H__
