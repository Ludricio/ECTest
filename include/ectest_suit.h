#ifndef ECTEST_SUITE__
#define ECTEST_SUITE__

#define ect_suite_new(suitename, modules...) ECT_SUITE_NEW__(suitename, modules)
#define ECT_SUITE_NEW__(suitename, X...)                                        \
    ({                                                                          \
        ect_module *modules[] = {X};                                            \
        size_t modulecount = ECT_SIZEOF_ARRAY(modules);                         \
        ect_suite *suite = ect_malloc__(sizeof *suite +                         \
                                        modulecount * sizeof *modules,          \
                                        ECT_MEMTAG_SUITE__);                    \
        memcpy(suite, &(ect_suite){                                             \
            .name = suitename,                                                  \
            .modulecount = modulecount,                                         \
            .modules = modules                                                  \
        }, sizeof *suite + modulecount * sizeof *modules);                      \
        suite;                                                                  \
    })

static inline void ect_suite_free(ect_suite *suite)
{
    if(suite){
        for(int i = 0; i < suite->modulecount; i++){
            ect_free__(suite->modules[i]);
        }
        ect_free__(suite);
    }
}

#endif /*ECTEST_SUITE__*/

