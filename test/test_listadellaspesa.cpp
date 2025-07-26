#include "gtest/gtest.h"
#include "../src/ListaDellaSpesa.h"
#include <fstream>

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

TEST(ListaDellaSpesaTest, SalvaECaricaListaFunziona) {
    ListaDellaSpesa listaOriginale;
    listaOriginale.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    listaOriginale.aggiungiOggetto(Oggetto("Pane", "Alimentari", 1));

    std::string filename = "test_lista.json";
    listaOriginale.salvaSuFile(filename);

    ListaDellaSpesa listaCaricata;
    listaCaricata.caricaDaFile(filename);

    const auto& oggetti = listaCaricata.getOggetti();
    ASSERT_EQ(oggetti.size(), 2);

    EXPECT_EQ(oggetti[0].getNome(), "Latte");
    EXPECT_EQ(oggetti[0].getCategoria(), "Alimentari");
    EXPECT_EQ(oggetti[0].getQuantita(), 2);

    EXPECT_EQ(oggetti[1].getNome(), "Pane");
    EXPECT_EQ(oggetti[1].getCategoria(), "Alimentari");
    EXPECT_EQ(oggetti[1].getQuantita(), 1);

    // Rimuove il file temporaneo dopo il test
    std::remove(filename.c_str());
}
