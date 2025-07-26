cmake_minimum_required(VERSION 3.31)
project(lista_spesa)

set(CMAKE_CXX_STANDARD 20)

# Aggiungi il percorso degli header di nlohmann_json
include_directories(${CMAKE_SOURCE_DIR}/external)

# Libreria interna
add_subdirectory(src)

# Test framework
add_subdirectory(external/googletest)

# Eseguiabile
add_executable(lista_spesa
        src/main.cpp
        src/Oggetto.h
        src/Oggetto.cpp
        test/test_oggetto.cpp
)

# Collega la libreria interna
target_link_libraries(lista_spesa lista_spesa_lib)

# Test
enable_testing()
add_subdirectory(test)