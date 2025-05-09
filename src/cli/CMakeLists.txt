set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PkCli main.cpp)

target_link_libraries(PkCli PRIVATE PkFramework argh)
