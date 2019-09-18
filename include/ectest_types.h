#ifndef ECTEST_TYPES__
#define ECTEST_TYPES__

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
    ect_testfn__ modsetup;
    ect_testfn__ modteardown;
    ect_testfn__ testsetup;
    ect_testfn__ testteardown;
    struct ect_test__ tests[];
}ect_module;

typedef struct ect_suit{
    const char *name;
    int modulecount;
    ect_module **modules;
}ect_suit;
    

#endif /*ECTEST_TYPES__*/

