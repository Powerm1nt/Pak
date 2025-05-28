cmake_minimum_required(VERSION 3.29)

project(Pak VERSION 2.0.0 LANGUAGES CXX)

if (WIN32)
    set(VCPKG_OS "windows")
elseif (APPLE)
    set(VCPKG_OS "osx")
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

add_library(Pak SHARED
        src/pk/Pak.cpp
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
        src/include/Pak.hpp
        src/include/utils.hpp
        src/include/pak_file.hpp
        src/include/m_file.hpp
        src/pk/core/File.cpp
        src/pk/core/SQLiteTransaction.cpp
        src/include/database.hpp
        src/include/fileutils.hpp
        src/include/m_object.hpp
        src/include/m_chunk.hpp
)

set_target_properties(Pak PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
        POSITION_INDEPENDENT_CODE ON
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Include directories for Pak
target_include_directories(Pak PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/include>
        $<INSTALL_INTERFACE:include>
)

find_package(jsoncpp CONFIG REQUIRED)
find_package(argh CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

set_target_properties(JsonCpp::JsonCpp PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(Pak PRIVATE
        JsonCpp::JsonCpp
        argh
        unofficial::sqlite3::sqlite3
        ZLIB::ZLIB
)

set_target_properties(Pak PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

if (WIN32)
    add_custom_command(TARGET Pak POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Pak>
            $<TARGET_FILE_DIR:Pak>
    )
endif ()


add_subdirectory(src/cli)
