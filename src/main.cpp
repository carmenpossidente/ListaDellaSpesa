#include <iostream>
#include <windows.h>
#include "CLI.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        CLI cli;
        cli.avvia();
    } catch(const std::exception& e) {
        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

