#include "cvt_base.h"
#include <string>

TimeLog::TimeLog(const char *hint)
{
    mHint = std::string(hint);
    mTimestamp = getMononicMS();
    LOGD("%s begin", hint);
}

TimeLog::~TimeLog()
{
    long diff = getMononicMS() - mTimestamp;
    LOGD("%s cost %ld ms", mHint.c_str(), diff);
}

long TimeLog::getMononicMS()
{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long ms = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    return ms;
}

long TimeLog::getCost()
{
    return getMononicMS() - mTimestamp;
}

void TimeLog::reset(const char *hint)
{
    long old = mTimestamp;
    mTimestamp = getMononicMS();
    LOGD("%s cost %ld ms", mHint.c_str(), mTimestamp - old);
    mHint = hint;
    LOGD("%s begin", hint);
}
