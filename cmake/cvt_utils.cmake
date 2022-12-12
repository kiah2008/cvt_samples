macro(cvt_update VAR)
  if(NOT DEFINED ${VAR})
    if("x${ARGN}" STREQUAL "x")
      set(${VAR} "")
    else()
      set(${VAR} ${ARGN})
    endif()
  else()
    #cvt_debug_message("Preserve old value for ${VAR}: ${${VAR}}")
  endif()
endmacro()

# Utility function: adds sample executable target with name "example_<group>_<file_name>"
# Usage:
#   cvt_sample_define(<output target> <relative filename> <group>)
function(cvt_sample_define out_target source sub)


  # Find OpenCV, you may need to set OpenCV_DIR variable
  # to the absolute path to the directory containing OpenCVConfig.cmake file
  # via the command line or GUI
  find_package(OpenCV REQUIRED)

  # If the package has been found, several variables will
  # be set, you can find the full list with descriptions
  # in the OpenCVConfig.cmake file.
  # Print some message showing some of them
  message(STATUS "====OpenCV library status:")
  message(STATUS "    config: ${OpenCV_DIR}")
  message(STATUS "    version: ${OpenCV_VERSION}")
  message(STATUS "    libraries: ${OpenCV_LIBS}")
  message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
  message(STATUS "    linker libraries: ${OPENCV_LINKER_LIBS}")
  message(STATUS "    CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

  set(OPENCV_CPP_SAMPLES_REQUIRED_DEPS
    opencv_core
    opencv_imgproc
    opencv_flann
    opencv_imgcodecs
    opencv_videoio
    opencv_highgui
    opencv_ml
    opencv_video
    opencv_objdetect
    opencv_photo
    opencv_features2d
    opencv_calib3d
    opencv_stitching
    opencv_dnn
  )

  get_filename_component(name "${source}" NAME_WE)
  set(the_target "example_${sub}_${name}")
  message(STATUS "Example: ${the_target}    (${source})")

  add_executable(${the_target} "${source}")
  if(TARGET Threads::Threads AND NOT OPENCV_EXAMPLES_DISABLE_THREADS)
    target_link_libraries(${the_target} PRIVATE Threads::Threads)
  endif()

  target_link_libraries(${the_target} PRIVATE ${OpenCV_LIBS} ${OPENCV_CPP_SAMPLES_REQUIRED_DEPS})
  target_include_directories(${the_target} PRIVATE "${OpenCV_INCLUDE_DIRS}")

  set_target_properties(${the_target} PROPERTIES PROJECT_LABEL "(sample) ${name}")
  if(ENABLE_SOLUTION_FOLDERS)
    set_target_properties(${the_target} PROPERTIES FOLDER "samples/${sub}")
  endif()
  if(WIN32 AND MSVC AND NOT BUILD_SHARED_LIBS)
    set_target_properties(${the_target} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
  endif()
  # Should be usable in stand-alone build scenario
  if(NOT DEFINED CVT_SAMPLES_BIN_INSTALL_PATH)
    set(CVT_SAMPLES_BIN_INSTALL_PATH "samples")
  endif()
  install(TARGETS ${the_target} RUNTIME DESTINATION "${CVT_SAMPLES_BIN_INSTALL_PATH}/${sub}" COMPONENT samples)


  # Add single target to build all samples in the group: 'make cvt_samples_cpp'
  set(parent_target cvt_samples_${sub})
  if(NOT TARGET ${parent_target})
    add_custom_target(${parent_target})
    if(TARGET cvt_samples)
      add_dependencies(cvt_samples ${parent_target})
    endif()
  endif()
  add_dependencies(${parent_target} ${the_target})
  # refect to parent scope
  set(${out_target} ${the_target} PARENT_SCOPE)
endfunction()


function(cvt_define_executeable out_target source sub)
  get_filename_component(name "${source}" NAME_WE)
  set(the_target "${sub}_${name}")
  message(STATUS "Example: ${the_target}    (${source})")
  if (NOT OpenCV_FOUND) 
    MESSAGE(FATAL_ERROR "not found opencv")
    return()
  endif()

  add_executable(${the_target} "${source}")
  target_link_libraries(${the_target} PUBLIC ${OpenCV_LIBS} ${deps})
  target_include_directories(${the_target} PRIVATE ${OpenCV_INCLUDE_DIRS})

  if(TARGET Threads::Threads AND NOT OPENCV_EXAMPLES_DISABLE_THREADS)
    target_link_libraries(${the_target} PRIVATE Threads::Threads)
  endif()

  set_target_properties(${the_target} PROPERTIES PROJECT_LABEL "(sample) ${name}")
  

  # if(ENABLE_SOLUTION_FOLDERS)
  #   set_target_properties(${the_target} PROPERTIES FOLDER "samples/${sub}")
  # endif()

  if(WIN32 AND MSVC AND NOT BUILD_SHARED_LIBS)
    set_target_properties(${the_target} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
  endif()

  # Should be usable in stand-alone build scenario
  if(NOT DEFINED CVT_SAMPLES_BIN_INSTALL_PATH)
    set(CVT_SAMPLES_BIN_INSTALL_PATH "cpp")
  endif()
  
  install(TARGETS ${the_target} RUNTIME DESTINATION "${CVT_SAMPLES_BIN_INSTALL_PATH}/${sub}" COMPONENT samples)


  # Add single target to build all samples in the group: 'make cvt_samples_cpp'
  set(parent_target cvt_samples_${sub})
  if(NOT TARGET ${parent_target})
    add_custom_target(${parent_target})
    if(TARGET cvt_samples)
      add_dependencies(cvt_samples ${parent_target})
    endif()
  endif()
  add_dependencies(${parent_target} ${the_target})
  # refect to parent scope
  set(${out_target} ${the_target} PARENT_SCOPE)
endfunction()