cmake_minimum_required(VERSION 2.8)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
#  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
PROJECT(slce)
include(CheckIncludeFiles)
include(CheckCXXSourceCompiles)
enable_testing()
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -Werror")

set(CMAKE_VERBOSE_MAKEFILE OFF)
find_package(Boost 1.65.0 COMPONENTS unit_test_framework system filesystem REQUIRED )



INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} )
subdirs( include test )

