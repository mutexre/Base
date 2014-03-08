#ifndef header_991FBFD583C1
#define header_991FBFD583C1

#include <list>
#include <string>
#include <stdio.h>

namespace Rt
{
    void dump(const void* buf, u4 nbytes);
    std::string stringFormat(const char* fmt, va_list args);
    void error(u4 ID);
    void error(u4 ID, const char* fmt, ...);
    template <typename T> void printList(std::list<T> l, const char* format, const char* separator);
    void printBacktrace(int fileno);
}

extern "C" {
    inline unsigned long long rdtsc()
    {
//      __asm__ __volatile__ ("xorl %%eax,%%eax \n cpuid" ::: "%rax", "%rbx", "%rcx", "%rdx");

#ifdef __APPLE__
		unsigned long value;
        __asm__ __volatile__ ("rdtsc" : "=r"(value));
        return value;
#elif defined _WIN32 || defined _WIN64
    #if defined _WIN64
        return __rdtsc();
    #else
        typedef union _LARGE_INTEGER {
            struct {
                Rt::u4 low;
                Rt::u4 high;
            };
            Rt::u8 whole;
        } LARGE_INTEGER, *PLARGE_INTEGER;

        LARGE_INTEGER li;

		rdtsc();

		__asm	mov	li.low, eax;
		__asm	mov	li.high, edx;

		return li.whole;
    #endif
#endif
    }
}

#define START_CLOCKCYCLES unsigned long AEBC, AA7A; AEBC = rdtsc();
#define STOP_CLOCKCYCLES AA7A = rdtsc(); printf("diff=%lu\n", AA7A - AEBC);

#include <Runtime/DebugDefinition.h>

#endif
