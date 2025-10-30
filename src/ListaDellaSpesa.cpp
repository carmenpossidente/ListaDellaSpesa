#include "ListaDellaSpesa.h"
#include "../external/nlohmann/json.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

ListaDellaSpesa::ListaDellaSpesa(const std::string& nome, const std::string& proprietario)
        : nomeLista(nome), proprietario(proprietario) {}

void ListaDellaSpesa::setNome(const std::string& nome) { nomeLista = nome; }

std::string ListaDellaSpesa::getNome() const { return nomeLista; }

void ListaDellaSpesa::setProprietario(const std::string& prop) { proprietario = prop; }

std::string ListaDellaSpesa::getProprietario() const { return proprietario; }

void ListaDellaSpesa::aggiungiOggetto(const Oggetto &o) {
    // Controlla se l'oggetto esiste già
    for (auto &oggetto : oggetti) {
        if (oggetto.getNome() == o.getNome() && oggetto.getCategoria() == o.getCategoria()) {
            int vecchiaQuantita = oggetto.getQuantita();
            oggetto.setQuantita(vecchiaQuantita + o.getQuantita());

            // Notifica AGGIORNAMENTO (quantità modificata, ma oggetto già esistente)
            notificaObservers("Oggetto aggiornato: " + o.getNome() +
                              " (nuova quantità: " + std::to_string(oggetto.getQuantita()) + ")");

            if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
            return;
        }
    }
    // Se non esiste, aggiungi nuovo oggetto (sempre come NON acquistato)
    oggetti.push_back(o);

    // Notifica nuovo oggetto da acquistare
    notificaObservers("Oggetto aggiunto: " + o.getNome());

    if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
}

void ListaDellaSpesa::rimuoviOggetto(const std::string& nome) {
    oggetti.erase(std::remove_if(oggetti.begin(), oggetti.end(),
                                 [&nome](const Oggetto& o) {
                                     return o.getNome() == nome;
                                 }), oggetti.end());

    // Notifica rimozione
    notificaObservers("Oggetto rimosso: " + nome);

    if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
}

void ListaDellaSpesa::marcaAcquistato(const std::string& nome, bool acquistato) {
    for (auto& obj : oggetti) {
        if (obj.getNome() == nome) {
            bool vecchioStato = obj.isAcquistato();
            obj.setAcquistato(acquistato);

            // Notifica solo se c'è un cambio di stato
            if (vecchioStato != acquistato) {
                if (acquistato) {
                    notificaObservers("Oggetto marcato_acquistato: " + nome);
                } else {
                    notificaObservers("Oggetto marcato_non_acquistato: " + nome);
                }
            }

            if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
            break;
        }
    }
}

void ListaDellaSpesa::setFilename(const std::string& filename) {
    defaultFilename = filename;
}

const std::vector<Oggetto>& ListaDellaSpesa::getOggetti() const {
    return oggetti;
}

void ListaDellaSpesa::aggiungiObserver(std::shared_ptr<Observer> obs) {
    observers.push_back(obs);
}

void ListaDellaSpesa::rimuoviObserver(std::shared_ptr<Observer> obs) {
    auto it = std::find_if(observers.begin(), observers.end(),
                           [&](const std::shared_ptr<Observer>& o) { return o == obs; });
    if (it != observers.end()) {
        observers.erase(it);
    } else {
        std::cerr << "Observer non trovato.\n";
    }
}


void ListaDellaSpesa::notificaObservers(const std::string& messaggio) {
    for (auto& obs : observers) {
        obs->aggiorna(messaggio);
    }
}

void ListaDellaSpesa::salvaSuFile(const std::string& filename) const {
    json j_array = json::array();
    for (const auto& ogg : oggetti) {
        json j_ogg;
        j_ogg["nome"] = ogg.getNome();
        j_ogg["categoria"] = ogg.getCategoria();
        j_ogg["quantita"] = ogg.getQuantita();
        j_ogg["acquistato"] = ogg.isAcquistato();
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

    // Prima notifica il reset
    notificaObservers("Lista caricata da file");

    // Poi carica gli oggetti e notifica uno per uno
    for (const auto& j_ogg : j_array) {
        Oggetto o(
                j_ogg["nome"].get<std::string>(),
                j_ogg["categoria"].get<std::string>(),
                j_ogg["quantita"].get<int>()
        );

        bool acquistato = false;
        if (j_ogg.contains("acquistato")) {
        acquistato = j_ogg["acquistato"].get<bool>();
        o.setAcquistato(acquistato);
        }

        oggetti.push_back(o);

        // Notifica l'aggiunta con lo stato corretto
        if (acquistato) {
            notificaObservers("Oggetto aggiunto: " + o.getNome());
            notificaObservers("Oggetto marcato_acquistato: " + o.getNome());
        } else {
            notificaObservers("Oggetto aggiunto: " + o.getNome());
        }
    }
}

std::vector<Oggetto> ListaDellaSpesa::filtraPerCategoria(const std::string& cat) const {
    std::vector<Oggetto> result;
    for (const auto& o : oggetti) {
        if (o.getCategoria() == cat) {
            result.push_back(o);
        }
    }
    return result;
}

std::map<std::string, int> ListaDellaSpesa::contaPerCategoria() const {
    std::map<std::string, int> conteggio;
    for (const auto& o : oggetti) {
        conteggio[o.getCategoria()] += o.getQuantita();
    }
    return conteggio;
}

int ListaDellaSpesa::getQuantitaDaAcquistare() const {
    int sum = 0;
    for (const auto& o : oggetti) {
        if (!o.isAcquistato()) {
            sum += o.getQuantita();
        }
    }
    return sum;
}
