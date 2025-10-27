#include "CLI.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include "ContatoreOggetti.h"

// --- helper ---
int leggiIntero(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input non valido. Riprova.\n";
        }
    }
}

std::string leggiStringa(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void pausa() {
    std::cout << "\nPremi INVIO per continuare...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// --- CLI ---
void CLI::pulisciSchermo() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

void CLI::avvia() {
    while (true) {
        pulisciSchermo();
        std::cout << "=== LISTA DELLA SPESA ===\n\n";

        auto utente = gestore.getUtenteCorrente();
        if (utente)
            std::cout << "Utente connesso: " << utente->getUsername() << "\n\n";
        else
            std::cout << "Nessun utente connesso.\n\n";

        mostraMenuPrincipale(); // stampa sempre le opzioni
    }
}

void CLI::mostraMenuPrincipale() {
    auto utente = gestore.getUtenteCorrente();

    std::cout << "Opzioni disponibili:\n";
    if (!utente) {
        std::cout << "1. Login\n";
        std::cout << "2. Registra nuovo utente\n";
    } else {
        std::cout << "3. Gestione liste\n";
        std::cout << "4. Logout\n";
    }
    std::cout << "0. Esci\n";

    int scelta = leggiIntero("Inserisci il numero dell'opzione: ");

    if (!utente) {
        switch (scelta) {
            case 1: gestisciLogin(); break;
            case 2: gestisciRegistrazione(); break;
            case 0: std::cout << "Arrivederci!\n"; exit(0);
            default: std::cout << "Scelta non valida!\n"; pausa();
        }
    } else {
        switch (scelta) {
            case 3: gestisciListe(); break;
            case 4: gestore.logout(); std::cout << "Logout effettuato!\n"; pausa(); break;
            case 0: std::cout << "Arrivederci!\n"; exit(0);
            default: std::cout << "Scelta non valida!\n"; pausa();
        }
    }
}

// --- Registrazione/Login ---
void CLI::gestisciRegistrazione() {
    pulisciSchermo();
    std::cout << "=== REGISTRAZIONE ===\n\n";

    std::string username = leggiStringa("Nuovo username: ");
    if (username.empty()) {
        std::cout << "\nUsername non valido!\n";
        pausa();
        return;
    }

    gestore.registraUtente(username);
    std::cout << "\nUtente '" << username << "' registrato con successo!\n\n";

    // Mini-menu dopo registrazione
    while (true) {
        std::cout << "Cosa vuoi fare ora?\n";
        std::cout << "1. Login ora\n";
        std::cout << "2. Torna al menu principale\n";

        int scelta = leggiIntero("Inserisci il numero dell'opzione: ");
        if (scelta == 1) {
            if (gestore.login(username)) {
                pulisciSchermo();
                std::cout << "=== LISTA DELLA SPESA ===\n\n";
                std::cout << "Utente connesso: " << username << "\n\n";
                std::cout << "Login effettuato con successo!\n";
                pausa();

                // Torna al ciclo principale: menu sempre chiaro
                return;
            }
        }
    }
}

void CLI::gestisciLogin() {
    pulisciSchermo();
    std::cout << "=== LOGIN ===\n\n";

    std::string username = leggiStringa("Username: ");
    if (gestore.login(username))
        std::cout << "\nLogin effettuato come " << username << "!\n";
    else
        std::cout << "\nUtente non trovato!\n";

    pausa();
}

// --- Gestione Liste ---
void CLI::gestisciListe() {
    auto utente = gestore.getUtenteCorrente();
    if (!utente) return;

    while (true) {
        pulisciSchermo();
        std::cout << "=== GESTIONE LISTE (" << utente->getUsername() << ") ===\n\n";

        auto personali = utente->getListePersonali();
        auto condivise = utente->getListeCondivise();

        std::cout << "--- LISTE PERSONALI ---\n";
        if (personali.empty())
            std::cout << "Nessuna lista personale\n";
        else
            for (size_t i = 0; i < personali.size(); ++i)
                std::cout << i + 1 << ". " << personali[i]->getNome()
                          << " (" << personali[i]->getOggetti().size() << " oggetti)\n";

        std::cout << "\n--- LISTE CONDIVISE ---\n";
        if (condivise.empty())
            std::cout << "Nessuna lista condivisa\n";
        else
            for (size_t i = 0; i < condivise.size(); ++i)
                std::cout << i + 1 + personali.size() << ". "
                          << condivise[i]->getNome() << " (di "
                          << condivise[i]->getProprietario() << ")\n";

        std::cout << "\nOpzioni:\n";
        std::cout << "1. Crea nuova lista\n";
        std::cout << "2. Seleziona lista\n";
        if (!personali.empty()) std::cout << "3. Condividi lista\n";
        std::cout << "4. Torna indietro\n";

        int scelta = leggiIntero("Inserisci il numero dell'opzione: ");

        if (scelta == 1) {
            std::string nome = leggiStringa("Nome della nuova lista: ");
            gestore.creaListaPerUtenteCorrente(nome);

            // Recupera l'ultima lista appena creata
            auto personaleAggiornato = utente->getListePersonali();
            auto nuovaLista = personaleAggiornato.back();

            std::cout << "\nLista '" << nome << "' creata con successo!\n";
            std::cout << "Ora puoi aggiungere oggetti.\n";
            pausa();

            gestisciOggetti(nuovaLista);

        } else if (scelta == 2) {
            if (personali.empty() && condivise.empty()) {
                std::cout << "\nNessuna lista disponibile!\n";
                pausa();
                continue;
            }

            int idx = leggiIntero("Numero lista da aprire: ");
            std::shared_ptr<ListaDellaSpesa> lista;

            if (idx >= 1 && idx <= (int)personali.size())
                lista = personali[idx - 1];
            else if (idx <= (int)(personali.size() + condivise.size()))
                lista = condivise[idx - 1 - personali.size()];
            else {
                std::cout << "\nIndice non valido.\n";
                pausa();
                continue;
            }

            gestisciOggetti(lista);

        } else if (scelta == 3 && !personali.empty()) {
            std::string nome = leggiStringa("Nome lista da condividere: ");
            std::string altro = leggiStringa("Username destinatario: ");
            gestore.condividiListaUtenteCorrente(nome, altro);
            std::cout << "\nCondivisione completata!\n";
            pausa();

        } else if (scelta == 4) {
            return;

        } else {
            std::cout << "\nScelta non valida!\n";
            pausa();
        }
    }
}

// --- Gestione Oggetti ---
void CLI::gestisciOggetti(std::shared_ptr<ListaDellaSpesa> lista) {
    auto contatore = std::make_shared<ContatoreOggetti>();
    lista->aggiungiObserver(contatore);

    while (true) {
        pulisciSchermo();
        std::cout << "=== LISTA: " << lista->getNome() << " ===\n"
                  << "Proprietario: " << lista->getProprietario() << "\n\n";

        auto oggetti = lista->getOggetti();
        if (oggetti.empty()) {
            std::cout << "La lista è vuota.\n";
        } else {
            std::cout << "--- Oggetti ---\n";
            for (size_t i = 0; i < oggetti.size(); ++i) {
                const auto& o = oggetti[i];
                std::cout << i + 1 << ". " << o.getNome()
                          << " (" << o.getCategoria() << ") x" << o.getQuantita()
                          << (o.isAcquistato() ? " [ACQUISTATO]" : "") << "\n";
            }
        }

        std::cout << "\nTotale oggetti: " << contatore->getNumeroOggetti()
                  << " | Da acquistare: " << lista->getQuantitaDaAcquistare() << "\n";

        auto categorie = lista->contaPerCategoria();
        if (!categorie.empty()) {
            std::cout << "Per categoria: ";
            for (const auto& [cat, q] : categorie)
                std::cout << cat << "(" << q << ") ";
            std::cout << "\n";
        }

        std::cout << "\nOpzioni:\n"
                  << "1. Aggiungi oggetto\n"
                  << "2. Rimuovi oggetto\n"
                  << "3. Filtra per categoria\n"
                  << "4. Torna indietro\n";

        int scelta = leggiIntero("Scelta: ");

        if (scelta == 1) {
            std::string nome = leggiStringa("Nome oggetto: ");
            std::string categoria = leggiStringa("Categoria: ");
            int qta = leggiIntero("Quantità: ");

            lista->aggiungiOggetto(Oggetto(nome, categoria, qta));
            std::cout << "\nOggetto aggiunto!\n";
            pausa();

        } else if (scelta == 2) {
            if (oggetti.empty()) {
                std::cout << "\nLa lista è vuota.\n";
                pausa();
                continue;
            }

            std::string nome = leggiStringa("Nome oggetto da rimuovere: ");
            lista->rimuoviOggetto(nome);
            std::cout << "\nOggetto rimosso!\n";
            pausa();

        } else if (scelta == 3) {
            std::string categoria = leggiStringa("Categoria: ");
            auto filtrati = lista->filtraPerCategoria(categoria);

            std::cout << "\nOggetti in '" << categoria << "':\n";
            if (filtrati.empty()) {
                std::cout << "Nessun oggetto in questa categoria.\n";
            } else {
                for (const auto& o : filtrati)
                    std::cout << "- " << o.getNome() << " x" << o.getQuantita() << "\n";
            }
            pausa();

        } else if (scelta == 4) {
            lista->rimuoviObserver(contatore);
            return;

        } else {
            std::cout << "\nScelta non valida!\n";
            pausa();
        }
    }
}
