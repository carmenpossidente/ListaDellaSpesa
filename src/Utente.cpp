#include "Utente.h"
#include <iostream>

Utente::Utente(const std::string& username) : username(username) {}

void Utente::aggiorna(const std::string& messaggio) {
    std::cout << "[" << username << "] Notifica: " << messaggio << std::endl;
}

std::shared_ptr<ListaDellaSpesa> Utente::creaLista(const std::string& nomeLista) {
    auto nuovaLista = std::make_shared<ListaDellaSpesa>(nomeLista, username);
    listePersonali.push_back(nuovaLista);
    std::cout << "Lista '" << nomeLista << "' creata per " << username << std::endl;
    return nuovaLista;
}

void Utente::condividiLista(const std::string& nomeLista, std::shared_ptr<Utente> altroUtente) {
    std::shared_ptr<ListaDellaSpesa> lista = nullptr;

    // ✅ CORRETTO: Cerca nelle liste PERSONALI, non in quelle condivise!
    for (const auto& l : listePersonali) {
        if (l->getNome() == nomeLista) {
            lista = l;
            break;
        }
    }

    if (lista && altroUtente) {
        // Aggiungi l'altro utente come observer (per le notifiche)
        lista->aggiungiObserver(altroUtente);

        // Aggiungi la lista alle liste condivise dell'altro utente
        altroUtente->aggiungiListaCondivisa(lista);

        std::cout << "[DEBUG] Lista '" << nomeLista << "' condivisa con "
                  << altroUtente->getUsername() << std::endl;
    } else {
        if (!lista) {
            std::cout << "[ERRORE] Lista '" << nomeLista << "' non trovata" << std::endl;
        }
        if (!altroUtente) {
            std::cout << "[ERRORE] Utente destinatario non valido" << std::endl;
        }
    }
}


void Utente::aggiungiListaCondivisa(std::shared_ptr<ListaDellaSpesa> lista) {
    listeCondivise.push_back(lista);
}

std::string Utente::getUsername() const {
    return username;
}

std::shared_ptr<ListaDellaSpesa> Utente::getListaPerNome(const std::string& nome) {
    // Cerca prima nelle liste personali
    for (auto& lista : listePersonali) {
        if (lista->getNome() == nome) {
            return lista;
        }
    }

    // Poi nelle liste condivise
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