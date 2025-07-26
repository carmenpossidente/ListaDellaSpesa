add_library(lista_spesa_lib
        Oggetto.cpp
        ListaDellaSpesa.cpp
        ListaDellaSpesa.h
        ContatoreOggetti.cpp
        Observer.h
        ContatoreOggetti.h
)

# Includi i percorsi necessari (sia per la libreria che per nlohmann_json)
target_include_directories(lista_spesa_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/external
)

