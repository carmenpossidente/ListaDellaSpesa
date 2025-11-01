#include "CLI.h"
#include "ContatoreOggetti.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

CLI::CLI() : running(false) {}

void CLI::avvia() {
    running = true;
    mostraBanner();

    while (running) {
        gestisciMenuPrincipale();
    }
}

void CLI::termina() {
    running = false;
    std::cout << "\n Grazie per aver usato Lista della Spesa!\n";
}

// Utility
void CLI::clearScreen() {
    for (int i = 0; i < 10; ++i) std::cout << '\n';
    std::cout.flush();
}

void CLI::pausa() {
    std::cout << "\nPremi INVIO per continuare...";

    // Consuma tutto fino al prossimo newline (compreso)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string CLI::leggiStringa(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int CLI::leggiIntero(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        try {
            int valore = std::stoi(input);
            if (valore >= min && valore <= max)
                return valore;
            std::cout << "Valore deve essere tra " << min << " e " << max << "\n";
        } catch (...) {
            std::cout << "Input non valido. Inserisci un numero.\n";
        }
    }
}

void CLI::mostraBanner() {
    clearScreen();
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════╗\n";
    std::cout << "║                                           ║\n";
    std::cout << "║             LISTA DELLA SPESA             ║\n";
    std::cout << "║                                           ║\n";
    std::cout << "╚═══════════════════════════════════════════╝\n";
    std::cout << "\n";
}

void CLI::stampaOggetto(const Oggetto& obj, int indice) {
    std::cout << "  " << std::setw(2) << indice << ". ";

    // Casella: spuntata se acquistato, vuota altrimenti
    std::string casella = obj.isAcquistato() ? "[✔]" : "[ ]";

    std::cout << casella << " ";


    std::cout << std::left << std::setw(15) << obj.getNome()
              << " | " << std::setw(15) << obj.getCategoria()
              << " | Qta: " << obj.getQuantita()
              << "\n";
}

void CLI::stampaLista(std::shared_ptr<ListaDellaSpesa> lista) {
    if (!lista) {
        std::cout << "Nessuna lista selezionata.\n";
        return;
    }

    const auto& oggetti = lista->getOggetti();

    if (oggetti.empty()) {
        std::cout << "\n La lista è vuota.\n";
        return;
    }

    std::cout << "\n┌─────────────────────────────────────────────────────────┐\n";
    std::cout << "│ Lista: " << std::left << std::setw(47) << lista->getNome() << "  │\n";
    std::cout << "├─────────────────────────────────────────────────────────┤\n";

    for (size_t i = 0; i < oggetti.size(); ++i) {
        stampaOggetto(oggetti[i], i + 1);
    }

    std::cout << "└─────────────────────────────────────────────────────────┘\n";
    int quantitaDaAcquistare = lista->getQuantitaDaAcquistare();
    int tipiOggetti = static_cast<int>(oggetti.size());

    std::cout << "\n Tipi di oggetti: " << tipiOggetti
              << " | Quantità da acquistare: " << quantitaDaAcquistare << "\n";
}

// Menu Principale
void CLI::mostraMenuPrincipale() {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║         MENU PRINCIPALE            ║\n";
    std::cout << "╠════════════════════════════════════╣\n";

    auto utente = gestore.getUtenteCorrente();
    if (utente) {
        std::cout << "║ Utente: " << std::left << std::setw(23)
                  << utente->getUsername() << "   ║\n";
        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║ 1. Gestisci Liste                  ║\n";
        std::cout << "║ 2. Gestisci Utente                 ║\n";
        std::cout << "║ 0. Esci                            ║\n";
    } else {
        std::cout << "║ Nessun utente connesso             ║\n";
        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║ 1. Registrazione                   ║\n";
        std::cout << "║ 2. Login                           ║\n";
        std::cout << "║ 0. Esci                            ║\n";
    }

    std::cout << "╚════════════════════════════════════╝\n";
}

void CLI::gestisciMenuPrincipale() {
    mostraMenuPrincipale();

    int scelta = leggiIntero("Scegli un'opzione: ", 0, 2);

    auto utente = gestore.getUtenteCorrente();

    if (utente) {
        switch (scelta) {
            case 1: menuListe(); break;
            case 2: menuUtente(); break;
            case 0: termina(); break;
        }
    } else {
        switch (scelta) {
            case 1: registrazioneUtente(); break;
            case 2: loginUtente(); break;
            case 0: termina(); break;
        }
    }
}

// Gestione Utente
void CLI::menuUtente() {
    clearScreen();
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║        GESTIONE UTENTE             ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║ 1. Logout                          ║\n";
    std::cout << "║ 0. Indietro                        ║\n";
    std::cout << "╚════════════════════════════════════╝\n";
    int scelta = leggiIntero("Scegli un'opzione: ", 0, 1);

    switch (scelta) {
        case 1: logoutUtente(); break;
        case 0: break;
    }
}

void CLI::registrazioneUtente() {
    clearScreen();
    std::cout << "\n=== REGISTRAZIONE NUOVO UTENTE ===\n\n";

    std::string username = leggiStringa("Username: ");

    if (username.empty()) {
        std::cout << "Username non può essere vuoto.\n";
        pausa();
        return;
    }

    gestore.registraUtente(username);
    std::cout << "\nUtente '" << username << "' registrato con successo!\n";
    std::cout << "Ora puoi effettuare il login.\n";
    pausa();
}

void CLI::loginUtente() {
    clearScreen();
    std::cout << "\n=== LOGIN ===\n\n";

    std::string username = leggiStringa("Username: ");

    if (gestore.login(username)) {
        std::cout << "\nLogin effettuato con successo!\n";
        std::cout << "Benvenuto, " << username << "!\n";
    } else {
        std::cout << "\nUtente non trovato.\n";
        std::cout << "Registrati prima di effettuare il login.\n";
    }
    pausa();
}

void CLI::logoutUtente() {
    auto utente = gestore.getUtenteCorrente();
    if (utente) {
        std::string username = utente->getUsername();
        gestore.logout();
        clearScreen();
        std::cout << "\nLogout effettuato.\n";
        std::cout << "Arrivederci, " << username << "!\n";
        pausa();
    }
}

// Gestione Liste
void CLI::menuListe() {
    while (true) {
        clearScreen();
        auto utente = gestore.getUtenteCorrente();
        if (!utente) {
            std::cout << "Devi effettuare il login prima.\n";
            pausa();
            return;
        }

        std::cout << "\n╔════════════════════════════════════╗\n";
        std::cout << "║        GESTIONE LISTE              ║\n";
        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║ 1. Crea nuova lista                ║\n";
        std::cout << "║ 2. Visualizza liste                ║\n";
        std::cout << "║ 3. Seleziona e modifica lista      ║\n";
        std::cout << "║ 4. Condividi lista                 ║\n";
        std::cout << "║ 5. Elimina lista                   ║\n";
        std::cout << "║ 6. Annulla condivisione            ║\n";
        std::cout << "║ 0. Indietro                        ║\n";
        std::cout << "╚════════════════════════════════════╝\n";

        int scelta = leggiIntero("Scegli un'opzione: ", 0, 6);

        switch (scelta) {
            case 1: creaLista(); break;
            case 2: visualizzaListe(); break;
            case 3: selezionaLista(); break;
            case 4: condividiLista(); break;
            case 5: eliminaLista(); break;
            case 6: annullaCondivisioneLista(); break;
            case 0: return;
        }
    }
}

void CLI::annullaCondivisioneLista() {
    clearScreen();
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    auto liste = utente->getListePersonali();
    if (liste.empty()) {
        std::cout << "\nNon hai liste personali da gestire.\n";
        pausa();
        return;
    }

    std::cout << "\n=== ANNULLA CONDIVISIONE ===\n\n";
    for (size_t i = 0; i < liste.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << liste[i]->getNome() << "\n";
    }
    std::cout << "  0. Annulla\n\n";

    int scelta = leggiIntero("Seleziona lista: ", 0, static_cast<int>(liste.size()));
    if (scelta == 0) return;

    std::string nomeLista = liste[scelta - 1]->getNome();
    std::string altroUtente = leggiStringa("Username con cui era condivisa: ");
    if (altroUtente.empty()) {
        std::cout << "\n[X] Username non valido.\n";
        pausa();
        return;
    }

    std::cout << "\nConfermi di annullare la condivisione di '" << nomeLista
              << "' con " << altroUtente << "? (s/n): ";
    std::string conferma;
    std::getline(std::cin, conferma);
    if (conferma != "s" && conferma != "S") {
        std::cout << "Operazione annullata.\n";
        pausa();
        return;
    }

    gestore.annullaCondivisioneUtenteCorrente(nomeLista, altroUtente);
    pausa();
}

void CLI::creaLista() {
    clearScreen();
    std::cout << "\n=== CREA NUOVA LISTA ===\n\n";

    std::string nomeLista = leggiStringa("Nome della lista: ");

    if (nomeLista.empty()) {
        std::cout << "Il nome non può essere vuoto.\n";
        pausa();
        return;
    }

    auto lista = gestore.creaListaPerUtenteCorrente(nomeLista);

    if (lista) {
        // Aggiungi un contatore come observer
        auto contatore = std::make_shared<ContatoreOggetti>();
        lista->aggiungiObserver(contatore);

        std::cout << "\nLista '" << nomeLista << "' creata con successo!\n";
        std::cout << "Ora puoi aggiungere gli oggetti.\n";

        pausa();
        menuOggetti(lista);
    } else {
        std::cout << "\nErrore nella creazione della lista.\n";
        pausa();
    }
}

void CLI::visualizzaListe() {
    clearScreen();
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    std::cout << "\n=== LE TUE LISTE ===\n\n";

    auto listePersonali = utente->getListePersonali();
    auto listeCondivise = utente->getListeCondivise();

    if (listePersonali.empty() && listeCondivise.empty()) {
        std::cout << "Non hai ancora creato nessuna lista.\n";
        std::cout << "Usa l'opzione 'Crea nuova lista' per iniziare!\n";
        pausa();
        return;
    }

    if (!listePersonali.empty()) {
        std::cout << "Liste Personali:\n";
        std::cout << "────────────────────────────────────────\n";
        for (size_t i = 0; i < listePersonali.size(); ++i) {
            auto lista = listePersonali[i];
            const auto& items = lista->getOggetti();
            int numOggetti = static_cast<int>(items.size());
            int daAcquistare = lista->getQuantitaDaAcquistare();
            int quantitaTotale = 0;
            for (const auto& o : items) quantitaTotale += o.getQuantita();

            std::cout << "  " << (i + 1) << ". " << lista->getNome()
                      << " (" << numOggetti << " tipi, "
                      << quantitaTotale << " totali, "
                      << daAcquistare << " da acquistare)\n";
        }
        std::cout << "\n";
    }

    if (!listeCondivise.empty()) {
        std::cout << "Liste Condivise:\n";
        std::cout << "────────────────────────────────────────\n";
        for (size_t i = 0; i < listeCondivise.size(); ++i) {
            auto lista = listeCondivise[i];
            const auto& items = lista->getOggetti();
            int numOggetti = static_cast<int>(items.size());
            int daAcquistare = lista->getQuantitaDaAcquistare();
            int quantitaTotale = 0;
            for (const auto& o : items) quantitaTotale += o.getQuantita();

            std::cout << "  " << (i + 1) << ". " << lista->getNome()
                      << " (di " << lista->getProprietario() << ") "
                      << "(" << numOggetti << " tipi, "
                      << quantitaTotale << " totali, "
                      << daAcquistare << " da acquistare)\n";
        }
    }

    pausa();
}

void CLI::selezionaLista() {
    clearScreen();
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    std::cout << "\n=== SELEZIONA LISTA ===\n\n";

    auto listePersonali = utente->getListePersonali();
    auto listeCondivise = utente->getListeCondivise();

    if (listePersonali.empty() && listeCondivise.empty()) {
        std::cout << "Non hai liste disponibili.\n";
        pausa();
        return;
    }

    std::cout << "Le tue liste:\n";
    int indice = 1;

    for (size_t i = 0; i < listePersonali.size(); ++i) {
        std::cout << "  " << indice++ << ". " << listePersonali[i]->getNome() << "\n";
    }

    for (size_t i = 0; i < listeCondivise.size(); ++i) {
        std::cout << "  " << indice++ << ". " << listeCondivise[i]->getNome()
                  << " (condivisa)\n";
    }

    std::cout << "  0. Annulla\n\n";

    int scelta = leggiIntero("Seleziona lista: ", 0, indice - 1);

    if (scelta == 0) return;

    std::shared_ptr<ListaDellaSpesa> listaSelezionata;

    if (scelta <= static_cast<int>(listePersonali.size())) {
        listaSelezionata = listePersonali[scelta - 1];
    } else {
        listaSelezionata = listeCondivise[scelta - listePersonali.size() - 1];
    }

    if (listaSelezionata) {
        menuOggetti(listaSelezionata);
    }
}

void CLI::condividiLista() {
    clearScreen();
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    std::cout << "\n=== CONDIVIDI LISTA ===\n\n";

    auto listePersonali = utente->getListePersonali();

    if (listePersonali.empty()) {
        std::cout << "Non hai liste personali da condividere.\n";
        pausa();
        return;
    }

    // Mostra le liste con più dettagli
    std::cout << "Le tue liste:\n";
    std::cout << "----------------------------------------\n";
    for (size_t i = 0; i < listePersonali.size(); ++i) {
        auto lista = listePersonali[i];
        std::cout << "  " << (i + 1) << ". " << lista->getNome()
                  << " (" << lista->getOggetti().size() << " oggetti)\n";
    }
    std::cout << "  0. Annulla\n";

    int scelta = leggiIntero("\nSeleziona lista: ", 0, listePersonali.size());

    if (scelta == 0) {
        std::cout << "Operazione annullata.\n";
        pausa();
        return;
    }

    std::string nomeLista = listePersonali[scelta - 1]->getNome();

    std::cout << "\nCondivisione lista: " << nomeLista << "\n";
    std::cout << "----------------------------------------\n";

    std::string altroUtente = leggiStringa("Username con cui condividere: ");

    // Validazione input
    if (altroUtente.empty()) {
        std::cout << "\n[X] Username non valido.\n";
        pausa();
        return;
    }

    if (altroUtente == utente->getUsername()) {
        std::cout << "\n[X] Non puoi condividere una lista con te stesso!\n";
        pausa();
        return;
    }

    // Verifica che l'utente esista
    auto utenteDestinatario = gestore.getUtente(altroUtente);
    if (!utenteDestinatario) {
        std::cout << "\n[X] Utente '" << altroUtente << "' non trovato.\n";
        std::cout << "Assicurati che l'utente sia registrato nel sistema.\n";
        pausa();
        return;
    }

    // Verifica che la lista non sia già condivisa con questo utente
    auto listeCondiviseDestinatario = utenteDestinatario->getListeCondivise();
    for (const auto& lista : listeCondiviseDestinatario) {
        if (lista->getNome() == nomeLista && lista->getProprietario() == utente->getUsername()) {
            std::cout << "\n[!] La lista '" << nomeLista << "' e' gia' condivisa con "
                      << altroUtente << ".\n";
            pausa();
            return;
        }
    }

    // Conferma finale
    std::cout << "\nConfermi di voler condividere '" << nomeLista
              << "' con " << altroUtente << "? (s/n): ";
    std::string conferma;
    std::getline(std::cin, conferma);

    if (conferma != "s" && conferma != "S") {
        std::cout << "Operazione annullata.\n";
        pausa();
        return;
    }

    // Esegui la condivisione
    try {
        gestore.condividiListaUtenteCorrente(nomeLista, altroUtente);

        std::cout << "\n[OK] Lista condivisa con successo!\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Lista: " << nomeLista << "\n";
        std::cout << "Condivisa con: " << altroUtente << "\n";
        std::cout << "\n[i] " << altroUtente << " ricevera' notifiche per ogni modifica.\n";
        std::cout << "[i] La lista apparira' nelle sue 'Liste Condivise'.\n";

    } catch (const std::exception& e) {
        std::cout << "\n[X] Errore durante la condivisione: " << e.what() << "\n";
    }

    pausa();
}

// Gestione Oggetti
void CLI::menuOggetti(std::shared_ptr<ListaDellaSpesa> lista) {
    if (!lista) return;

    while (true) {
        clearScreen();
        std::cout << "\n╔════════════════════════════════════╗\n";
        std::cout << "║    GESTIONE OGGETTI                ║\n";
        std::cout << "║    Lista: " << std::left << std::setw(24)
                  << lista->getNome() << " ║\n";
        std::cout << "╠════════════════════════════════════╣\n";
        std::cout << "║ 1. Aggiungi oggetto                ║\n";
        std::cout << "║ 2. Visualizza oggetti              ║\n";
        std::cout << "║ 3. Rimuovi oggetto                 ║\n";
        std::cout << "║ 4. Marca come acquistato           ║\n";
        std::cout << "║ 5. Filtra per categoria            ║\n";
        std::cout << "║ 6. Mostra statistiche              ║\n";
        std::cout << "║ 7. Salva su file                   ║\n";
        std::cout << "║ 8. Carica da file                  ║\n";
        std::cout << "║ 0. Indietro                        ║\n";
        std::cout << "╚════════════════════════════════════╝\n";

        int scelta = leggiIntero("Scegli un'opzione: ", 0, 8);

        switch (scelta) {
            case 1: aggiungiOggetto(lista); break;
            case 2: visualizzaOggetti(lista); break;
            case 3: rimuoviOggetto(lista); break;
            case 4: marcaAcquistato(lista); break;
            case 5: filtraPerCategoria(lista); break;
            case 6: mostraStatistiche(lista); break;
            case 7: salvaLista(lista); break;
            case 8: caricaLista(lista); break;
            case 0: return;
        }
    }
}

void CLI::eliminaLista() {
    clearScreen();
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    auto liste = utente->getListePersonali();
    if (liste.empty()) {
        std::cout << "\nNon hai liste personali da eliminare.\n";
        pausa();
        return;
    }

    std::cout << "\n=== ELIMINA LISTA ===\n\n";
    for (size_t i = 0; i < liste.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << liste[i]->getNome() << "\n";
    }
    std::cout << "  0. Annulla\n\n";

    int scelta = leggiIntero("Seleziona lista da eliminare: ", 0, static_cast<int>(liste.size()));
    if (scelta == 0) return;

    std::string nomeLista = liste[scelta - 1]->getNome();
    std::cout << "\nConfermi l'eliminazione di '" << nomeLista << "'? (s/n): ";
    std::string conferma;
    std::getline(std::cin, conferma);
    if (conferma != "s" && conferma != "S") {
        std::cout << "Operazione annullata.\n";
        pausa();
        return;
    }

    utente->eliminaLista(nomeLista);
    pausa();
}

void CLI::aggiungiOggetto(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== AGGIUNGI OGGETTO ===\n\n";

    std::string nome = leggiStringa("Nome oggetto: ");
    if (nome.empty()) {
        std::cout << "Il nome non può essere vuoto.\n";
        pausa();
        return;
    }

    std::string categoria = leggiStringa("Categoria (es. Frutta, Verdura, Igiene...): ");
    if (categoria.empty()) {
        categoria = "Generale";
    }

    int quantita = leggiIntero("Quantità: ", 1, 999);

    try {
        Oggetto nuovoOggetto(nome, categoria, quantita);
        lista->aggiungiOggetto(nuovoOggetto);
        std::cout << "\nOggetto aggiunto con successo!\n";

        // Mostra se è stato incrementato o aggiunto
        for (const auto& obj : lista->getOggetti()) {
            if (obj.getNome() == nome && obj.getCategoria() == categoria) {
                if (obj.getQuantita() > quantita) {
                    std::cout << "Quantità incrementata (già esistente nella lista)\n";
                }
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Errore: " << e.what() << "\n";
    }

    pausa();
}

void CLI::visualizzaOggetti(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== OGGETTI NELLA LISTA ===\n";
    stampaLista(lista);

    pausa();
}

void CLI::rimuoviOggetto(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== RIMUOVI OGGETTO ===\n";

    const auto& oggetti = lista->getOggetti();

    if (oggetti.empty()) {
        std::cout << "\nLa lista è vuota.\n";
        pausa();
        return;
    }

    stampaLista(lista);

    std::cout << "\n";
    int scelta = leggiIntero("Seleziona oggetto da rimuovere (0 per annullare): ",
                             0, static_cast<int>(oggetti.size()));

    if (scelta == 0) return;

    std::string nomeOggetto = oggetti[scelta - 1].getNome();

    std::cout << "\nSei sicuro di voler rimuovere '" << nomeOggetto << "'? (s/n): ";
    std::string conferma;
    std::getline(std::cin, conferma);

    if (conferma == "s" || conferma == "S") {
        lista->rimuoviOggetto(nomeOggetto);
        std::cout << "Oggetto rimosso!\n";
    } else {
        std::cout << "Operazione annullata.\n";
    }

    pausa();
}

void CLI::marcaAcquistato(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== MARCA COME ACQUISTATO ===\n";

    auto oggetti = lista->getOggetti();

    if (oggetti.empty()) {
        std::cout << "\nLa lista è vuota.\n";
        pausa();
        return;
    }

    // Mostra solo oggetti non acquistati
    std::vector<int> indiciNonAcquistati;
    std::cout << "\nOggetti da acquistare:\n";
    std::cout << "────────────────────────────────────────\n";

    int contatore = 1;
    for (size_t i = 0; i < oggetti.size(); ++i) {
        if (!oggetti[i].isAcquistato()) {
            std::cout << "  " << contatore << ". " << oggetti[i].getNome()
                      << " (Qta: " << oggetti[i].getQuantita() << ")\n";
            indiciNonAcquistati.push_back(i);
            contatore++;
        }
    }

    if (indiciNonAcquistati.empty()) {
        std::cout << "\nHai già acquistato tutto!\n";
        pausa();
        return;
    }

    std::cout << "\n";
    int scelta = leggiIntero("Seleziona oggetto (0 per annullare): ",
                             0, static_cast<int>(indiciNonAcquistati.size()));

    if (scelta == 0) return;

    // Usa il metodo marcaAcquistato di ListaDellaSpesa
    int indiceOriginale = indiciNonAcquistati[scelta - 1];
    std::string nomeOggetto = oggetti[indiceOriginale].getNome();

    lista->marcaAcquistato(nomeOggetto, true);  // Notifica l'Observer

    std::cout << "\nOggetto marcato come acquistato!\n";
    pausa();
}

void CLI::filtraPerCategoria(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== FILTRA PER CATEGORIA ===\n\n";

    // Mostra tutte le categorie disponibili
    auto conteggio = lista->contaPerCategoria();

    if (conteggio.empty()) {
        std::cout << "Nessun oggetto nella lista.\n";
        pausa();
        return;
    }

    std::cout << "Categorie disponibili:\n";
    std::cout << "────────────────────────────────────────\n";

    std::vector<std::string> categorie;
    int indice = 1;
    for (const auto& [cat, count] : conteggio) {
        std::cout << "  " << indice++ << ". " << cat
                  << " (" << count << " oggetti)\n";
        categorie.push_back(cat);
    }

    std::cout << "\n";
    int scelta = leggiIntero("Seleziona categoria (0 per annullare): ",
                             0, static_cast<int>(categorie.size()));

    if (scelta == 0) return;

    std::string categoriaSelezionata = categorie[scelta - 1];
    auto oggettiFiltrati = lista->filtraPerCategoria(categoriaSelezionata);

    std::cout << "\nCategoria: " << categoriaSelezionata << "\n";
    std::cout << "────────────────────────────────────────\n";

    for (size_t i = 0; i < oggettiFiltrati.size(); ++i) {
        stampaOggetto(oggettiFiltrati[i], i + 1);
    }

    pausa();
}

void CLI::mostraStatistiche(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== STATISTICHE LISTA ===\n\n";
    std::cout << "Lista: " << lista->getNome() << "\n";
    std::cout << "══════════════════════════════════════\n\n";

    const auto& oggetti = lista->getOggetti();

    if (oggetti.empty()) {
        std::cout << "La lista è vuota.\n";
        pausa();
        return;
    }

    std::cout << "STATISTICHE GENERALI:\n";
    std::cout << "────────────────────────────────────────\n";

    // Statistiche generali
    int totaleOggetti = 0;
    int oggettiAcquistati = 0;
    int quantitaTotale = 0;
    int quantitaDaAcquistare = lista->getQuantitaDaAcquistare();

    for (const auto& obj : oggetti) {
        totaleOggetti++;
        quantitaTotale += obj.getQuantita();
        if (obj.isAcquistato()) {
            oggettiAcquistati++;
        }
    }

    std::cout << "Totale tipi di oggetti: " << totaleOggetti << "\n";
    std::cout << "Quantità totale: " << quantitaTotale << "\n";
    std::cout << "Oggetti acquistati: " << oggettiAcquistati << "\n";
    std::cout << "🛒 Oggetti DA ACQUISTARE: " << (totaleOggetti - oggettiAcquistati) << "\n";
    std::cout << "Quantità da acquistare: " << quantitaDaAcquistare << "\n\n";

    // Lista oggetti da acquistare
    std::cout << "OGGETTI DA ACQUISTARE:\n";
    std::cout << "────────────────────────────────────────\n";
    bool haOggettiDaAcquistare = false;
    for (const auto& obj : oggetti) {
        if (!obj.isAcquistato()) {
            std::cout << "  • " << obj.getNome()
                      << " (" << obj.getCategoria() << ") - Qta: "
                      << obj.getQuantita() << "\n";
            haOggettiDaAcquistare = true;
        }
    }

    if (!haOggettiDaAcquistare) {
        std::cout << "  ✓ Hai acquistato tutto!\n";
    }
    std::cout << "\n";

    // Percentuale completamento
    float percentuale = totaleOggetti > 0
                        ? (static_cast<float>(oggettiAcquistati) / totaleOggetti) * 100
                        : 0;

    std::cout << "Progresso: " << std::fixed << std::setprecision(1)
              << percentuale << "%\n";

    // Barra di progresso
    int barraPiena = static_cast<int>(percentuale / 5);
    std::cout << "[";
    for (int i = 0; i < 20; ++i) {
        if (i < barraPiena) std::cout << "█";
        else std::cout << "░";
    }
    std::cout << "]\n\n";

    // Statistiche per categoria
    auto conteggio = lista->contaPerCategoria();

    std::cout << "Per Categoria:\n";
    std::cout << "────────────────────────────────────────\n";

    for (const auto& [cat, count] : conteggio) {
        std::cout << "  • " << std::left << std::setw(20) << cat
                  << ": " << count << " oggetti\n";
    }

    pausa();
}
// Gestione File
void CLI::salvaLista(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== SALVA LISTA SU FILE ===\n\n";

    std::string filename = leggiStringa("Nome file (senza estensione, premere INVIO per default): ");

    if (filename.empty()) {
        filename = lista->getNome();
    }

    // Aggiungi estensione .json se non presente
    if (filename.find(".json") == std::string::npos) {
        filename += ".json";
    }

    try {
        lista->salvaSuFile(filename);
        lista->setFilename(filename);
        std::cout << "\nLista salvata in '" << filename << "'\n";
        std::cout << "La lista verrà ora salvata automaticamente ad ogni modifica.\n";
    } catch (const std::exception& e) {
        std::cout << "Errore nel salvataggio: " << e.what() << "\n";
    }

    pausa();
}

void CLI::caricaLista(std::shared_ptr<ListaDellaSpesa> lista) {
    clearScreen();
    std::cout << "\n=== CARICA LISTA DA FILE ===\n\n";

    std::string filename = leggiStringa("Nome file: ");

    if (filename.empty()) {
        std::cout << "Nome file non valido.\n";
        pausa();
        return;
    }

    // Aggiungi estensione .json se non presente
    if (filename.find(".json") == std::string::npos) {
        filename += ".json";
    }

    std::cout << "\nAttenzione: il contenuto attuale della lista verrà sostituito.\n";
    std::cout << "Continuare? (s/n): ";

    std::string conferma;
    std::getline(std::cin, conferma);

    if (conferma != "s" && conferma != "S") {
        std::cout << "Operazione annullata.\n";
        pausa();
        return;
    }

    try {
        lista->caricaDaFile(filename);
        lista->setFilename(filename);
        std::cout << "\nLista caricata con successo da '" << filename << "'!\n";
        std::cout << "Oggetti caricati: " << lista->getOggetti().size() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Errore nel caricamento: " << e.what() << "\n";
        std::cout << "Verifica che il file esista e sia valido.\n";
    }

    pausa();
}