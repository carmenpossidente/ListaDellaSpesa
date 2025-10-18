#include "ListaDellaSpesa.h"
#include "ContatoreOggetti.h"
#include "../external/nlohmann/json.hpp"
#include <algorithm>
#include <fstream>

using json = nlohmann::json;

ListaDellaSpesa::ListaDellaSpesa(const std::string& nome, const std::string& proprietario)
        : nomeLista(nome), proprietario(proprietario) {}

void ListaDellaSpesa::setNome(const std::string& nome) { nomeLista = nome; }
std::string ListaDellaSpesa::getNome() const { return nomeLista; }
void ListaDellaSpesa::setProprietario(const std::string& prop) { proprietario = prop; }
std::string ListaDellaSpesa::getProprietario() const { return proprietario; }

void ListaDellaSpesa::aggiungiOggetto(const Oggetto &o) {
    for (auto &oggetto : oggetti) {
        if (oggetto.getNome() == o.getNome()) {
            oggetto.setQuantita(oggetto.getQuantita() + o.getQuantita());
            notificaObservers("Oggetto aggiornato: " + o.getNome());
            if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
            return;
        }
    }

    oggetti.push_back(o);
    notificaObservers("Oggetto aggiunto: " + o.getNome());
    if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
}


void ListaDellaSpesa::rimuoviOggetto(const std::string& nome) {
    oggetti.erase(std::remove_if(oggetti.begin(), oggetti.end(),
                                 [&nome](const Oggetto& o) {
                                     return o.getNome() == nome;
                                 }), oggetti.end());
    notificaObservers("Oggetto rimosso: " + nome);
    if (!defaultFilename.empty()) salvaSuFile(defaultFilename);
}


void ListaDellaSpesa::setFilename(const std::string& filename) {
    defaultFilename = filename;
}

const std::vector<Oggetto>& ListaDellaSpesa::getOggetti() const {
    return oggetti;
}

void ListaDellaSpesa::aggiungiObserver(Observer* obs) {
    observers.push_back(obs);
}

void ListaDellaSpesa::rimuoviObserver(Observer* obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
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

    for (const auto& j_ogg : j_array) {
        Oggetto o(
                j_ogg["nome"].get<std::string>(),
                j_ogg["categoria"].get<std::string>(),
                j_ogg["quantita"].get<int>()
        );
        if (j_ogg.contains("acquistato")) {
            o.setAcquistato(j_ogg["acquistato"].get<bool>());
        }
        oggetti.push_back(o);
    }

    notificaObservers("Lista caricata da file");  // notifica dopo caricamento
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
