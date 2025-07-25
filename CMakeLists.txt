cmake_minimum_required(VERSION 3.31)
project(lista_spesa)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_executable(lista_spesa src/main.cpp
        src/Oggetto.h
        src/Oggetto.cpp
        test/test_oggetto.cpp)

target_link_libraries(lista_spesa lista_spesa_lib)

add_subdirectory(external/googletest)

enable_testing()

add_subdirectory(test)


