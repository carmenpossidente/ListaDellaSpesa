#include <gtest/gtest.h>
#include "../src/GestoreListe.h"

TEST(GestoreListeTest, RegistrazioneUtente) {
GestoreListe gestore;
gestore.registraUtente("Mario");

auto utente = gestore.getUtente("Mario");
EXPECT_NE(utente, nullptr);
EXPECT_EQ(utente->getUsername(), "Mario");
}

TEST(GestoreListeTest, LoginUtente) {
GestoreListe gestore;
gestore.registraUtente("Lucia");

EXPECT_TRUE(gestore.login("Lucia"));
EXPECT_NE(gestore.getUtenteCorrente(), nullptr);
}