#include "Utente.h"
#include <iostream>

Utente::Utente(const std::string& username) : username(username) {}

void Utente::aggiorna(const std::string& messaggio) {
    std::cout << "[Notifica Observer] " << messaggio << std::endl;
}

std::shared_ptr<ListaDellaSpesa> Utente::creaLista(const std::string& nomeLista) {
    auto nuovaLista = std::make_shared<ListaDellaSpesa>(nomeLista, username);
    listePersonali.push_back(nuovaLista);
    std::cout << "Lista '" << nomeLista << "' creata per " << username << std::endl;
    return nuovaLista;
}

void Utente::condividiLista(const std::string& nomeLista, std::shared_ptr<Utente> altroUtente) {
    std::shared_ptr<ListaDellaSpesa> lista = nullptr;

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

void Utente::rimuoviListaCondivisa(std::shared_ptr<ListaDellaSpesa> lista) {
    for (auto it = listeCondivise.begin(); it != listeCondivise.end(); ++it) {
        if (*it == lista) {
            listeCondivise.erase(it);
            return;
        }
    }
}

void Utente::eliminaLista(const std::string& nomeLista) {
    for (auto it = listePersonali.begin(); it != listePersonali.end(); ++it) {
        if ((*it)->getNome() == nomeLista) {
            listePersonali.erase(it);
            std::cout << "Lista '" << nomeLista << "' eliminata per " << username << std::endl;
            return;
        }
    }
    std::cout << "[ERRORE] Lista '" << nomeLista << "' non trovata" << std::endl;
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