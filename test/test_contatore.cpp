#include "gtest/gtest.h"
#include "../src/ContatoreOggetti.h"
#include "../src/ListaDellaSpesa.h"

TEST(ContatoreOggettiTest, InizialmenteZero) {
    ContatoreOggetti c;
    EXPECT_EQ(c.getNumeroOggetti(), 0);
}

TEST(ContatoreOggettiTest, NotificaDopoAggiuntaOggetto) {
    ListaDellaSpesa lista;
    auto c = std::make_shared<ContatoreOggetti>();
    lista.aggiungiObserver(c);
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));

    EXPECT_EQ(c->getNumeroOggetti(), 1);
}

TEST(ContatoreOggettiTest, NotificaDopoRimozioneOggetto) {
    ListaDellaSpesa lista;
    auto c = std::make_shared<ContatoreOggetti>();
    lista.aggiungiObserver(c);
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.aggiungiOggetto(Oggetto("Pane", "Alimentari", 1));
    lista.rimuoviOggetto("Latte");

    EXPECT_EQ(c->getNumeroOggetti(), 1); // solo "Pane" rimasto
}
