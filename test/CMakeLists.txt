add_executable(test_oggetto test_oggetto.cpp)

target_link_libraries(test_oggetto
        gtest
        gtest_main
        lista_spesa_lib
)

include(GoogleTest)
gtest_discover_tests(test_oggetto)
