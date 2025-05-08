cmake_minimum_required(VERSION 3.31)

project(PkFramework VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB LIB_DIRS "${CMAKE_CURRENT_LIST_DIR}/libs/*")
foreach(LIB_DIR ${LIB_DIRS})
    if(IS_DIRECTORY ${LIB_DIR})
        get_filename_component(LIB_NAME ${LIB_DIR} NAME)

        file(GLOB LIB_HEADERS "${LIB_DIR}/*.h" "${LIB_DIR}/*.hpp")
        if(LIB_HEADERS)
            add_library(${LIB_NAME} INTERFACE)
            target_include_directories(${LIB_NAME} INTERFACE ${LIB_DIR})

            message(STATUS "Found library: ${LIB_NAME} at ${LIB_DIR}")
        endif()
    endif()
endforeach()

add_library(PkFramework SHARED src/pk/PkFramework.cpp)

set_target_properties(PkFramework PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)

foreach(LIB_DIR ${LIB_DIRS})
    if(IS_DIRECTORY ${LIB_DIR})
        get_filename_component(LIB_NAME ${LIB_DIR} NAME)
        if(TARGET ${LIB_NAME})
            target_link_libraries(PkFramework PRIVATE ${LIB_NAME})
        endif()
    endif()
endforeach()

target_include_directories(PkFramework PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/pk/include>
        $<INSTALL_INTERFACE:include>
)

add_subdirectory(src/cli)

set_target_properties(PkFramework PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(PkFramework PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(PkCli PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)