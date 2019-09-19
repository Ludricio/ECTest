#ifndef ECTEST_SUIT__
#define ECTEST_SUIT__

#define ECT_SUIT_NEW__(suitname, X...)                                          \
    ({                                                                          \
        ect_module *modules[] = {X};                                            \
        size_t modulecount = ECT_SIZEOF_ARRAY(modules);                         \
        ect_suit *suit = malloc(sizeof *suit + modulecount * sizeof *modules);  \
        memcpy(suit, &(ect_suit){                                               \
            .name = suitname,                                                   \
            .modulecount = modulecount,                                         \
            .modules = modules                                                  \
        }, sizeof *suit + modulecount * sizeof *modules);                       \
        suit;                                                                   \
    })
 
#define ECT_SUIT_FREE__(suit)                                                   \
    ({                                                                          \
        if(suit){                                                               \
            for(int i = 0; i < suit->modulecount; i++){                         \
                free(suit->modules[i]);                                         \
            }                                                                   \
            free(suit);                                                         \
        }                                                                       \
    })

#endif /*ECTEST_SUIT__*/

