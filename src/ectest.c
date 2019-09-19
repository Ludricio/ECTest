#ifndef EXCEPTIONS_NO_SIGNALHANDLING
#define _DEFAULT_SOURCE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <ucontext.h>
#if defined(REG_RIP)
#   define EXCEPTIONS_FAULT_ADDRESS_REG REG_RIP
#   define EXCEPTIONS_FAULT_ADDRESS_FMT "%llx"
#elif defined(REG_EIP)
#   define EXCEPTIONS_FAULT_ADDRESS_REG REG_EIP
#   define EXCEPTIONS_FAULT_ADDRESS_FMT "%x"
#else
#   error _GNU_SOURCE must be declared before including ucontext.h
#endif
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <dlfcn.h>
#endif

/*#include <signal.h>
#include <unistd.h>
#include <sys/ucontext.h>
#include <ucontext.h>
#include <sys/types.h>
#include <sys/wait.h>*/

#include <ectest_master.h>

//ECT_TESTRUNNER
/*int main(void)
{
 //   ect_module *asd = ECT_IMPORT_MODULE(module);
    ect_suit *asd = ECT_SUIT_NEW("TestSuit",
        ECT_IMPORT_MODULE(module),
        ECT_IMPORT_MODULE(module)
    );
    printf("%s\n", asd->modules[0]->tests[0].name);
    ECT_SUIT_FREE(asd);
    return 0;
}*/

#define ECT_TESTRUNNER ECT_TESTRUNNER__

#define ECT_TESTRUNNER__

/*static __thread struct ect_state__;
static void ect_suit_run__(ect_suit *suit){
    
    ECT_ARRAY_FOREACH(ect_module *mod, suit->modules, suit->modulecount){
        if(mod->modsetup) mod->modsetup();
           
        
        
        if(mod->modteardown) mod->modteardown();
    }
}

static void ect_test_prepare__(state)
void ect_test_fail__()
void ect_test_skip__()*/

/*#define void ECT_SUIT_RUN(suit)
{
    
}*/

                                         
    
void fail();
int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    
    sa.sa_sigaction = exceptions_signalHandler;
    sa.sa_flags = SA_SIGINFO;
    
    if(sigaction(SIGSEGV, &sa, NULL) < 0){
        perror("sigaction");
        return 1;
    }
    extern void tg_testgrab();
//    tg_testgrab();
    fail();
    return 0;
}

void fail(){
    int * p = (int*) 0x12345678;
    *p = 0;
    //raise(SIGSEGV);
}









































