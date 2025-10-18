# Test per Oggetto
add_executable(test_oggetto test_oggetto.cpp)
target_link_libraries(test_oggetto gtest gtest_main lista_spesa_lib)
target_include_directories(test_oggetto PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Test per ContatoreOggetti
add_executable(test_contatore test_contatore.cpp)
target_link_libraries(test_contatore gtest gtest_main lista_spesa_lib)
target_include_directories(test_contatore PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Test per ListaDellaSpesa
add_executable(test_listadellaspesa test_listadellaspesa.cpp)
target_link_libraries(test_listadellaspesa gtest gtest_main lista_spesa_lib)
target_include_directories(test_listadellaspesa PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Test per Utente
add_executable(test_utente test_utente.cpp)
target_link_libraries(test_utente gtest gtest_main lista_spesa_lib)
target_include_directories(test_utente PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Test per GestoreListe
add_executable(test_gestore test_gestore.cpp)
target_link_libraries(test_gestore gtest gtest_main lista_spesa_lib)
target_include_directories(test_gestore PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Aggiungi tutti i test
include(GoogleTest)
gtest_discover_tests(test_oggetto)
gtest_discover_tests(test_contatore)
gtest_discover_tests(test_listadellaspesa)
gtest_discover_tests(test_utente)
gtest_discover_tests(test_gestore)