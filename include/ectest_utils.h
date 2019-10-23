#ifndef ECTEST_UTILS__
#define ECTEST_UTILS__

#define ECT_PRED__(txt) "\x1B[31m"txt"\x1B[0m"
#define ECT_PGRN__(txt) "\x1B[32m"txt"\x1B[0m"
#define ECT_PYEL__(txt) "\x1B[33m"txt"\x1B[0m"

#define ECT_SIZEOF_ARRAY(array) ECT_SIZEOF_ARRAY__(array)
#define ECT_SIZEOF_ARRAY__(array) sizeof array/sizeof *array

#define ECT_ARRAY_FOREACH(item, array, size)                                    \
        ECT_ARRAY_FOREACH__(item, array, size) 
#define ECT_ARRAY_FOREACH__(item, array, size)                                  \
    for(int ect_fe_keep_ = 1,                                                   \
            ect_fe_count_ = 0,                                                  \
            ect_fe_size_ = size;                                                \
        ect_fe_keep_ && ect_fe_count_ != ect_fe_size_;                          \
        ect_fe_keep_ = !ect_fe_keep_, ect_fe_count_++)                          \
      for(item = array[ect_fe_count_]; ect_fe_keep_; ect_fe_keep_ = !ect_fe_keep_)


/*  ECT_LOG_LEVEL__
 *  0 = none
 *  1 = error
 *  2 = warning
 *  3 = info
 *  4 = debug
 */


#ifndef ECT_LOG_LEVEL__
    #define ECT_LOG_LEVEL__ 3
#endif

#ifndef ECT_EXT_LOG_IMPL__

#define ECT_LOG__(dlvl, fmt,  ...)                                              \
    printf("[%s]\tL:%d\t%s::%s\t" fmt "\n" ,                                    \
        dlvl,                                                                   \
        __LINE__,                                                               \
        __FILE__,                                                               \
        __func__,                                                               \
        ##__VA_ARGS__)
        
#if ECT_LOG_LEVEL__ >= 1
#define ECT_ELOG__(fmt, x...) ECT_LOG__("ERROR", fmt, ##x)
#else
#define ECT_ELOG__(fmt, x...)
#endif /*ECT_LOG_LEVEL__ >= 1*/

#if ECT_LOG_LEVEL__ >= 4
#define ECT_WLOG__(fmt, x...) ECT_LOG__("WARNING", fmt, ##x)
#else
#define ECT_WLOG__(fmt, x...)
#endif /*ECT_LOG_LEVEL__ >= 2*/

#if ECT_LOG_LEVEL__ >= 4
#define ECT_ILOG__(fmt, x...) ECT_LOG__("INFO", fmt, ##x)
#else
#define ECT_ILOG__(fmt, x...)
#endif /*ECT_LOG_LEVEL__ >= 3*/

#if ECT_LOG_LEVEL__ >= 4
#define ECT_DLOG__(fmt, x...) ECT_LOG__("DEBUG", fmt, ##x)
#else
#define ECT_DLOG__(fmt, x...)
#endif /*ECT_LOG_LEVEL__ >= 4*/

#endif /*ECT_EXT_LOG_IMPL__*/

#endif /*ECTEST_UTILS__*/

