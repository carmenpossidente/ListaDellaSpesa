#ifndef CLI_H
#define CLI_H

#include "GestoreListe.h"
#include <iostream>
#include <memory>

class CLI {
private:
    GestoreListe gestore;

    void mostraMenuPrincipale();
    void gestisciLogin();
    void gestisciRegistrazione();
    void gestisciListe();
    void gestisciOggetti(std::shared_ptr<ListaDellaSpesa> lista);
    void pulisciSchermo();

public:
    void avvia();
};

#endif