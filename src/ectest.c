#include <ectest.h>
#include <stdio.h>

#define ECT_SUIT_NEW(suitname, X...)\
    ({\
        ect_module *modules[] = {X};\
        size_t modulecount = ECT_SIZEOF_ARRAY(modules);\
        ect_suit *suit = malloc(sizeof *suit + modulecount * sizeof *modules);\
        memcpy(suit, &(ect_suit){\
            .name = suitname,\
            .modulecount = modulecount,\
            .modules = modules\
        }, sizeof *suit + modulecount * sizeof *modules);\
        suit;\
    })
 
#define ECT_SUIT_FREE(suit)\
    ({\
        if(suit){\
            for(int i = 0; i < suit->modulecount; i++){\
                free(suit->modules[i]);\
            }\
            free(suit);\
        }\
    })
    
    
int main(void)
{
 //   ect_module *asd = ECT_IMPORT_MODULE(module);
    ect_suit *asd = ECT_SUIT_NEW("TestSuit",
        ECT_IMPORT_MODULE(module),
        ECT_IMPORT_MODULE(module)
    );
    printf("%s\n", asd->modules[0]->tests[0].name);
    ECT_SUIT_FREE(asd);
    return 0;
}

#define ECT_SUIT_RUN(suit)
{
    
}

