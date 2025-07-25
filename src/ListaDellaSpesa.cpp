#include "ListaDellaSpesa.h"
#include "ContatoreOggetti.h"
#include <algorithm>

void ListaDellaSpesa::aggiungiOggetto(const Oggetto &o) {
    // Cerca se esiste già un oggetto con lo stesso nome
    for (auto &oggetto : oggetti) {
        if (oggetto.getNome() == o.getNome()) {
            // Se esiste, aggiorna la quantità e notifica
            oggetto.setQuantita(oggetto.getQuantita() + o.getQuantita());
            notificaObservers();
            return;
        }
    }

    // Se non esiste, aggiungilo normalmente
    oggetti.push_back(o);
    notificaObservers();
}


void ListaDellaSpesa::rimuoviOggetto(const std::string& nome) {
    oggetti.erase(std::remove_if(oggetti.begin(), oggetti.end(),
                                 [&nome](const Oggetto& o) {
                                     return o.getNome() == nome;
                                 }), oggetti.end());
    notificaObservers();
}

const std::vector<Oggetto>& ListaDellaSpesa::getOggetti() const {
    return oggetti;
}

void ListaDellaSpesa::aggiungiObserver(std::shared_ptr<ContatoreOggetti> obs) {
    observers.push_back(obs);
}

void ListaDellaSpesa::rimuoviObserver(std::shared_ptr<ContatoreOggetti> obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void ListaDellaSpesa::notificaObservers() const {
    for (const auto& obs : observers) {
        obs->aggiorna(oggetti);
    }
}
