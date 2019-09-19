#ifndef ECTEST_UTILS__
#define ECTEST_UTILS__

#define ECT_PRED__(txt) "\x1B[31m"txt"\x1B[0m"
#define ECT_PGRN__(txt) "\x1B[32m"txt"\x1B[0m"
#define ECT_PYEL__(txt) "\x1B[33m"txt"\x1B[0m"

#define ECT_SIZEOF_ARRAY__(array) sizeof array/sizeof *array

#define ECT_ARRAY_FOREACH__(item, array, size)                                  \
    for(int ect_fe_keep_ = 1,                                                   \
            ect_fe_count_ = 0,                                                  \
            ect_fe_size_ = size;                                                \
        ect_fe_keep_ && ect_fe_count_ != ect_fe_size_;                          \
        ect_fe_keep_ = !ect_fe_keep_, ect_fe_count_++)                          \
      for(item = array[ect_fe_count_]; ect_fe_keep_; ect_fe_keep_ = !ect_fe_keep_)
    

#endif /*ECTEST_UTILS__*/

