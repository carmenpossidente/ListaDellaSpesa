#include "ListaDellaSpesa.h"
#include "ContatoreOggetti.h"
#include "../external/nlohmann/json.hpp"
#include <algorithm>
#include <fstream>

using json = nlohmann::json;

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


void ListaDellaSpesa::salvaSuFile(const std::string& filename) const {
    json j_array = json::array();
    for (const auto& ogg : oggetti) {
        json j_ogg;
        j_ogg["nome"] = ogg.getNome();
        j_ogg["categoria"] = ogg.getCategoria();
        j_ogg["quantita"] = ogg.getQuantita();
        j_array.push_back(j_ogg);
    }

    std::ofstream out(filename);
    out << j_array.dump(4);  // pretty print con indentazione
}

void ListaDellaSpesa::caricaDaFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;

    json j_array;
    in >> j_array;

    oggetti.clear();

    for (const auto& j_ogg : j_array) {
        Oggetto o(
                j_ogg["nome"].get<std::string>(),
                j_ogg["categoria"].get<std::string>(),
                j_ogg["quantita"].get<int>()
        );
        oggetti.push_back(o);
    }

    notificaObservers();  // notifica dopo caricamento
}
