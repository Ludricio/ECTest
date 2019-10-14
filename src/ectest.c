#define ECT_LOG_LEVEL__ 0
#include <ectest_master.h>
void fail();

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
    int *ptr = ect_malloc__(sizeof *ptr);
    ECT_DLOG__();
    ect_free__(ptr);
    ect_memroot_free__();
    
    
    
    extern void tg_testgrab();
    return 0;
}

void fail(){
   
    int * p = (int*) 0x12345678;
    *p = 0;
    //raise(SIGSEGV);
}









































