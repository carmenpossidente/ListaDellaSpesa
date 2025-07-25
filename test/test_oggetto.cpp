#include <gtest/gtest.h>
#include "../src/Oggetto.h"

TEST(OggettoTest, CostruttoreEGetter) {
    Oggetto o("Latte", "Alimentari", 2);
    EXPECT_EQ(o.getNome(), "Latte");
    EXPECT_EQ(o.getCategoria(), "Alimentari");
    EXPECT_EQ(o.getQuantita(), 2);
}

TEST(OggettoTest, SetQuantita) {
    Oggetto o("Pane", "Alimentari", 1);
    o.setQuantita(3);
    EXPECT_EQ(o.getQuantita(), 3);
}

TEST(OggettoTest, Uguaglianza) {
    Oggetto o1("Acqua", "Bevande", 6);
    Oggetto o2("Acqua", "Bevande", 6);
    EXPECT_TRUE(o1 == o2);
}
