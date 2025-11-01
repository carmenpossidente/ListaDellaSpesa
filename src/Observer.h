#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <string>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void aggiorna(const std::string& messaggio) = 0;
};

class Observable {
public:
    virtual ~Observable() = default;
    virtual void aggiungiObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void rimuoviObserver(std::shared_ptr<Observer> observer) = 0;

protected:
    virtual void notificaObservers(const std::string& messaggio) = 0;
};

#endif
