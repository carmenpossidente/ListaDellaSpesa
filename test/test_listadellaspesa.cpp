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

TEST(ListaDellaSpesaTest, FlagAcquistatoFunziona) {
    ListaDellaSpesa lista;
    Oggetto latte("Latte", "Alimentari", 2);
    latte.setAcquistato(true);
    lista.aggiungiOggetto(latte);

    auto oggetti = lista.getOggetti();
    ASSERT_EQ(oggetti.size(), 1);
    EXPECT_TRUE(oggetti[0].isAcquistato());

    // Ora lo salviamo e lo ricarichiamo
    std::string filename = "test_flag_acquistato.json";
    lista.salvaSuFile(filename);

    ListaDellaSpesa lista2;
    lista2.caricaDaFile(filename);

    auto oggetti2 = lista2.getOggetti();
    ASSERT_EQ(oggetti2.size(), 1);
    EXPECT_TRUE(oggetti2[0].isAcquistato());
}

TEST(ListaDellaSpesaTest, FiltraPerCategoria) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.aggiungiOggetto(Oggetto("Shampoo", "Igiene", 1));
    lista.aggiungiOggetto(Oggetto("Pane", "Alimentari", 3));

    auto alimentari = lista.filtraPerCategoria("Alimentari");
    ASSERT_EQ(alimentari.size(), 2);
    EXPECT_EQ(alimentari[0].getNome(), "Latte");
    EXPECT_EQ(alimentari[1].getNome(), "Pane");
}

TEST(ListaDellaSpesaTest, ContatorePerCategoria) {
    ListaDellaSpesa lista;
    lista.aggiungiOggetto(Oggetto("Latte", "Alimentari", 2));
    lista.aggiungiOggetto(Oggetto("Pane", "Alimentari", 1));
    lista.aggiungiOggetto(Oggetto("Sapone", "Igiene", 3));

    auto contatore = lista.contaPerCategoria();
    EXPECT_EQ(contatore["Alimentari"], 3); // 2 + 1
    EXPECT_EQ(contatore["Igiene"], 3);
}

TEST(ListaDellaSpesaTest, TotaleDaAcquistare) {
    ListaDellaSpesa lista;
    auto l = Oggetto("Latte", "Alimentari", 2);
    auto s = Oggetto("Shampoo", "Igiene", 1);
    l.setAcquistato(false);
    s.setAcquistato(true);
    lista.aggiungiOggetto(l);
    lista.aggiungiOggetto(s);
    EXPECT_EQ(lista.getQuantitaDaAcquistare(), 2);
}
