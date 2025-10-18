#include "Utente.h"
#include <iostream>

Utente::Utente(const std::string& username) : username(username) {}

void Utente::aggiorna(const std::string& messaggio) {
    std::cout << "[" << username << "] Notifica: " << messaggio << std::endl;
}

void Utente::creaLista(const std::string& nomeLista) {
    auto nuovaLista = std::make_shared<ListaDellaSpesa>();
    // Configura la lista qui se necessario
    listePersonali.push_back(nuovaLista);
}

std::shared_ptr<ListaDellaSpesa> Utente::getListaPerNome(const std::string& nome) {
    for (auto& lista : listePersonali) {
        // Dovresti aggiungere un metodo getName() a ListaDellaSpesa
        // Per ora restituiamo la prima
        return lista;
    }
    return nullptr;
}

std::vector<std::shared_ptr<ListaDellaSpesa>> Utente::getListePersonali() const {
    return listePersonali;
}

std::vector<std::shared_ptr<ListaDellaSpesa>> Utente::getListeCondivise() const {
    return listeCondivise;
}