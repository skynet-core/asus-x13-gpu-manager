#ifndef egpu_x13_lib_config_h_
#define egpu_x13_lib_config_h_ 1

#if defined(LEVEL_DEBUG)
#define LOG_LEVEL 4
#elif defined(LEVEL_INFO)
#define LOG_LEVEL 3
#elif defined(LEVEL_WARN)
#define LOG_LEVEL 2
#elif defined(LEVEL_ERROR)
#define LOG_LEVEL 1
#endif


#endif
