/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GestoreListe.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lista della Spesa");

    GestoreListe gestore;
    gestore.registraUtente("utente1");
    gestore.login("utente1");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        // Qui aggiungerai i componenti GUI
        window.display();
    }

    return 0;
}