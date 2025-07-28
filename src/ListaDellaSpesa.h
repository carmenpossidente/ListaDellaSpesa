#ifndef LISTA_DELLA_SPESA_H
#define LISTA_DELLA_SPESA_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "Oggetto.h"
#include "Observer.h"
#include "ContatoreOggetti.h"

class ListaDellaSpesa {
private:
    std::vector<Oggetto> oggetti;
    std::vector<std::shared_ptr<ContatoreOggetti>> observers;
    std::string defaultFilename;

    void notificaObservers() const;

public:
    void aggiungiOggetto(const Oggetto& o);
    void rimuoviOggetto(const std::string& nome);
    void setFilename(const std::string& filename);
    const std::vector<Oggetto>& getOggetti() const;
    void salvaSuFile(const std::string& filename) const;
    void caricaDaFile(const std::string& filename);
    std::vector<Oggetto> filtraPerCategoria(const std::string& categoria) const;
    std::map<std::string, int> contaPerCategoria() const;
    int getQuantitaDaAcquistare() const;

    void aggiungiObserver(std::shared_ptr<ContatoreOggetti> obs);
    void rimuoviObserver(std::shared_ptr<ContatoreOggetti> obs);
};

#endif

