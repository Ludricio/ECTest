#ifndef ECTEST_EXPIMP__
#define ECTEST_EXPIMP__    
    
#define ECT_EXPORT_MODULE__(module, X...)                                       \
    ect_module *ect_export_module_##module##__()                                \
    {                                                                           \
        struct ect_test__ tests[] = {X};                                        \
        size_t testcount = ECT_SIZEOF_ARRAY(tests);                             \
        ect_module *mod = malloc(sizeof *mod + testcount* sizeof *tests);       \
                                                                                \
        memcpy(mod, &(ect_module){                                              \
            .file = __FILE__,                                                   \
            .module = #module,                                                  \
            .testcount = testcount,                                             \
            .modsetup = NULL,                                                   \
            .modteardown = NULL,                                                \
            .testsetup = NULL,                                                  \
            .testteardown = NULL                                                \
        }, sizeof *mod);                                                        \
        memcpy(mod->tests, tests, testcount * sizeof *tests);                   \
                                                                                \
        ECT_ARRAY_FOREACH(struct ect_test__ test, mod->tests, testcount){       \
            if(test.type = ECT_TESTTYPE_TEST__) continue;                       \
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
    
#define ECT_TEST__(test) {test, 0, #test}
#define ECT_TEST_MODSETUP__(test) {test, 1, #test}
#define ECT_TEST_MODTEARDOWN__(test) {test, 2, #test}
#define ECT_TEST_SETUP__(test) {test, 3, #test}
#define ECT_TEST_TEARDOWN__(test) {test, 4, #test}

#define ECT_IMPORT_MODULE__(module)                                             \
    ({                                                                          \
        extern ect_module *ect_export_module_##module##__();                    \
        ect_export_module_##module##__();                                       \
    })
    
#endif /*ECTEST_EXPIMP__*/

