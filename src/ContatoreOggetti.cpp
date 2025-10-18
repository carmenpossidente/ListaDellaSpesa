#include "ContatoreOggetti.h"
#include <iostream>

ContatoreOggetti::ContatoreOggetti() : numeroOggetti(0) {}

void ContatoreOggetti::aggiorna(const std::string& messaggio) {
    std::cout << "[Contatore] Ricevuto: " << messaggio << std::endl;
    if (messaggio.find("aggiunto") != std::string::npos) {
        numeroOggetti++;
        std::cout << "[Contatore] Incrementato a: " << numeroOggetti << std::endl;
    } else if (messaggio.find("rimosso") != std::string::npos) {
        if (numeroOggetti > 0) {
            numeroOggetti--;
            std::cout << "[Contatore] Decrementato a: " << numeroOggetti << std::endl;
        }
    }
}

std::size_t ContatoreOggetti::getNumeroOggetti() const {
    return numeroOggetti;
}
