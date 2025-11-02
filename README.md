# 🛒 Lista della Spesa

Applicazione C++ per la gestione di liste della spesa, con supporto a più liste per utente e notifiche basate su Observer in-process.

## Caratteristiche Principali

- **Modello Utente e Liste multiple**: Un utente può avere più liste e più utenti possono condividere le stesse liste
- **Notifiche (Observer in-process)**: Le liste notificano gli observer interni ad ogni modifica
- **Persistenza Dati**: Salvataggio liste in JSON (Utenti e condivisioni esistono invece solo in memoria durante la sessione)
- **Statistiche Lista**: Visualizza progress, categorie e metriche dettagliate
- **Tracking Acquisti**: Marca gli oggetti come acquistati
- **CLI Intuitiva**: Interfaccia a riga di comando user-friendly

### Build ed Esecuzione
- Requisiti: CMake3.20+, un compilatore C++17+, GoogleTest (incluso in `external/`)
- Dopo aver configurato e generato la build con CMake, compilare il progetto ed eseguire l’applicazione principale `lista_spesa_console`

## Design Patterns Implementati:
### Observer Pattern
- **Observable**: `ListaDellaSpesa` (notifica cambiamenti)
- **Observer**: `ContatoreOggetti`, `Utente` (riceve notifiche)

### Movel View Controller
- **Model**: `ListaDellaSpesa`, `Oggetto`, `Utente` (logica business)
- **View**: `CLI` (interfaccia utente)
- **Controller**: `GestoreListe` (orchestrazione multi-utente)

### Smart Pointers (RAII)
Uso sistematico di std::shared_ptr per gestione automatica della memoria
- Prevenzione di memory leak e dangling pointer
- Condivisione sicura di risorse tra componenti


### Struttura del Progetto

```
ListaDellaSpesa/
├── 📁 src/                         # Codice sorgente
│   ├── main.cpp                    # Entry point
│   ├── Observer.h                  # Interfacce Observer/Observable
│   ├── ListaDellaSpesa.h/cpp       # Classe principale (Observable)
│   ├── ContatoreOggetti.h/cpp      # Observer per statistiche
│   ├── Utente.h/cpp                # Gestione utenti (Observer)
│   ├── Oggetto.h/cpp               # Entity oggetto spesa
│   ├── GestoreListe.h/cpp          # Orchestrator multi-utente
│   └── CLI.h/cpp                   # Interfaccia utente
│
├── 📁 test/                        # Unit tests (GoogleTest)
│   ├── test_observer.cpp           # Test pattern Observer
│   ├── test_listadellaspesa.cpp
│   ├── test_contatore.cpp
│   ├── test_utente.cpp
│   ├── test_gestore.cpp
│   └── test_oggetto.cpp
│
├── 📁 external/                 # Dipendenze (git submodule)
│   ├── googletest/              # Framework testing
│   └── nlohmann/                # JSON library
│
├── CMakeLists.txt               # Build configuration
└── README.md
```

### Test
- I test sono basati su GoogleTest
- Copertura test: classi `Observer`, `ContatoreOggetti`, `Oggetto`, `ListaDellaSpesa`, `Utente`, `GestoreListe`


### **Classi Principali**

| Classe | Ruolo | Responsabilità |
|--------|-------|----------------|
| **`ListaDellaSpesa`** | Observable | Gestisce oggetti, notifica cambiamenti |
| **`Oggetto`** | Entity | Rappresenta un articolo (nome, categoria, quantità) |
| **`ContatoreOggetti`** | Observer | Traccia statistiche e oggetti da acquistare |
| **`Utente`** | Observer + Manager | Crea/condivide liste, riceve notifiche |
| **`GestoreListe`** | Controller | Gestisce utenti e liste multiple |
| **`CLI`** | View | Interfaccia utente e navigazione |


### Flusso Notifiche
- Aggiunta oggetto → "Oggetto aggiunto: X" → Contatore incrementa 
- Rimozione oggetto → "Oggetto rimosso: X" → Contatore decrementa
- Acquisto → "Oggetto marcato_acquistato: X" → Contatore aggiorna
- Condivisione → Nuovo observer riceve tutte le notifiche future

### Funzionalità CLI

```
Menu Principale → Gestione Liste → Gestione Oggetti
    ↓               ↓                  ↓
Login/Logout   Crea/Seleziona    Aggiungi/Rimuovi
Registrazione  Condividi/Elimina Marca acquistato
               Salva             Statistiche/Filtri
```
