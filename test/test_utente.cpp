#include <gtest/gtest.h>
#include "../src/Utente.h"

TEST(UtenteTest, CreazioneUtente) {
Utente utente("Mario");
EXPECT_EQ(utente.getUsername(), "Mario");
}

TEST(UtenteTest, CreazioneLista) {
Utente utente("Lucia");
utente.creaLista("Spesa Settimanale");

auto liste = utente.getListePersonali();
EXPECT_EQ(liste.size(), 1);
}