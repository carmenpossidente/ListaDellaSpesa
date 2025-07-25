#include "gtest/gtest.h"
#include "../src/ListaDellaSpesa.h"

TEST(ListaDellaSpesaTest, AggiuntaOggetto) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));

    auto oggetti = lista.getOggetti();
    ASSERT_EQ(oggetti.size(), 1);
    EXPECT_EQ(oggetti[0].getNome(), "Latte");
    EXPECT_EQ(oggetti[0].getCategoria(), "Alimentari");
    EXPECT_EQ(oggetti[0].getQuantita(), 2);
}

TEST(ListaDellaSpesaTest, AggiuntaDuplicatoIncrementaQuantita) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 1));

    auto oggetti = lista.getOggetti();
    ASSERT_EQ(oggetti.size(), 1);
    EXPECT_EQ(oggetti[0].getQuantita(), 3); // 2 + 1
}

TEST(ListaDellaSpesaTest, RimozioneOggetto) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.rimuoviOggetto("Latte");

    auto oggetti = lista.getOggetti();
    EXPECT_TRUE(oggetti.empty());
}

TEST(ListaDellaSpesaTest, RimuoviOggettoNonPresenteNonCrasha) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Pane", "Alimentari", 1));
    EXPECT_NO_THROW(lista.rimuoviOggetto("Latte"));
}
