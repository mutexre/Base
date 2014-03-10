#include <stdio.h>
#include <GLCPP/GL.h>

#ifdef __APPLE__
    #if TARGET_OS_IPHONE

GL::Queries::Queries(bool enableSamplesPassed) {
    samplesPassed.init(enableSamplesPassed, GL_ANY_SAMPLES_PASSED_EXT);
}

GL::Query& GL::Queries::getSamplesPassed() {
    return samplesPassed;
}

    #elif TARGET_OS_MAC

GL::Queries::Queries(bool enableSamplesPassed, bool enableTimeElapsed) {
    samplesPassed.setEnabled(enableSamplesPassed);
    samplesPassed.setTarget(GL_SAMPLES_PASSED);

    timeElapsed.setEnabled(enableTimeElapsed);
    timeElapsed.setTarget(GL_TIME_ELAPSED);
}

GL::Query& GL::Queries::getSamplesPassed() {
    return samplesPassed;
}

GL::Query& GL::Queries::getTimeElapsed() {
    return timeElapsed;
}

    #endif
#elif defined(__linux)
#elif defined(_WIN32)
#elif defined(_WIN64)
#endif
