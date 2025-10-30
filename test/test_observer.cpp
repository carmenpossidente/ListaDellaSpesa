#include <gtest/gtest.h>
#include "ListaDellaSpesa.h"
#include "ContatoreOggetti.h"
#include "Oggetto.h"
#include <memory>

class ObserverTest : public ::testing::Test {
protected:
    std::shared_ptr<ListaDellaSpesa> lista;
    std::shared_ptr<ContatoreOggetti> contatore;

    void SetUp() override {
        lista = std::make_shared<ListaDellaSpesa>("Test Lista", "TestUser");
        contatore = std::make_shared<ContatoreOggetti>();
        lista->aggiungiObserver(contatore);
    }
};

// Test 1: Aggiunta oggetto incrementa il contatore
TEST_F(ObserverTest, AggiungiOggettoIncrementaContatore) {
Oggetto obj("Mele", "Frutta", 3);
lista->aggiungiOggetto(obj);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);

auto oggettiDaAcquistare = contatore->getListaOggettiDaAcquistare();
EXPECT_EQ(oggettiDaAcquistare.size(), 1);
EXPECT_EQ(oggettiDaAcquistare[0], "Mele");
}

// Test 2: Aggiunta multipla di oggetti
TEST_F(ObserverTest, AggiungiMultipliOggetti) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->aggiungiOggetto(Oggetto("Pane", "Panetteria", 1));
lista->aggiungiOggetto(Oggetto("Latte", "Latticini", 2));

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 3);

auto oggettiDaAcquistare = contatore->getListaOggettiDaAcquistare();
EXPECT_EQ(oggettiDaAcquistare.size(), 3);
}

// Test 3: Marca come acquistato decrementa il contatore
TEST_F(ObserverTest, MarcaAcquistatoDecrementaContatore) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->aggiungiOggetto(Oggetto("Pane", "Panetteria", 1));

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 2);

lista->marcaAcquistato("Mele", true);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);
EXPECT_FALSE(contatore->isDaAcquistare("Mele"));
EXPECT_TRUE(contatore->isDaAcquistare("Pane"));
}

// Test 4: Rimozione oggetto aggiorna il contatore
TEST_F(ObserverTest, RimuoviOggettoAggiorna) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->aggiungiOggetto(Oggetto("Pane", "Panetteria", 1));

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 2);

lista->rimuoviOggetto("Mele");

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);

auto oggettiDaAcquistare = contatore->getListaOggettiDaAcquistare();
EXPECT_EQ(oggettiDaAcquistare.size(), 1);
EXPECT_EQ(oggettiDaAcquistare[0], "Pane");
}

// Test 5: Rimozione di oggetto già acquistato non cambia il contatore
TEST_F(ObserverTest, RimuoviOggettoAcquistatoNonCambiaContatore) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->marcaAcquistato("Mele", true);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 0);

lista->rimuoviOggetto("Mele");

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 0);
}

// Test 6: Aggiornamento quantità (oggetto già esistente)
TEST_F(ObserverTest, AggiornaQuantitaNonCambiaContatore) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);

// Aggiungi di nuovo lo stesso oggetto (incrementa quantità)
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 2));

// Il contatore non deve cambiare (è sempre 1 oggetto da acquistare)
EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);
}

// Test 7: Marca come NON acquistato incrementa il contatore
TEST_F(ObserverTest, MarcaNonAcquistatoIncrementaContatore) {
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->marcaAcquistato("Mele", true);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 0);

// Rimetti tra gli oggetti da acquistare
lista->marcaAcquistato("Mele", false);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);
EXPECT_TRUE(contatore->isDaAcquistare("Mele"));
}

// Test 8: Scenario completo
TEST_F(ObserverTest, ScenarioCompleto) {
// Aggiungi 5 oggetti
lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));
lista->aggiungiOggetto(Oggetto("Pane", "Panetteria", 1));
lista->aggiungiOggetto(Oggetto("Latte", "Latticini", 2));
lista->aggiungiOggetto(Oggetto("Uova", "Latticini", 6));
lista->aggiungiOggetto(Oggetto("Pasta", "Pasta", 2));

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 5);

// Marca 2 come acquistati
lista->marcaAcquistato("Mele", true);
lista->marcaAcquistato("Pane", true);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 3);

// Rimuovi un oggetto da acquistare
lista->rimuoviOggetto("Latte");

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 2);

// Verifica quali sono da acquistare
auto daAcquistare = contatore->getListaOggettiDaAcquistare();
EXPECT_EQ(daAcquistare.size(), 2);
EXPECT_TRUE(std::find(daAcquistare.begin(), daAcquistare.end(), "Uova") != daAcquistare.end());
EXPECT_TRUE(std::find(daAcquistare.begin(), daAcquistare.end(), "Pasta") != daAcquistare.end());
}

// Test 9: Multipli observer sulla stessa lista
TEST_F(ObserverTest, MultipliObserver) {
auto contatore2 = std::make_shared<ContatoreOggetti>();
lista->aggiungiObserver(contatore2);

lista->aggiungiOggetto(Oggetto("Mele", "Frutta", 3));

// Entrambi gli observer devono essere aggiornati
EXPECT_EQ(contatore->getNumeroDaAcquistare(), 1);
EXPECT_EQ(contatore2->getNumeroDaAcquistare(), 1);

lista->marcaAcquistato("Mele", true);

EXPECT_EQ(contatore->getNumeroDaAcquistare(), 0);
EXPECT_EQ(contatore2->getNumeroDaAcquistare(), 0);
}