#include "StopWatch.h"

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
StopWatch::StopWatch() : elapsed_(0) {
    elapsed_ = 0;
    start_.QuadPart = 0;
    stop_.QuadPart = 0;
    QueryPerformanceFrequency(&frequency_);
}
#else
StopWatch::StopWatch() : elapsed_(0), start_(MicroSeconds::zero()), stop_(MicroSeconds::zero()) {}
#endif

StopWatch::~StopWatch() {}

void StopWatch::start() {
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
    QueryPerformanceCounter(&start_);
#else
    start_ = Clock::now();
#endif
}

void StopWatch::stop() {
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(WIN32)
    QueryPerformanceCounter(&stop_);
    elapsed_ += (stop_.QuadPart - start_.QuadPart) * 1000000 / frequency_.QuadPart;
#else
    stop_ = Clock::now();
    elapsed_ = std::chrono::duration_cast<MicroSeconds>(stop_ - start).count();
#endif
}

void StopWatch::restart() {
    elapsed_ = 0;
    start();
}

double StopWatch::elapsed() {
    return static_cast<double>(elapsed_);
}

double StopWatch::elapsedMS() {
    return elapsed_ / 1000.0;
}

double StopWatch::elapsedSecond() {
    return elapsed_ / 1000000.0;
}