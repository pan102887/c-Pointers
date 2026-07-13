cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(c-demo LANGUAGES C VERSION 0.1.0)

find_package(Threads REQUIRED)

option(CP_BUILD_TESTS "Build unit tests" OFF)

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

list(FILTER PROJECT_SOURCE_FILES EXCLUDE REGEX ".*/src/main\\.c$")

set(PROJECT_INCLUDE_DIRS "")
foreach(PROJECT_SOURCE ${PROJECT_SOURCE_FILES})
    get_filename_component(PROJECT_SOURCE_DIR "${PROJECT_SOURCE}" DIRECTORY)
    list(APPEND PROJECT_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}")
endforeach()
list(REMOVE_DUPLICATES PROJECT_INCLUDE_DIRS)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC MICRO=100)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads m)

if(CP_BUILD_TESTS)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/test/*.c"
        "${CMAKE_SOURCE_DIR}/test/*.h"
    )

    add_executable(${PROJECT_NAME}-tests ${PROJECT_SOURCE_FILES} ${TEST_SOURCES})
    target_compile_definitions(${PROJECT_NAME}-tests PRIVATE CP_ENABLE_TESTS MICRO=100)
    target_include_directories(${PROJECT_NAME}-tests PRIVATE
        ${PROJECT_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/test"
    )
    target_link_libraries(${PROJECT_NAME}-tests PRIVATE Threads::Threads m)

    add_test(NAME ${PROJECT_NAME}-tests COMMAND ${PROJECT_NAME}-tests --run_all)
    set_tests_properties(${PROJECT_NAME}-tests PROPERTIES
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()
