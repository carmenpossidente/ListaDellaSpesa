cmake_minimum_required(VERSION 3.31)
project(lista_spesa)

set(CMAKE_CXX_STANDARD 20)

# Percorso Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Aggiungi il percorso degli header
include_directories(${CMAKE_SOURCE_DIR}/external)

# Sottodirectory
add_subdirectory(src)
add_subdirectory(external/googletest)

# Eseguiabile CONSOLE
add_executable(lista_spesa_console src/main.cpp)
target_link_libraries(lista_spesa_console lista_spesa_lib)

# Eseguiabile GUI - ORDINE CORRETTO!
qt6_wrap_cpp(lista_spesa_gui_moc src/MainWindow.h)  # PRIMA il MOC!

add_executable(lista_spesa_gui
src/main_gui.cpp
src/MainWindow.cpp
${lista_spesa_gui_moc}  # AGGIUNGI i file MOC generati
)

# POI processa la UI
qt6_wrap_ui(lista_spesa_gui_ui src/mainwindow.ui)
target_sources(lista_spesa_gui PRIVATE ${lista_spesa_gui_ui})

# POI collega le librerie
target_link_libraries(lista_spesa_gui
Qt6::Widgets
lista_spesa_lib
)

# Includi le directory generate
target_include_directories(lista_spesa_gui PRIVATE
${CMAKE_CURRENT_BINARY_DIR}
)

# Test separati
add_executable(test_oggetto test/test_oggetto.cpp)
target_link_libraries(test_oggetto gtest gtest_main lista_spesa_lib)

add_executable(test_contatore test/test_contatore.cpp)
target_link_libraries(test_contatore gtest gtest_main lista_spesa_lib)

add_executable(test_listadellaspesa test/test_listadellaspesa.cpp)
target_link_libraries(test_listadellaspesa gtest gtest_main lista_spesa_lib)