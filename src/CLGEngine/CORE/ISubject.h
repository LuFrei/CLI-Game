#pragma once

#include "IObserver.h"

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void AddSubscriber(IObserver* o) = 0;
    virtual void RemoveSubscriber(IObserver* o) = 0;
    virtual void Notify() = 0;
};