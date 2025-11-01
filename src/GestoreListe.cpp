#include <iostream>
#include "GestoreListe.h"

GestoreListe::GestoreListe() {}

void GestoreListe::annullaCondivisioneUtenteCorrente(const std::string& nomeLista, const std::string& altroUtente) {
    if (!utenteCorrente) {
        std::cout << "[ERRORE] Nessun utente loggato" << std::endl;
        return;
    }

    auto lista = utenteCorrente->getListaPerNome(nomeLista);
    auto altroUtentePtr = getUtente(altroUtente);

    if (lista && altroUtentePtr) {
        // Rimuovi l'altro utente come observer e rimuovi la lista dalle sue condivise
        lista->rimuoviObserver(altroUtentePtr);
        altroUtentePtr->rimuoviListaCondivisa(lista);
        std::cout << "[DEBUG] Condivisione annullata" << std::endl;
    } else {
        if (!lista) {
            std::cout << "[ERRORE] Lista '" << nomeLista << "' non trovata" << std::endl;
        }
        if (!altroUtentePtr) {
            std::cout << "[ERRORE] Utente '" << altroUtente << "' non trovato" << std::endl;
        }
    }
}

void GestoreListe::registraUtente(const std::string& username) {
    if (utenti.find(username) == utenti.end()) {
        utenti[username] = std::make_shared<Utente>(username);
    }
}

bool GestoreListe::login(const std::string& username) {
    auto it = utenti.find(username);
    if (it != utenti.end()) {
        utenteCorrente = it->second;
        return true;
    }
    return false;
}
std::shared_ptr<Utente> GestoreListe::getUtenteCorrente() const {
    return utenteCorrente;
}

std::shared_ptr<Utente> GestoreListe::getUtente(const std::string& username) {
    auto it = utenti.find(username);
    return (it != utenti.end()) ? it->second : nullptr;
}

void GestoreListe::logout() {
    utenteCorrente = nullptr;
}

std::shared_ptr<ListaDellaSpesa> GestoreListe::creaListaPerUtenteCorrente(const std::string& nomeLista) {
    if (utenteCorrente) {
        return utenteCorrente->creaLista(nomeLista);
    }
    return nullptr;
}

void GestoreListe::condividiListaUtenteCorrente(const std::string& nomeLista, const std::string& altroUtente) {
    if (!utenteCorrente) {
        std::cout << "[ERRORE] Nessun utente loggato" << std::endl;
        return;
    }

    // Cerca la lista nelle liste personali dell'utente corrente
    auto lista = utenteCorrente->getListaPerNome(nomeLista);

    // Ottieni il puntatore all'altro utente
    auto altroUtentePtr = getUtente(altroUtente);

    if (lista && altroUtentePtr) {
        // Condividi la lista
        utenteCorrente->condividiLista(nomeLista, altroUtentePtr);

        std::cout << "[DEBUG] GestoreListe: condivisione eseguita" << std::endl;
    } else {
        if (!lista) {
            std::cout << "[ERRORE] Lista '" << nomeLista << "' non trovata" << std::endl;
        }
        if (!altroUtentePtr) {
            std::cout << "[ERRORE] Utente '" << altroUtente << "' non trovato" << std::endl;
        }
    }
}


