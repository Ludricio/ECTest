#ifndef ECTEST_EXPIMP__
#define ECTEST_EXPIMP__
    
#define ECT_EXPORT_MODULE__(module, X...)                                       \
    ect_module *ect_export_module_##module##__()                                \
    {                                                                           \
        struct ect_test__ tests[] = {X};                                        \
        size_t testcount = ECT_SIZEOF_ARRAY(tests);                             \
        ect_module *mod = malloc(sizeof *mod + testcount* sizeof *tests);       \
        memcpy(mod, &(ect_module){                                              \
            .file = __FILE__,                                                   \
            .module = #module,                                                  \
            .testcount = testcount,                                             \
        }, sizeof *mod);                                                        \
        memcpy(mod->tests, tests, testcount * sizeof *tests);                   \
        return mod;                                                             \
    }
    
#define ECT_TEST__(test) {test, #test}

#define ECT_IMPORT_MODULE__(module)                                             \
    ({                                                                          \
        extern ect_module *ect_export_module_##module##__();                    \
        ect_export_module_##module##__();                                       \
    })
    
#endif /*ECTEST_EXPIMP__*/

