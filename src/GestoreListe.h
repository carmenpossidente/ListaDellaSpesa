#ifndef LISTA_SPESA_GESTORELISTE_H
#define LISTA_SPESA_GESTORELISTE_H

#include "Utente.h"
#include <unordered_map>
#include <memory>

class GestoreListe {
private:
    std::unordered_map<std::string, std::shared_ptr<Utente>> utenti;
    std::shared_ptr<Utente> utenteCorrente;

public:
    GestoreListe();

    void registraUtente(const std::string& username);
    bool login(const std::string& username);
    void logout();

    std::shared_ptr<Utente> getUtenteCorrente() const;
    std::shared_ptr<Utente> getUtente(const std::string& username);

    std::shared_ptr<ListaDellaSpesa> creaListaPerUtenteCorrente(const std::string& nomeLista);
    void condividiListaUtenteCorrente(const std::string& nomeLista, const std::string& altroUtente);
};

#endif