#include <ectest.h>

ECT_IMPORT_MODULES(
    TestModule
);

int main(int argc, char **argv)
{
    (void)argc;(void)argv;//TODO remove

    /*ECT_PREPARE_MODULES__*/
    ect_testsuite ect_suite__ = {0};
    ect_suite__.modules = ect_stack_create(NULL);
    ECT_FOREACH__(ect_module *(*importer)(void), ect_module_importers__){
        ect_stack_push(ect_suite__.modules, importer());/*TODO Change to map structure*/
    }
    /*END ECT_PREPARE_MODULES__*/

    /*TODO check if only specific tests/modules should be ran*/

    /*ECT_RUN_TESTS__*/
    ect_module *ect_curmodule__;
    ect_stack *ect_results_ = ect_stack_create(NULL);
    while((ect_curmodule__ = ect_stack_pop(ect_suite__.modules)) != NULL){
        /*ECT_MODULE_RUN__*/
        ect_setup__ *ect_ms_ = ect_curmodule__->bmodule;
        ect_setup__ *ect_ts_ = ect_curmodule__->btest;
        ect_test *ect_tests_ = ect_curmodule__->tests;
        ect_teardown__ *ect_ttd_ = ect_curmodule__->atest;
        ect_teardown__ *ect_mtd_ = ect_curmodule__->amodule;

        ECT_DFOREACH__(ect_setup__ ect_msfunc_, ect_ms_, ect_curmodule__->nbmodule){ect_msfunc_();}
        ECT_DFOREACH__(ect_test ect_test_, ect_tests_, ect_curmodule__->ntests){
            ECT_DFOREACH__(ect_setup__ ect_tsfunc_, ect_ts_, ect_curmodule__->nbtest){ect_tsfunc_();}

            /*ECT_MODULE_EXEC_TEST__*/
            ect_caseresult ect_result_;
            ect_test_.func(&ect_result_);
            ect_stack_push(ect_results_, ect_testresult_new__(ect_result_.result,
                                                              ect_curmodule__->name,
                                                              ect_result_.testname));
            switch(ect_result_.result){
                case ECT_CASERES_SUCCESS:{
                    //TODO log statement
                }break;
                case ECT_CASERES_FAILED:{
                    //TODO log statement
                    //TODO check if abort
                }break;
                case ECT_CASERES_SKIPPED: {
                    //TODO log statement
                }break;
            }
            /*END ECT_MODULE_EXEC_TEST__*/

            ECT_DFOREACH__(ect_teardown__ ect_ttdfunc_, ect_ttd_, ect_curmodule__->natest){ect_ttdfunc_();}
        }
        ECT_DFOREACH__(ect_setup__ ect_mtdfunc_, ect_mtd_, ect_curmodule__->namodule){ect_mtdfunc_();}
        //Summary
    }
    /*END ECT_RUN_TESTS__*/

//    ect_moduleresult ECT_CONCWU__(modulename, run)(void)\
//    {\
//        struct ect_moduleresult result_ = {0};\
//            /*Run module setup functions*/\
//            ECT_FOREACH__(ECT_FUNC_PTR__(void, bmfunc), BMARRAY){ bmfunc(); }\
//            /*Loop over all test functions*/\
//            ECT_FOREACH__(ECT_FUNC_PTR__(ect_caseresult, tfunc), TARRAY){\
//                /*Run test setup functions*/\
//                ECT_FOREACH__(ECT_FUNC_PTR__(void, btfunc), BTARRAY){ btfunc(); }\
//                /*Run test function*/\
//                result_.count++;\
//                ect_caseresult caseresult_ = tfunc();\
//                switch(caseresult_.result){\
//                    case ECT_CASERES_SUCCESS:{\
//                        result_.success++;\
//                        ECT_IF__(ETC_LOG_SUCCESS__,\
//                            ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KGRN__,"SUCCESS")"]\t%s.%s\n",\
//                                    ECT_STRINGIZE__(modulename), \
//                                    caseresult_.testname),);\
//                    }break;\
//                    case ECT_CASERES_FAILED:{\
//                        result_.failed++;\
//                        ECT_IF__(ETC_LOG_FAIL__,\
//                            ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KRED__, "FAILED")"]\t%s.%s | %s\n",\
//                                    ECT_STRINGIZE__(modulename),\
//                                    caseresult_.testname,\
//                                    caseresult_.msg);\
//                            free(caseresult_.msg);,)\
//                        ECT_IF__(ECT_ABORT_ON_FAIL,\
//                            ECT_LOG_SEP__();\
//                            ECT_FLOG__("[Module Summary] Module '%s' failed, aborting test...\n\n",ECT_STRINGIZE__(modulename));\
//                            return result_;,)\
//                    }break;\
//                    case ECT_CASERES_SKIPPED:{\
//                        result_.skipped++;\
//                        ECT_IF__(ETC_LOG_SKIP__,\
//                            ECT_FLOG__("["ECT_PRINT_WITH_COLOR__(ECT_KYEL__,"SKIPPED")"]\t%s.%s\n",\
//                                    ECT_STRINGIZE__(modulename), \
//                                    caseresult_.testname);,)\
//                    }break;\
//                }\
//                /*Run test teardown functions*/\
//                ECT_FOREACH__(ECT_FUNC_PTR__(void, atfunc), BTARRAY){ atfunc(); }\
//        }\
//        /*Run module teardown functions*/\
//        ECT_FOREACH__(ECT_FUNC_PTR__(void, amfunc), AMARRAY){ amfunc(); }\
//        ECT_FLOG__("[Module Summary] Module '%s' | Tests: %d Success: %d Failed: %d Skipped: %d\n", ECT_STRINGIZE__(modulename),\
//                result_.count, result_.success, result_.failed, result_.skipped);\
//        ECT_LOG_SEP__();\
//        return result_;\
//    }
    ECT_RUN_MODULE(TestModule);
    return 0;
}

