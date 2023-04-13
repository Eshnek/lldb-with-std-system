cmake_minimum_required(VERSION 3.25)
project(test)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE Sources_Glob CONFIGURE_DEPENDS src/*.cxx)
add_executable(test ${Sources_Glob})
