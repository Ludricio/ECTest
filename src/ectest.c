#define ECT_LOG_LEVEL__ 5
#include <ectest_master.h>
void fail();

//TODO ect_suite_run
//  Add test breakdown
//  Add result printout
//  Add appenders
//  Add jumpback from failed test
//  Add test isolation ???

void ect_suite_run(ect_suite *suite)
{
    ECT_DLOG__("Running suite: %s", suite->name);
    struct ect_state__ tstate = {0};
    

    for(int i = 0; i < suite->modulecount; i++){
        ect_module *module = suite->modules[i];
        ECT_DLOG__("Running module: %s.%s", suite->name, module->name);
        if(module->modsetup) module->modsetup();

        for(int j = 0; j < module->testcount; j++){
            struct ect_test__ test = module->tests[j];
            ECT_DLOG__("Running test: %s.%s.%s", suite->name, module->name, test.name);
            if(module->testsetup) module->testsetup();
            tstate.state = ECT_STATE_SUCCESS__;
            test.func();
            switch (tstate.state){
                //TODO add state handling
                case /* constant-expression */:
                    /* code */
                    break;
                default:
                    //TODO add error handling
                    break;
            }
            if(module->testteardown) module->testteardown();

        }

        if(module->modteardown) module->modteardown();
    }
}

int main(int argc, char **argv)
{
/*    struct sigaction sa;
    memset(&sa, 0, sizeof sa);

    sa.sa_sigaction = exceptions_signalHandler;
    sa.sa_flags = SA_SIGINFO;

    if(sigaction(SIGSEGV, &sa, NULL) < 0){
        perror("sigaction");
        return 1;
    }*/
/*    struct sigaction sAction;
    sAction.sa_sigaction = &exceptions_signalHandler;
    sigemptyset(&sAction.sa_mask);
    sAction.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV,&sAction,NULL);*/
    
    ect_mem_init__();
    void *ptr = ect_malloc__(25, ECT_MEMTAG_MODULE__);
    ect_free__(ptr);
    ect_mem_release__();

    /*printf("SIZE OF: %zu\n", sizeof(struct ect_memnode__));
    ect_suite *suite = ect_suite_new("test suite", ect_import_module(test_module));
    ect_suite_run(suite);
    ect_suite_free(suite);*/

    //extern void tg_testgrab();
    return 0;
}

void fail(){

    int * p = (int*) 0x12345678;
    *p = 0;
    //raise(SIGSEGV);
}
