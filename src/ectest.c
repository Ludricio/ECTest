#include <ectest_master.h>
    
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

/*#define void ECT_SUIT_RUN(suit)
{
    
}*/

