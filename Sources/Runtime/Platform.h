#ifndef header_D74CEF35ED79
#define header_D74CEF35ED79

#ifdef __APPLE__

    #include <stdint.h>
    #include "TargetConditionals.h"

    #if TARGET_OS_IPHONE
    #elif TARGET_OS_MAC
    #endif

    namespace Rt
    {
        typedef uint8_t u1;
        typedef int8_t s1;
        typedef uint16_t u2;
        typedef int16_t s2;
        typedef uint32_t u4;
        typedef int32_t s4;
        typedef uint64_t u8;
        typedef int64_t s8;
        typedef	uint8_t uuid[16];
        
        using f4 = float;
        using f8 = double;

        template <typename T>
        class StrideOffset
        {
        public:
            T stride;
            T offset;
        };
    }

#elif defined(__linux)
    #error not implemented
#elif defined _WIN32 || defined _WIN64
	#include <windows.h>
    #include <stdint.h>

    #if TARGET_OS_IPHONE
    #elif TARGET_OS_MAC
    #endif

    #define __func__ __FUNCTION__

    #if defined(_MSC_VER)
        #define strtoll _strtoi64
    #endif

    namespace Rt
    {
        typedef uint8_t u1;
        typedef int8_t s1;
        typedef uint16_t u2;
        typedef int16_t s2;
        typedef uint32_t u4;
        typedef int32_t s4;
        typedef uint64_t u8;
        typedef int64_t s8;
        typedef	uint8_t uuid[16];

        using f4 = float;
        using f8 = double;

        template <typename T>
        class StrideOffset
        {
        public:
            T stride;
            T offset;
        };
    }

    #define RT_HAVE_NO_UNISTD

	#ifdef min
		#undef min
	#endif

	#ifdef max
		#undef max
	#endif
#endif

#ifdef RT_HAVE_NO_UNISTD
    #define STDIN_FILENO 0
    #define STDOUT_FILENO 1
    #define STDERR_FILENO 2
#endif

#endif
