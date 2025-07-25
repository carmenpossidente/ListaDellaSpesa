# test/test_oggetto.cpp
add_executable(test_oggetto test_oggetto.cpp)
target_link_libraries(test_oggetto gtest gtest_main lista_spesa_lib)

include(GoogleTest)
gtest_discover_tests(test_oggetto)

# test/test_contatore.cpp
add_executable(test_contatore test_contatore.cpp)
target_link_libraries(test_contatore gtest gtest_main lista_spesa_lib)
add_test(NAME test_contatore COMMAND test_contatore)

# test/test_listadellaspesa.cpp
add_executable(test_listadellaspesa test_listadellaspesa.cpp)
target_link_libraries(test_listadellaspesa gtest gtest_main lista_spesa_lib)
add_test(NAME test_listadellaspesa COMMAND test_listadellaspesa)
