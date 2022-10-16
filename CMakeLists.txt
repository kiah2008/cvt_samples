cmake_minimum_required(VERSION 3.0.0)
project(CVT CXX C)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cvt_detectCompiler)
INCLUDE(cvt_utils)

OPTION(CVT_SKIP_SYSTEM_PROCESSOR_DETECTION "if skip system processor detection" OFF)
MESSAGE("CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})


if(MINGW)
  if(EXISTS /mingw)
      list(APPEND CMAKE_INCLUDE_PATH /mingw)
  endif()
  if(EXISTS /mingw32)
      list(APPEND CMAKE_INCLUDE_PATH /mingw32)
  endif()
  if(EXISTS /mingw64)
      list(APPEND CMAKE_INCLUDE_PATH /mingw64)
  endif()
elseif(ANDROID)
  set(OpenCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/android/jni/)
endif()

# Save libs and executables in the same place
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Output directory for applications")

if(ANDROID)
  set(LIBRARY_OUTPUT_PATH                "$CVT_BINARY_DIR}/lib/${ANDROID_NDK_ABI_NAME}")
  cvt_update(3P_LIBRARY_OUTPUT_PATH      "$CVT_BINARY_DIR}/3rdparty/lib/${ANDROID_NDK_ABI_NAME}")
else()
  set(LIBRARY_OUTPUT_PATH                "$CVT_BINARY_DIR}/lib")
  cvt_update(3P_LIBRARY_OUTPUT_PATH      "$CVT_BINARY_DIR}/3rdparty/lib")
endif()

# if(ANDROID)
#   if(ANDROID_ABI MATCHES "NEON")
#     set(ENABLE_NEON ON)
#   endif()
#   if(ANDROID_ABI MATCHES "VFPV3")
#     set(ENABLE_VFPV3 ON)
#   endif()
# endif()

add_subdirectory(src)
add_subdirectory(tests)


