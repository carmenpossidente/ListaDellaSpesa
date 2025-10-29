# 🛒 Lista della Spesa

Un'applicazione C++ per la gestione collaborativa di liste della spesa, con supporto multi-utente e notifiche real-time.

## Caratteristiche Principali

- **Sistema Multi-Utente**: Registrazione, login e gestione profili
- **Condivisione Liste**: Condividi le tue liste con altri utenti
- **Notifiche Real-Time**: Sistema di notifiche basato su Observer Pattern
- **Persistenza Dati**: Salvataggio e caricamento automatico in formato JSON
- **Statistiche Lista**: Visualizza progress, categorie e metriche dettagliate
- **Tracking Acquisti**: Marca gli oggetti come acquistati
- **Categorie**: Organizza gli oggetti per categoria personalizzata
- **CLI Intuitiva**: Interfaccia a riga di comando user-friendly



### Design Patterns Implementati

#### Observer Pattern
```cpp
// Le liste notificano gli utenti condivisi ad ogni modifica
lista->aggiungiOggetto(oggetto);
// Output: [utente_b] Notifica: Oggetto aggiunto: latte
```

#### Smart Pointers
```cpp
std::shared_ptr<ListaDellaSpesa> lista;
std::shared_ptr<Utente> utente;
// Gestione automatica della memoria, nessun memory leak
```

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
│   └── 📄 test_contatore.cpp        
│
├── 📁 data/                         # Dati applicazione
├── 📁 external/                     # Dipendenze esterne
├── 📁 cmake-build-debug/            
└── 📄 CMakeLists.txt                


## Diagramma delle Classi

<img width="1369" height="1600" alt="UMLListaDellaSpesa" src="https://github.com/user-attachments/assets/c8f968ed-d9bd-40dc-943b-1c5a67402b00" />




             └──────────────┘
