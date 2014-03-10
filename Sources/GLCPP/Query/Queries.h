#ifndef header_AFE4CB401169
#define header_AFE4CB401169

namespace GL
{
    class Queries
    {
#ifdef __APPLE__
    #if TARGET_OS_IPHONE

    private:
        Query samplesPassed;

    public:
        //Queries();
        Queries(bool enableSamplesPassed);
        virtual ~Queries();

        Query& getSamplesPassed();

    #elif TARGET_OS_MAC

    private:
        Query samplesPassed;
        Query timeElapsed;

    public:
        //Queries();
        Queries(bool enableSamplesPassed, bool enableTimeElapsed);
        virtual ~Queries();

        Query& getSamplesPassed();
        Query& getTimeElapsed();

    #endif
#elif defined(__linux)
#elif defined(_WIN32)
#elif defined(_WIN64)
#endif
    };
}

#endif
