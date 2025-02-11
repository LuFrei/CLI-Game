#pragma once

#include "IObserver.h"

// We inheret Event from IObserver

namespace CLGEngine{
class ISubject {
public:
    virtual ~ISubject() {};
    virtual void AddSubscriber(IObserver* o) = 0;
    virtual void RemoveSubscriber(IObserver* o) = 0;
};
}