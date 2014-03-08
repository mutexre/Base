#ifndef header_739F047BD8EE
#define header_739F047BD8EE

#if (defined _WIN32 || defined _WIN64) && defined RT_LOG_THROUGH_WINAPI
#define RtLog(text) OutputDebugString(L ## text)
#else
	#define RtLog printf
#endif

#ifdef DEBUG
    #define RtDebugLog RtLog
    #define RtAssert(cond) if (!(cond)) { RTDebugLog( "assert \"%s\" failed in %s at line %d\n", #cond, __FILE__, __LINE__); }
#else
    #define RtDebugLog(...)
    #define	RtAssert(cond)
#endif

#endif
