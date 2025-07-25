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

public:
    Oggetto(const std::string& nome, const std::string& categoria, int quantita);

    std::string getNome() const;
    std::string getCategoria() const;
    int getQuantita() const;

    void setQuantita(int nuovaQuantita);

    bool operator==(const Oggetto& altro) const;
};

#endif // OGGETTO_H

