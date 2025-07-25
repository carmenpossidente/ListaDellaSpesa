#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "Oggetto.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void aggiorna(const std::vector<Oggetto>& nuovaLista) = 0;
};

#endif
