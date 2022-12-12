#pragma once
#include <string>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __unix__
#include <stdio.h>
#define LOGD(format, ...) printf(format "\n", ##__VA_ARGS__)
#else
#include <android/log.h>
#ifndef TAG
#define TAG "cvt_log"
#endif

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__);
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);
#endif

#ifdef __cplusplus
}
#endif

class TimeLog {

private:
    std::string mHint;
    long mTimestamp;

    long getMononicMS();
public:

    TimeLog(const char* hint);
    ~TimeLog();
    long getCost();
    void reset(const char* hint);
};

#define VAR_NAME__(x,y) x_##y
#define VAR_NAME_(x) VAR_NAME__(x, __LINE__)

//#define TIME_LOG(x) std::shared_ptr<TimeLog> VAR_NAME_(TIME_LOG) = std::make_shared<TimeLog>(x)
#define TIME_LOG(x) TimeLog VAR_NAME_(TIME_LOG)(x)

