# 🛒 Lista della Spesa

Applicazione C++ per la gestione di liste della spesa, con supporto a più liste per utente e notifiche basate su Observer in-process.

## Caratteristiche Principali

- **Modello Utente e Liste multiple**: Strutture per gestire più liste per utente
- **Notifiche (Observer in-process)**: Le liste notificano gli observer interni ad ogni modifica
- **Persistenza Dati**: Salvataggio e caricamento automatico in formato JSON
- **Statistiche Lista**: Visualizza progress, categorie e metriche dettagliate
- **Tracking Acquisti**: Marca gli oggetti come acquistati
- **Categorie**: Organizza gli oggetti per categoria personalizzata
- **CLI Intuitiva**: Interfaccia a riga di comando user-friendly



### Design Patterns Implementati

#### Observer Pattern
```cpp
// Le liste notificano gli observer registrati (in-process) ad ogni modifica
lista->aggiungiOggetto(oggetto);
// Esempio di messaggi: "Oggetto aggiunto: Latte", "Oggetto rimosso: Latte"
```

#### Smart Pointers
```cpp
std::shared_ptr<ListaDellaSpesa> lista;
std::shared_ptr<Utente> utente;
// Gestione automatica della memoria, nessun memory leak
```

### Build ed Esecuzione

- Requisiti: CMake, un compilatore C++17+, GoogleTest (fornito in `external/`)
- Build (es. da CLion):
  1. Configura con CMake
  2. Compila target `lista_spesa_lib` e gli eseguibili
  3. Esegui: `lista_spesa_console`

### Test

- I test sono basati su GoogleTest
- Copertura test: classi `Observer`,`ContatoreOggetti`, `Oggetto`, `ListaDellaSpesa`, `Utente`, `GestoreListe`

### Struttura del Progetto

ListaDellaSpesa/
├── 📁 src/
│   ├── 📄 main.cpp                  # Main 
│   ├── 📄 CMakeLists.txt            # Build src
│   │
│   ├── 📄 ListaDellaSpesa.cpp/h     # Classe lista principale
│   ├── 📄 Oggetto.cpp/h             # Classe articolo
│   ├── 📄 Utente.cpp/h              # Classe utente
│   ├── 📄 GestoreListe.cpp/h        # Gestore multiple liste
│   ├── 📄 ContatoreOggetti.cpp/h    # Contatore articoli
│   ├── 📄 CLI.cpp/h                 # CLI
│   └── 📄 Observer.h                # Pattern Observer
│
├── 📁 test/
│   ├── 📄 CMakeLists.txt            # Build test
│   ├── 📄 test_oggetto.cpp          
│   ├── 📄 test_listadellaspesa.cpp  
│   ├── 📄 test_utente.cpp           
│   ├── 📄 test_gestore.cpp         
│   ├── 📄 test_observer.cpp         
│   └── 📄 test_contatore.cpp        
│
├── 📁 data/                         # Dati applicazione
├── 📁 external/                     # Dipendenze esterne
├── 📁 cmake-build-debug/  
├── 📄 README.md
└── 📄 CMakeLists.txt


## Descrizione delle Classi
### Observer
    - Interfaccia con un solo metodo 
    aggiorna(std::string messaggio)
    - Implementata da 
    ContatoreOggetti

### Observable
- Interfaccia con metodi per gestione observer:
    aggiungiObserver(std::shared_ptr)
    rimuoviObserver(std::shared_ptr)
    notificaObservers(const std::string& messaggio)
    (in ListaDellaSpesa è privata)
- Implementata da ListaDellaSpesa

### ListaDellaSpesa (Observable)
- Attributi principali:
    std::vector<Oggetto> oggetti
    std::vector<std::shared_ptr<Observer>> observers
    std::string nomeLista, proprietario, defaultFilename

- Metodi chiave:
    aggiungiOggetto, 
    rimuoviOggetto, 
    marcaAcquistato(nome, bool),
    getOggetti() const, 
    filtraPerCategoria(cat) const,
    contaPerCategoria() const,
    salvaSuFile(filename) const,
    caricaDaFile(filename),
    getQuantitaDaAcquistare() const

- Gestione observer: 
    aggiungiObserver, 
    rimuoviObserver, 
    notificaObservers(...)
    
- Responsabilità:
    Gestisce lo stato degli oggetti.
    Emette notifiche testuali agli observer nelle operazioni (es. “Oggetto aggiunto: X”, “Oggetto marcato_acquistato: X”, ...).

### Oggetto
- Attributi: nome, categoria, quantita, acquistato (bool).
- Metodi getter/setter relativi.
- Entità foglia, utilizzata da ListaDellaSpesa

### ContatoreOggetti (Observer)
- Attributi:
    int numeroDaAcquistare
    std::map<std::string, bool> oggettiDaAcquistare

- Metodi:
    aggiorna(messaggio)
    → parser generico dei messaggi “Oggetto : ”
    getNumeroDaAcquistare() const
    getListaOggettiDaAcquistare() const
    getOggettiConStato() const
    isDaAcquistare(nome) const

- Logica:
    Aggiunta: inserisce nome come non acquistato e incrementa il contatore.
    Rimozione: rimuove e, se non acquistato, decrementa.
    Marcato acquistato/non: aggiorna stato e contatore di conseguenza.
    Caricamento file: resetta stato interno, poi si riallinea con notifiche successive.

### Utente
- Modello di utente (nome/ID ecc.); può essere proprietario di una lista.
- Relazione concettuale: 1 Utente → N ListaDellaSpesa

### GestoreListe
- Gestisce un insieme di ListaDellaSpesa (creazione/recupero, eventualmente per utente).
- Relazione: 1 Gestore → N ListaDellaSpesa.

### Relazioni e molteplicità
- ListaDellaSpesa “contiene” N Oggetto (composizione: la lista possiede la vita degli oggetti).
- ListaDellaSpesa “osservabile da” N Observer (associazione 1→N; uno a molti).
- ContatoreOggetti “osserva” 1..N ListaDellaSpesa (può essere aggiunto a più liste, anche se di solito 1:1).
- GestoreListe “gestisce” N ListaDellaSpesa
- Utente “ha” N ListaDellaSpesa (proprietario), e liste possono essere condivise tra più utenti a livello concettuale.

### Flusso delle notifiche
Quando ListaDellaSpesa cambia:
- Aggiungi: “Oggetto aggiunto: Nome”
- Aggiorna quantità: “Oggetto aggiornato: Nome (nuova quantità: X)”
- Rimuovi: “Oggetto rimosso: Nome”
- Marca acquistato/non: “Oggetto marcato_acquistato: Nome” / “Oggetto marcato_non_acquistato: Nome”
- Carica da file: “Lista caricata da file” (reset degli observer)

ContatoreOggetti.aggiorna interpreta il messaggio e adegua il proprio stato

### Riassunto
Pattern principale: Observer in-process tra ListaDellaSpesa (Observable) e ContatoreOggetti (Observer)

Modello dominio: Oggetti nella lista con stato di acquisto e quantità, statistiche per categoria e totale “da acquistare”

Gestione multi-lista: GestoreListe e proprietà/attributi su
ListaDellaSpesa consentono scenari multi-utente/multi-lista
