#include "Utente.h"
#include <iostream>

Utente::Utente(const std::string& username) : username(username) {}

void Utente::aggiorna(const std::string& messaggio) {
    std::cout << "[" << username << "] Notifica: " << messaggio << std::endl;
}

void Utente::creaLista(const std::string& nomeLista) {
    auto nuovaLista = std::make_shared<ListaDellaSpesa>(nomeLista, username);
    listePersonali.push_back(nuovaLista);
    std::cout << "Lista '" << nomeLista << "' creata per " << username << std::endl;
}

void Utente::condividiLista(const std::string& nomeLista, Utente* altroUtente) {
    auto lista = getListaPerNome(nomeLista);
    if (lista && altroUtente) {
        altroUtente->aggiungiListaCondivisa(lista);
        // Aggiungi observer per le notifiche
        lista->aggiungiObserver(std::make_shared<Utente>(*altroUtente));
        std::cout << "Lista '" << nomeLista << "' condivisa con " << altroUtente->getUsername() << std::endl;
    }
}

void Utente::aggiungiListaCondivisa(std::shared_ptr<ListaDellaSpesa> lista) {
    listeCondivise.push_back(lista);
}

std::string Utente::getUsername() const {
    return username;
}

std::shared_ptr<ListaDellaSpesa> Utente::getListaPerNome(const std::string& nome) {
    for (auto& lista : listePersonali) {
        if (lista->getNome() == nome) {
            return lista;
        }
    }
    for (auto& lista : listeCondivise) {
        if (lista->getNome() == nome) {
            return lista;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<ListaDellaSpesa>> Utente::getListePersonali() const {
    return listePersonali;
}

std::vector<std::shared_ptr<ListaDellaSpesa>> Utente::getListeCondivise() const {
    return listeCondivise;
}