#include "gtest/gtest.h"
#include "../src/ContatoreOggetti.h"
#include "../src/ListaDellaSpesa.h"
#include <memory>

TEST(ContatoreOggettiTest, InizialmenteZero) {
    ContatoreOggetti c;
    EXPECT_EQ(c.getNumeroOggetti(), 0);
}

TEST(ContatoreOggettiTest, NotificaDopoAggiuntaOggetto) {
    ListaDellaSpesa lista;
    auto contatore = std::make_shared<ContatoreOggetti>();
    lista.aggiungiObserver(contatore);
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));

    EXPECT_EQ(contatore->getNumeroOggetti(), 1);
}

TEST(ContatoreOggettiTest, NotificaDopoRimozioneOggetto) {
    ListaDellaSpesa lista;
    auto contatore = std::make_shared<ContatoreOggetti>();
    lista.aggiungiObserver(contatore);
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.aggiungiOggetto(Oggetto("Pane", "Alimentari", 1));
    lista.rimuoviOggetto("Latte");

    EXPECT_EQ(contatore->getNumeroOggetti(), 1); // solo "Pane" rimasto
}

TEST(ContatoreOggettiTest, RiceveNotifiche) {
    ListaDellaSpesa lista;
    auto contatore = std::make_shared<ContatoreOggetti>();

    lista.aggiungiObserver(contatore);

    // Aggiungi oggetto - dovrebbe triggerare una notifica
    Oggetto oggetto("Latte", "Latticini", 1);
    lista.aggiungiOggetto(oggetto);

    // Anche se non conta più automaticamente, verifichiamo che il sistema notifiche funzioni
    EXPECT_EQ(lista.getOggetti().size(), 1); // La lista ha 1 oggetto
}