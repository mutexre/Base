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
        using u1 = uint8_t;
        using s1 = int8_t;
        using u2 = uint16_t;
        using s2 = int16_t;
        using u4 = uint32_t;
        using s4 = int32_t;
        using u8 = uint64_t;
        using s8 = int64_t;
        using f4 = float;
        using f8 = double;
        using uuid = uint8_t[16];

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
        using u1 = uint8_t;
        using s1 = int8_t;
        using u2 = uint16_t;
        using s2 = int16_t;
        using u4 = uint32_t;
        using s4 = int32_t;
        using u8 = uint64_t;
        using s8 = int64_t;
        using f4 = float;
        using f8 = double;
        using uuid = uint8_t[16];

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
