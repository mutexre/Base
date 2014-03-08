#ifndef header_16FA91E4EE68
#define header_16FA91E4EE68

#include <stdarg.h>
#include <string>
#ifdef __APPLE__
    #include <execinfo.h>
#endif

namespace Rt
{
    #define N_CALLSTACK_ENTRIES 32

    class Exception
    {
    private:
        void* callStack[N_CALLSTACK_ENTRIES];

    public:
        Exception() {
            #ifdef __APPLE__
            backtrace(callStack, N_CALLSTACK_ENTRIES);
            #endif
        }

        virtual ~Exception() {};
    };
}

#endif
