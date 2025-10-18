#include "GestoreListe.h"

GestoreListe::GestoreListe() {}

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

void GestoreListe::creaListaPerUtenteCorrente(const std::string& nomeLista) {
    if (utenteCorrente) {
        utenteCorrente->creaLista(nomeLista);
    }
}

void GestoreListe::condividiListaUtenteCorrente(const std::string& nomeLista, const std::string& altroUtente) {
    // Implementazione placeholder
    // Qui dovresti trovare l'altro utente e condividere la lista
}

