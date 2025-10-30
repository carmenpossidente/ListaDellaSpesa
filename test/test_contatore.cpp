#include "gtest/gtest.h"
#include "../src/ContatoreOggetti.h"

TEST(ContatoreOggettiTest, InizialmenteZero) {
    ContatoreOggetti c;
    EXPECT_EQ(c.getNumeroDaAcquistare(), 0);
}

TEST(ContatoreOggettiTest, NotificaDopoAggiuntaOggetto) {
    ContatoreOggetti c;
    c.aggiorna("Oggetto aggiunto: Latte");

    EXPECT_EQ(c.getNumeroDaAcquistare(), 1);
}

TEST(ContatoreOggettiTest, NotificaDopoRimozioneOggetto) {
    ContatoreOggetti c;
    c.aggiorna("Oggetto aggiunto: Latte");
    c.aggiorna("Oggetto aggiunto: Pane");
    c.aggiorna("Oggetto rimosso: Latte");

    EXPECT_EQ(c.getNumeroDaAcquistare(), 1); // solo "Pane" rimasto
}

TEST(ContatoreOggettiTest, RiceveNotifiche) {
    ContatoreOggetti c;

    // Aggiunta e aggiornamento quantità non cambiano il numero di item "da acquistare"
    c.aggiorna("Oggetto aggiunto: Latte");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 1);

    c.aggiorna("Oggetto aggiornato: Latte (nuova quantità: 2)");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 1);
}

TEST(ContatoreOggettiTest, MarcaAcquistatoDecrementa) {
    ContatoreOggetti c;
    c.aggiorna("Oggetto aggiunto: Mele");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 1);

    c.aggiorna("Oggetto marcato_acquistato: Mele");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 0);
    EXPECT_FALSE(c.isDaAcquistare("Mele"));
}

TEST(ContatoreOggettiTest, MarcaNonAcquistatoIncrementa) {
    ContatoreOggetti c;
    c.aggiorna("Oggetto aggiunto: Mele");
    c.aggiorna("Oggetto marcato_acquistato: Mele");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 0);

    c.aggiorna("Oggetto marcato_non_acquistato: Mele");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 1);
    EXPECT_TRUE(c.isDaAcquistare("Mele"));
}

TEST(ContatoreOggettiTest, RimuoviOggettoAcquistatoNonCambiaContatore) {
    ContatoreOggetti c;
    c.aggiorna("Oggetto aggiunto: Pane");
    c.aggiorna("Oggetto marcato_acquistato: Pane");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 0);

    c.aggiorna("Oggetto rimosso: Pane");
    EXPECT_EQ(c.getNumeroDaAcquistare(), 0);
}