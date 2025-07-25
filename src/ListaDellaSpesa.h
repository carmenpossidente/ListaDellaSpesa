#ifndef LISTA_DELLA_SPESA_H
#define LISTA_DELLA_SPESA_H

#include <vector>
#include <string>
#include <memory>
#include "Oggetto.h"
#include "Observer.h"
#include "ContatoreOggetti.h"

class ListaDellaSpesa {
private:
    std::vector<Oggetto> oggetti;
    std::vector<std::shared_ptr<ContatoreOggetti>> observers;

    void notificaObservers() const;

public:
    void aggiungiOggetto(const Oggetto& o);
    void rimuoviOggetto(const std::string& nome);
    const std::vector<Oggetto>& getOggetti() const;

    void aggiungiObserver(std::shared_ptr<ContatoreOggetti> obs);
    void rimuoviObserver(std::shared_ptr<ContatoreOggetti> obs);
};

#endif
