#ifndef ECTEST_SUIT__
#define ECTEST_SUIT__

#define ECT_SUIT_NEW__(suitname, X...)                                          \
    ({                                                                          \
        ect_module *modules[] = {X};                                            \
        size_t modulecount = ECT_SIZEOF_ARRAY(modules);                         \
        ect_suit *suit = ect_malloc__(sizeof *suit +                            \
                                        modulecount * sizeof *modules);         \
        memcpy(suit, &(ect_suit){                                               \
            .name = suitname,                                                   \
            .modulecount = modulecount,                                         \
            .modules = modules                                                  \
        }, sizeof *suit + modulecount * sizeof *modules);                       \
        suit;                                                                   \
    })

static inline void ect_suit_free(ect_suit *suit)
{
    if(suit){
        for(int i = 0; i < suit->modulecount; i++){
            ect_free__(suit->modules[i]);
        }
        ect_free__(suit);
    }
}

#endif /*ECTEST_SUIT__*/

