cmake_minimum_required(VERSION 3.10.2)

project(cpp_course)

# Version number.
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)

set(CMAKE_CXX_CPPLINT "cpplint")

# GCC flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

# Include paths.
include_directories(
	include
)

# Library sources.
set(LIBRARY_SOURCES
	src/isometry.cpp
)

# Library creation.
add_library(isometry ${LIBRARY_SOURCES})

set_target_properties(isometry PROPERTIES CXX_CPPCHECK "cppcheck;--language=c++;--std=c++11;--enable=warning,style,performance,portability")
set_target_properties(isometry PROPERTIES CXX_CLANG_TIDY "clang-tidy;-checks=*,-fuchsia-overloaded-operator,-readability-else-after-*,-cert-err58-cpp")

# Includes GTest.
enable_testing()
add_subdirectory(test)