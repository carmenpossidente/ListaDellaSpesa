#ifndef CLI_H
#define CLI_H

#include "GestoreListe.h"
#include <string>
#include <memory>

class CLI {
private:
    GestoreListe gestore;
    bool running;

    // Metodi per il menu principale
    void mostraMenuPrincipale();
    void gestisciMenuPrincipale();

    // Metodi per gestione utenti
    void menuUtente();
    void registrazioneUtente();
    void loginUtente();
    void logoutUtente();

    // Metodi per gestione liste
    void menuListe();
    void creaLista();
    void visualizzaListe();
    void selezionaLista();
    void eliminaLista();
    void condividiLista();
    void annullaCondivisioneLista();

    // Metodi per gestione oggetti
    void menuOggetti(std::shared_ptr<ListaDellaSpesa> lista);
    void aggiungiOggetto(std::shared_ptr<ListaDellaSpesa> lista);
    void rimuoviOggetto(std::shared_ptr<ListaDellaSpesa> lista);
    void visualizzaOggetti(std::shared_ptr<ListaDellaSpesa> lista);
    void marcaAcquistato(std::shared_ptr<ListaDellaSpesa> lista);
    void filtraPerCategoria(std::shared_ptr<ListaDellaSpesa> lista);
    void mostraStatistiche(std::shared_ptr<ListaDellaSpesa> lista);

    // Metodi per gestione file
    void salvaLista(std::shared_ptr<ListaDellaSpesa> lista);

    // Utility
    void clearScreen();
    void pausa();
    std::string leggiStringa(const std::string& prompt);
    int leggiIntero(const std::string& prompt, int min = 0, int max = 100);
    void mostraBanner();
    void stampaLista(std::shared_ptr<ListaDellaSpesa> lista);
    void stampaOggetto(const Oggetto& obj, int indice);

public:
    CLI();
    void avvia();
    void termina();
};

#endif // CLI_H