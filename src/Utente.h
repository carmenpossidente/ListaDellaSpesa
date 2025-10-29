#ifndef LISTA_SPESA_UTENTE_H
#define LISTA_SPESA_UTENTE_H

#include <string>
#include <vector>
#include <memory>
#include "ListaDellaSpesa.h"
#include "Observer.h"

class Utente : public Observer {
private:
    std::string username;
    std::vector<std::shared_ptr<ListaDellaSpesa>> listePersonali;
    std::vector<std::shared_ptr<ListaDellaSpesa>> listeCondivise;

public:
    Utente(const std::string& username);

    // Observer implementation
    void aggiorna(const std::string& messaggio) override;

    // Gestione liste
    std::shared_ptr<ListaDellaSpesa> creaLista(const std::string& nomeLista);
    void condividiLista(const std::string& nomeLista, std::shared_ptr<Utente> altroUtente);
    void aggiungiListaCondivisa(std::shared_ptr<ListaDellaSpesa> lista);

    // Getter
    std::string getUsername() const;
    std::vector<std::shared_ptr<ListaDellaSpesa>> getListePersonali() const;
    std::vector<std::shared_ptr<ListaDellaSpesa>> getListeCondivise() const;

    // Cerca lista per nome
    std::shared_ptr<ListaDellaSpesa> getListaPerNome(const std::string& nome);
};

#endif