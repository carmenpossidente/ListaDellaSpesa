#ifndef CONTATOREOGGETTI_H
#define CONTATOREOGGETTI_H

#include "Observer.h"
#include <cstddef>

class ContatoreOggetti : public Observer {
private:
    std::size_t numeroOggetti;

public:
    ContatoreOggetti();

    void aggiorna(const std::vector<Oggetto>& nuovaLista) override;

    std::size_t getNumeroOggetti() const;
};

#endif
