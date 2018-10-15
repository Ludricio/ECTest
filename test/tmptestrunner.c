#include <ectest.h>

ECT_IMPORT_MODULES(
    TestModule
);

int main()
{
    ect_testsuite ect_suite__ = {0};
    ect_suite__.modules = ect_stack_create(NULL);
    ECT_FOREACH__(ect_module *(*importer)(void), ect_module_importers__){
        ect_stack_push(ect_suite__.modules, importer());/*TODO Change to map structure*/
    }

    ect_module *ect_curmodule__;
    while((ect_curmodule__ = ect_stack_pop(ect_suite__.modules)) != NULL){
        ect_setup__ *ect_msetups__ = ect_curmodule__->beforemodule;
        ect_setup__ *ect_tsetups__ = ect_curmodule__->beforetest;
        ect_test *ect_tests__ = ect_curmodule__->tests;
        ect_teardown__ *ect_tteardowns__ = ect_curmodule__->aftertest;
        ect_teardown__ *ect_mteardowns__ = ect_curmodule__->aftermodule;

        ECT_DFOREACH__(ect_setup__ ect_bmodule__, ect_msetups__, ect_curmodule__->nbmodule){ect_bmodule__();}
        ECT_DFOREACH__(ect_test ect_test__, ect_tests__, ect_curmodule__->ntests){
            ECT_DFOREACH__(ect_setup__ ect_btest__, ect_tsetups__, ect_curmodule__->nbtest){ect_btest__();}

            ect_caseresult ect_result__;
            ect_test__.func(&ect_result__);

            ECT_DFOREACH__(ect_teardown__ ect_atest__, ect_tteardowns__, ect_curmodule__->natest){ect_atest__();}
        }
        ECT_DFOREACH__(ect_setup__ ect_amodule__, ect_mteardowns__, ect_curmodule__->namodule){ect_mteardowns__();}
    }
    ECT_RUN_MODULE(TestModule);
    return 0;
}

