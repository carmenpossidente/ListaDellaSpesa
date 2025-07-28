//
// Created by Carmen on 24/07/2025.
//

#ifndef OGGETTO_H
#define OGGETTO_H

#include <string>

class Oggetto {
private:
    std::string nome;
    std::string categoria;
    int quantita;
    bool acquistato = false;

public:
    Oggetto(const std::string& nome, const std::string& categoria, int quantita);

    std::string getNome() const;
    std::string getCategoria() const;
    int getQuantita() const;
    bool isAcquistato() const;           // getter
    void setAcquistato(bool valore);     // setter

    void setQuantita(int nuovaQuantita);

    bool operator==(const Oggetto& altro) const;
};

#endif // OGGETTO_H

