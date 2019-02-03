cmake_minimum_required(VERSION 3.5)
project(List LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)

SET(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(core-files
Autocorrector.cpp
Autocorrector.hpp
utils.hpp)

add_executable(main
main.cpp
${core-files}
)

find_package(Threads REQUIRED)
target_link_libraries(main Threads::Threads)

set(binaries
cli
)


foreach(target ${BINARIES})
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
target_compile_options( ${target} PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic -lpthread)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
target_compile_options( ${target} PRIVATE /W4 )
target_compile_options( ${target} PRIVATE /utf-8 )
endif()
endforeach()


if ( CMAKE_BUILD_TYPE MATCHES "Release|RelWithDebInfo" )
message(STATUS "Registering the complexities test to CTest")
add_test(NAME complexities COMMAND tests-stage-5 [.long])
endif()
