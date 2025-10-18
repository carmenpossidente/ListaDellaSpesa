#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <string>
#include "Oggetto.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void aggiorna(const std::string& messaggio) = 0;
};

class Observable {
public:
    virtual ~Observable() = default;
    virtual void aggiungiObserver(Observer* observer) = 0;
    virtual void rimuoviObserver(Observer* observer) = 0;
    virtual void notificaObservers(const std::string& messaggio) = 0;
};

#endif
