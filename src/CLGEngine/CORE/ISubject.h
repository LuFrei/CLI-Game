#pragma once

#include <map>
#include <forward_list>
#include "IObserver.h" 

class ISubject {
protected:
// TODO(personal): look up types of lists structures and how each effect performance
    std::map<int, std::forward_list<IObserver*>> _observers;
public:
    virtual enum Event{}; // Will this work? Impl class defines Enum values
    virtual ~ISubject() {};
    virtual void Subscribe(int Event, IObserver* o) {};
    virtual void Unsubscribe(int Event, IObserver* o) {};
    virtual void Notify() {};
};