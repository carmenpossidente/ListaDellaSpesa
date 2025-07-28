//
// Created by Carmen on 24/07/2025.
//
#include "Oggetto.h"

Oggetto::Oggetto(const std::string& nome, const std::string& categoria, int quantita)
        : nome(nome), categoria(categoria), quantita(quantita) {}

std::string Oggetto::getNome() const {
    return nome;
}

std::string Oggetto::getCategoria() const {
    return categoria;
}

int Oggetto::getQuantita() const {
    return quantita;
}

void Oggetto::setQuantita(int nuovaQuantita) {
    quantita = nuovaQuantita;
}


bool Oggetto::isAcquistato() const {
    return acquistato;
}

void Oggetto::setAcquistato(bool valore) {
    acquistato = valore;
}

bool Oggetto::operator==(const Oggetto& other) const {
    return nome == other.nome &&
           categoria == other.categoria &&
           quantita == other.quantita &&
           acquistato == other.acquistato;
}
