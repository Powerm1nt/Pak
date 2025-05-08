cmake_minimum_required(VERSION 3.31)

project(PKFramework VERSION 1.0.0 LANGUAGES CXX)

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

add_library(PKFramework SHARED library.cpp)

foreach(LIB_DIR ${LIB_DIRS})
    if(IS_DIRECTORY ${LIB_DIR})
        get_filename_component(LIB_NAME ${LIB_DIR} NAME)
        if(TARGET ${LIB_NAME})
            target_link_libraries(PKFramework PRIVATE ${LIB_NAME})
        endif()
    endif()
endforeach()

target_include_directories(PKFramework PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include>
)