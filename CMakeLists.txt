cmake_minimum_required(VERSION 3.29)

project(PkFramework VERSION 2.0.0 LANGUAGES CXX)

if (WIN32)
    set(VCPKG_OS "windows")
elseif (APPLE)
    set(VCPKG_OS "macos")
elseif (UNIX)
    set(VCPKG_OS "linux")
endif ()

set(ARCH "")
if (CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|x64")
    set(ARCH "x64")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686|x86")
    set(ARCH "x86")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64|aarch64")
    set(ARCH "arm64")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "ARM")
    set(ARCH "arm")
else ()
    set(ARCH "unknown")
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/vcpkg_installed/${ARCH}-${VCPKG_OS}")

add_library(PkFramework SHARED
        src/pk/PkFramework.cpp
        src/pk/helpers/cli.cpp
        src/pk/core/Package.cpp
        src/pk/core/ConfigProvider.cpp
        src/pk/core/Repository.cpp
        src/pk/core/Utils.cpp
        src/include/helper_cli.hpp
        src/include/m_config.hpp
        src/include/m_os.hpp
        src/include/m_package.hpp
        src/include/m_repository.hpp
        src/include/PkFramework.hpp
        src/include/utils.hpp
)

set_target_properties(PkFramework PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        POSITION_INDEPENDENT_CODE ON
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Include directories for PkFramework
target_include_directories(PkFramework PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/include>
        $<INSTALL_INTERFACE:include>
)

find_package(jsoncpp CONFIG REQUIRED)
find_package(argh CONFIG REQUIRED)

set_target_properties(JsonCpp::JsonCpp PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(PkFramework PRIVATE JsonCpp::JsonCpp argh)

set_target_properties(PkFramework PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if (WIN32)
    add_custom_command(TARGET PkFramework POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:PkFramework>
            $<TARGET_FILE_DIR:PkFramework>
    )
endif ()


add_subdirectory(src/cli)
