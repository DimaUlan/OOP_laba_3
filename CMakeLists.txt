cmake_minimum_required(VERSION 3.14)
project(OOP_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
  "$<$<CONFIG:Debug>:/MDd>"
  "$<$<CONFIG:Release>:/MD>"
)

option(BUILD_TESTS "Build unit tests" ON)

include_directories(include)


add_executable(main
    src/main.cpp
    src/Array.cpp
    src/Rhombus.cpp
    src/Pentagon.cpp
    src/Trapezoid.cpp
)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(tests
        tests/tests.cpp
        src/Array.cpp
        src/Rhombus.cpp
        src/Pentagon.cpp
        src/Trapezoid.cpp
    )

    target_link_libraries(tests gtest gtest_main)

    enable_testing()
    add_test(NAME AllTests COMMAND tests)
endif()