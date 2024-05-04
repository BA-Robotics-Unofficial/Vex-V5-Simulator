cmake_minimum_required(VERSION 3.22)
project(VexSim)

set(CMAKE_CXX_STANDARD 11)

include_directories("inc/" "inc/vex")

add_executable(VexSim "src/main.cpp" 
"inc/Vex/vex.h"
"inc/Vex/vex.cpp" "inc/vex/utils.h")

target_link_libraries(VexSim PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/SDL3.lib
        ${CMAKE_SOURCE_DIR}/lib/SDL3_ttf.lib
        ${CMAKE_SOURCE_DIR}/lib/SDL3_image.lib
)



# Set the output directory for the executable
set_target_properties(VexSim PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)
