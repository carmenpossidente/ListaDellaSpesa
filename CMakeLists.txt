cmake_minimum_required(VERSION 3.20)
project(lista_spesa)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_LIBRARY_PATH "C:/SFML-2.6.1/lib")
#set(CMAKE_INCLUDE_PATH "C:/SFML-2.6.1/include")

# Sottodirectory
add_subdirectory(src)
add_subdirectory(external/googletest)
add_subdirectory(test)

# Eseguiabile CONSOLE
add_executable(lista_spesa_console src/main.cpp)
target_link_libraries(lista_spesa_console lista_spesa_lib)

#add_executable(lista_spesa_gui src/main_gui.cpp src/Oggetto.cpp src/ListaDellaSpesa.cpp src/ContatoreOggetti.cpp  src/Utente.cpp src/GestoreListe.cpp)
#target_include_directories(lista_spesa_gui PRIVATE "C:/SFML-2.6.1/include" "${CMAKE_SOURCE_DIR}/external")
#target_link_directories(lista_spesa_gui PRIVATE "C:/SFML-2.6.1/lib")
#target_link_libraries(lista_spesa_gui "C:/SFML-2.6.1/lib/libsfml-graphics-d.a" "C:/SFML-2.6.1/lib/libsfml-window-d.a" "C:/SFML-2.6.1/lib/libsfml-system-d.a")

# Copia DLL
#add_custom_command(TARGET lista_spesa_gui POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory  "C:/SFML-2.6.1/bin"  $<TARGET_FILE_DIR:lista_spesa_gui>)