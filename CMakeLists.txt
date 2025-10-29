cmake_minimum_required(VERSION 3.20)
project(lista_spesa)

set(CMAKE_CXX_STANDARD 20)

# Sottodirectory
add_subdirectory(src)
add_subdirectory(external/googletest)
add_subdirectory(test)

# Eseguiabile CONSOLE
add_executable(lista_spesa_console src/main.cpp)
target_link_libraries(lista_spesa_console lista_spesa_lib)
