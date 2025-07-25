#include "ContatoreOggetti.h"

ContatoreOggetti::ContatoreOggetti() : numeroOggetti(0) {}

void ContatoreOggetti::aggiorna(const std::vector<Oggetto>& nuovaLista) {
    numeroOggetti = nuovaLista.size();
}

std::size_t ContatoreOggetti::getNumeroOggetti() const {
    return numeroOggetti;
}
