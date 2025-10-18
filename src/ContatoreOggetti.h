#ifndef CONTATOREOGGETTI_H
#define CONTATOREOGGETTI_H

#include "Observer.h"
#include <cstddef>
#include <string>
#include <vector>
#include "Oggetto.h"

class ContatoreOggetti : public Observer {
private:
    std::size_t numeroOggetti;

public:
    ContatoreOggetti();

    void aggiorna(const std::string& messaggio) override;

    std::size_t getNumeroOggetti() const;
};

#endif
