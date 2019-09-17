#include <stdlib.h>
#include <string.h>

struct ect_state__{
    int state;
};
    
typedef void (*ect_testfn__)(void);

struct ect_test__{
    ect_testfn__ func;
    const char *name;
};

typedef struct ect_module{
    const char *file;
    const char *module;
    int testcount;
    struct ect_test__ tests[];
}ect_module;

typedef struct ect_suit{
    const char *name;
    int modulecount;
    ect_module **modules;
}ect_suit;
    
#define ECT_EXPORT_MODULE(module, X...)\
    ect_module *ect_export_module_##module##__()\
    {\
        struct ect_test__ tests[] = {X};\
        size_t testcount = ECT_SIZEOF_ARRAY(tests);\
        ect_module *mod = calloc(sizeof *mod + testcount* sizeof *tests, 1);\
        memcpy(mod, &(ect_module){\
            .file = __FILE__,\
            .module = #module,\
            .testcount = testcount\
        }, sizeof *mod);\
        memcpy(mod->tests, tests, testcount * sizeof *tests);\
        return mod;\
    }
    
#define ECT_IMPORT_MODULE(module)\
    ({\
        extern ect_module *ect_export_module_##module##__();\
        ect_export_module_##module##__();\
    })
    
#define ECT_TEST(test) {test, #test}    
#define ECT_SIZEOF_ARRAY(arr) sizeof arr/sizeof *arr


