# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Define project name
project(cvt_base)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} base_cpp)

add_library(cvt_base  
    STATIC ${base_cpp}
    )

set_target_properties(cvt_base
PROPERTIES
OUTPUT_NAME   "cvt_base"
PREFIX        "lib"
PUBLIC_HEADER "cvt_base.h"
)

