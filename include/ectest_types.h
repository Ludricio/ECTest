#ifndef ECTEST_TYPES__
#define ECTEST_TYPES__

struct ect_state__{
    int state;
    int line;
    char func[128];
    char msg[1024];
};
    
typedef void (*ect_testfn__)(void);

#define ECT_TESTTYPE_TEST__ 0
#define ECT_TESTTYPE_MODSETUP__ 1
#define ECT_TESTTYPE_MODTEARDOWN__ 2
#define ECT_TESTTYPE_TESTSETUP__ 3
#define ECT_TESTTYPE_TESTTEARDOWN__ 4 
struct ect_test__{
    ect_testfn__ func;
    char type;
    const char *name;
};

typedef struct ect_module{
    int testcount;
    ect_testfn__ modsetup;
    ect_testfn__ modteardown;
    ect_testfn__ testsetup;
    ect_testfn__ testteardown;
    const char *file;
    const char *module;
    struct ect_test__ tests[];
}ect_module;

typedef struct ect_suit{
    int modulecount;
    ect_module **modules;
    const char *name;
}ect_suit;
    

#endif /*ECTEST_TYPES__*/
