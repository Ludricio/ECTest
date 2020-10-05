

#ifndef __ECTEST_MASTER_H_
#define __ECTEST_MASTER_H_


#ifndef __ECTEST_TYPES_H_
#define __ECTEST_TYPES_H_

typedef void (*__ectest_tfn)(void);

struct __ectest_test{
    char *fnname;
    __ectest_tfn fn;   
};

struct __ectest_module{
    char *mname;
    int ntests;
    struct __ectest_test tests[];
};

struct __ectest_suite{
    int nmodules;
    struct __ectest_module modules[];
};
#endif /*__ECTEST_TYPES_H_*/




#endif /*__ECTEST_MASTER_H_*/
