#include <iostream>
#include "CLI.h"

int main() {
    try {
        CLI cli;
        cli.avvia();
    } catch(const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}