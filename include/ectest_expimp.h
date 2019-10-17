#ifndef ECTEST_EXPIMP__
#define ECTEST_EXPIMP__    
    
#define ect_export_module(module, functions...)                                 \
        ECT_EXPORT_MODULE__(module, functions)
#define ECT_EXPORT_MODULE__(module, X...)                                       \
    ect_module *ect_export_module_##module##__()                                \
    {                                                                           \
        struct ect_test__ tests[] = {X};                                        \
        size_t testcount = ECT_SIZEOF_ARRAY(tests);                             \
        ect_module *mod = ect_malloc__(sizeof *mod + testcount* sizeof *tests,  \
                                        ECT_MEMTAG_MODULE__);                   \
                                                                                \
        memcpy(mod, &(ect_module){                                              \
            .file = __FILE__,                                                   \
            .name = #module,                                                    \
            .testcount = testcount,                                             \
            .modsetup = NULL,                                                   \
            .modteardown = NULL,                                                \
            .testsetup = NULL,                                                  \
            .testteardown = NULL                                                \
        }, sizeof *mod);                                                        \
        memcpy(mod->tests, tests, testcount * sizeof *tests);                   \
                                                                                \
        ECT_ARRAY_FOREACH(struct ect_test__ test, mod->tests, testcount){       \
            if(test.type == ECT_TESTTYPE_TEST__) continue;                      \
                                                                                \
            if(!mod->modsetup && test.type == ECT_TESTTYPE_MODSETUP__){         \
                mod->modsetup = test.func;                                      \
                continue;                                                       \
            }                                                                   \
            if(!mod->modteardown && test.type == ECT_TESTTYPE_TESTTEARDOWN__){  \
                mod->modteardown = test.func;                                   \
                continue;                                                       \
            }                                                                   \
            if(!mod->testsetup && test.type == ECT_TESTTYPE_TESTSETUP__){       \
                mod->testsetup = test.func;                                     \
                continue;                                                       \
            }                                                                   \
            if(!mod->testteardown && test.type == ECT_TESTTYPE_TESTTEARDOWN__){ \
                mod->testteardown = test.func;                                  \
                continue;                                                       \
            }                                                                   \
        }                                                                       \
                                                                                \
        return mod;                                                             \
    }
      
#define ect_test(function) ECT_TEST__(function)
#define ECT_TEST__(function) {function, 0, #function}

#define ect_module_setup(function) ECT_MODULE_SETUP__(function)
#define ECT_MODULE_SETUP__(function) {function, 1, #function}

#define ect_module_teardown(function) ECT_MODULE_TEARDOWN__(function)
#define ECT_MODULE_TEARDOWN__(function) {function, 2, #function}

#define ect_test_setup(function) ECT_TEST_SETUP__(function)
#define ECT_TEST_SETUP__(function) {function, 3, #function}

#define ect_test_teardown(function) ECT_TEST_TEARDOWN__(function)
#define ECT_TEST_TEARDOWN__(function) {function, 4, #function}

#define ect_import_module(module) ECT_IMPORT_MODULE__(module)
#define ECT_IMPORT_MODULE__(module)                                             \
    ({                                                                          \
        extern ect_module *ect_export_module_##module##__();                    \
        ect_export_module_##module##__();                                       \
    })
    
#endif /*ECTEST_EXPIMP__*/

