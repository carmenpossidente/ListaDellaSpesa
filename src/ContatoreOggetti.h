#ifndef CONTATOREOGGETTI_H
#define CONTATOREOGGETTI_H

#include "Observer.h"
#include <cstddef>
#include <string>
#include <vector>
#include <map>

class ContatoreOggetti : public Observer {
private:
    int numeroDaAcquistare;
    std::map<std::string, bool> oggettiDaAcquistare;

public:
    ContatoreOggetti();

    void aggiorna(const std::string& messaggio) override;

    // Getter per il numero di oggetti da acquistare
    int getNumeroDaAcquistare() const;

    // Getter per la lista degli oggetti da acquistare
    std::vector<std::string> getListaOggettiDaAcquistare() const;

    // Getter per tutti gli oggetti con il loro stato
    std::map<std::string, bool> getOggettiConStato() const;

    // Verifica se un oggetto è da acquistare
    bool isDaAcquistare(const std::string& nome) const;
};

#endif
