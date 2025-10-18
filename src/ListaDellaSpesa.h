#ifndef LISTA_DELLA_SPESA_H
#define LISTA_DELLA_SPESA_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "Oggetto.h"
#include "Observer.h"

class ListaDellaSpesa : public Observable {
private:
    std::vector<Oggetto> oggetti;
    std::vector<Observer*> observers;
    std::string defaultFilename;
    std::string nomeLista;
    std::string proprietario;

    void notificaObservers(const std::string& messaggio);

public:
    ListaDellaSpesa(const std::string& nome = "", const std::string& proprietario = "");

    void setNome(const std::string& nome);
    std::string getNome() const;
    void setProprietario(const std::string& prop);
    std::string getProprietario() const;

    void aggiungiOggetto(const Oggetto& o);
    void rimuoviOggetto(const std::string& nome);
    void setFilename(const std::string& filename);
    const std::vector<Oggetto>& getOggetti() const;
    void salvaSuFile(const std::string& filename) const;
    void caricaDaFile(const std::string& filename);
    std::vector<Oggetto> filtraPerCategoria(const std::string& categoria) const;
    std::map<std::string, int> contaPerCategoria() const;
    int getQuantitaDaAcquistare() const;

    // Observable implementation
    void aggiungiObserver(Observer* obs) override;
    void rimuoviObserver(Observer* obs) override;
};

#endif
