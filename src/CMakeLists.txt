# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Define project name
project(cpp_samples)

# macro(cpp_target_link_libraries)
#    target_link_libraries(${ARGN})
# endmacro()

#include_directories(BEFORE "${OpenCV_INCLUDE_DIRS}")
# message(STATUS "== cv include ${OpenCV_INCLUDE_DIRS}")
# include_directories("${OpenCV_INCLUDE_DIRS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)

file(GLOB_RECURSE cpp_samples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} cv/*.cpp)
# file(GLOB cpp_samples  "*.cpp")


foreach(cpp_sample ${cpp_samples})
  set(package "cpp")

  message(STATUS "handle ${cpp_sample}")

  if(cpp_sample MATCHES "cv/")
    set(package "cv")
    cvt_sample_define(tgt ${cpp_sample} ${package})
  endif()

  if(cpp_sample MATCHES "cpp/")
    set(package "cpp")
    cvt_cpp_define(tgt ${cpp_sample} ${package})
  endif()

#   if(DEFINED DEPS_${tgt})
#     set(deps ${DEPS_${tgt}})
#   endif()

#   if(cpp_sample MATCHES "/gpu/" AND HAVE_opencv_cudaarithm AND HAVE_opencv_cuda_filters)
#   target_link_libraries(${tgt} PRIVATE opencv_cudaarithm opencv_cudafilters)
#   endif()
#   if(cpp_sample MATCHES "/viz/")
#   target_link_libraries(${tgt} PRIVATE ${VTK_LIBRARIES})
#     target_compile_definitions(${tgt} PRIVATE -DUSE_VTK)
#   endif()
#   if(HAVE_OPENGL AND cpp_sample MATCHES "detect_mser")
#     target_compile_definitions(${tgt} PRIVATE HAVE_OPENGL)
#     target_link_libraries(${tgt} PRIVATE "${OPENGL_LIBRARIES}")
#   endif()

endforeach()

# # Declare the executable target built from your sources
# add_executable(opencv_example example.cpp)

# # Link your application with OpenCV libraries
# target_link_libraries(opencv_example PRIVATE ${OpenCV_LIBS})
