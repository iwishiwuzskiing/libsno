# Simple CMakeLists.txt file for basic library. Builds library from .cpp files
# in ./src and headers in ./include
cmake_minimum_required(VERSION 2.8)

#################################
## Define the project
set(project_name sno)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My Library")
#Directory for the rest of our CMake stuff
set(cmake_dir /usr/local/share/cmake)
include(${cmake_dir}/pimpl_lib.cmake)
