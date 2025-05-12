cmake_minimum_required(VERSION 3.31)

project(PkFramework VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(PkFramework SHARED
        src/pk/PkFramework.cpp
        src/pk/helpers/cli.cpp
        src/pk/core/Package.cpp
        src/pk/core/ConfigProvider.cpp
        src/pk/core/Repository.cpp
)

set_target_properties(PkFramework PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        POSITION_INDEPENDENT_CODE ON
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "Disable jsoncpp tests" FORCE)

# Include directories for PkFramework
target_include_directories(PkFramework PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/include>
        $<INSTALL_INTERFACE:include>
)

# Dynamic library resolver for libs/*
file(GLOB LIB_DIRS "${CMAKE_CURRENT_LIST_DIR}/libs/*")

set(LIB_TARGETS "")

foreach (LIB_DIR ${LIB_DIRS})
    if (IS_DIRECTORY ${LIB_DIR})
        get_filename_component(LIB_NAME ${LIB_DIR} NAME)

        if (EXISTS "${LIB_DIR}/CMakeLists.txt")
            message(STATUS "Found standalone CMake library: ${LIB_NAME} at ${LIB_DIR}")
            add_subdirectory(${LIB_DIR})
            # Handle special cases like JsonCpp where the target name might differ
            if (LIB_NAME STREQUAL "jsoncpp" AND TARGET jsoncpp_lib)
                list(APPEND LIB_TARGETS jsoncpp_lib)
                set_target_properties(jsoncpp_lib PROPERTIES
                        CXX_STANDARD 23
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF
                        POSITION_INDEPENDENT_CODE ON
                        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
                )
                include_directories(${LIB_NAME} INTERFACE ${LIB_DIR}/include)
            elseif (TARGET ${LIB_NAME})
                list(APPEND LIB_TARGETS ${LIB_NAME})
            endif ()
        else ()
            file(GLOB LIB_HEADERS "${LIB_DIR}/*.h" "${LIB_DIR}/*.hpp")
            if (LIB_HEADERS)
                message(STATUS "Found header-only library: ${LIB_NAME} at ${LIB_DIR}")
                add_library(${LIB_NAME} INTERFACE)
                target_include_directories(${LIB_NAME} INTERFACE ${LIB_DIR})
                list(APPEND LIB_TARGETS ${LIB_NAME})
            endif ()
        endif ()
    endif ()
endforeach ()

list(JOIN LIB_TARGETS " " LIB_TARGETS_STR)
foreach (LIB_TARGET ${LIB_TARGETS})
    if (TARGET ${LIB_TARGET})
        target_link_libraries(PkFramework PRIVATE ${LIB_TARGET})
    endif ()
endforeach ()

add_subdirectory(src/cli)

set_target_properties(PkFramework PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set_target_properties(PkCli PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)