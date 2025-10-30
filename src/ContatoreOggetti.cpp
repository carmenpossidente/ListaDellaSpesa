#include "ContatoreOggetti.h"
#include <iostream>
#include <cctype>

ContatoreOggetti::ContatoreOggetti() : numeroDaAcquistare(0) {}

void ContatoreOggetti::aggiorna(const std::string& messaggio) {
    std::cout << "[Observer] Ricevuto: " << messaggio << std::endl;

    // Caso: reset dopo caricamento da file
    if (messaggio.find("caricata da file") != std::string::npos) {
        std::cout << "[Observer] Lista caricata da file - reset del contatore" << std::endl;
        oggettiDaAcquistare.clear();
        numeroDaAcquistare = 0;
        return;
    }

    // Parsing generico dei messaggi che iniziano con "Oggetto "
    if (messaggio.rfind("Oggetto ", 0) == 0) {
        // Trova separatore ": "
        const auto sepPos = messaggio.find(": ");
        if (sepPos == std::string::npos) return;

        // Azione tra "Oggetto " e ":"
        const std::string azione = messaggio.substr(8, sepPos - 8);

        // Nome dopo ": ", con trim semplice
        std::string nome = messaggio.substr(sepPos + 2);
        while (!nome.empty() && std::isspace(static_cast<unsigned char>(nome.front()))) nome.erase(nome.begin());
        while (!nome.empty() && std::isspace(static_cast<unsigned char>(nome.back()))) nome.pop_back();

        // Caso speciale: "aggiornato" porta suffisso " (nuova quantità: X)"
        if (azione == "aggiornato") {
            const auto parenPos = nome.find(" (");
            if (parenPos != std::string::npos) nome = nome.substr(0, parenPos);
        }

        if (azione == "aggiunto") {
            if (oggettiDaAcquistare.find(nome) == oggettiDaAcquistare.end()) {
                oggettiDaAcquistare[nome] = false;
                numeroDaAcquistare++;
                std::cout << "[Observer] Aggiunto '" << nome << "' come da acquistare. Totale: "
                          << numeroDaAcquistare << std::endl;
            }
        } else if (azione == "aggiornato") {
            std::cout << "[Observer] Quantita' aggiornata per '" << nome << "'" << std::endl;
        } else if (azione == "rimosso") {
            auto it = oggettiDaAcquistare.find(nome);
            if (it != oggettiDaAcquistare.end()) {
                if (!it->second) numeroDaAcquistare--;
                oggettiDaAcquistare.erase(it);
                std::cout << "[Observer] Rimosso '" << nome << "'. Totale da acquistare: "
                          << numeroDaAcquistare << std::endl;
            }
        } else if (azione == "marcato_acquistato") {
            auto it = oggettiDaAcquistare.find(nome);
            if (it != oggettiDaAcquistare.end() && !it->second) {
                it->second = true;
                numeroDaAcquistare--;
                std::cout << "[Observer] '" << nome << "' marcato come acquistato. Restano da acquistare: "
                          << numeroDaAcquistare << std::endl;
            }
        } else if (azione == "marcato_non_acquistato") {
            auto it = oggettiDaAcquistare.find(nome);
            if (it != oggettiDaAcquistare.end() && it->second) {
                it->second = false;
                numeroDaAcquistare++;
                std::cout << "[Observer] '" << nome << "' rimesso tra gli oggetti da acquistare. Totale: "
                          << numeroDaAcquistare << std::endl;
            }
        }
    }
}

int ContatoreOggetti::getNumeroDaAcquistare() const {
    return numeroDaAcquistare;
}

std::vector<std::string> ContatoreOggetti::getListaOggettiDaAcquistare() const {
    std::vector<std::string> lista;
    for (const auto& [nome, acquistato] : oggettiDaAcquistare) {
        if (!acquistato) {
            lista.push_back(nome);
        }
    }
    return lista;
}

std::map<std::string, bool> ContatoreOggetti::getOggettiConStato() const {
    return oggettiDaAcquistare;
}

bool ContatoreOggetti::isDaAcquistare(const std::string& nome) const {
    auto it = oggettiDaAcquistare.find(nome);
    return it != oggettiDaAcquistare.end() && !it->second;
}