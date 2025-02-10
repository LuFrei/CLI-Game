#pragma once

// https://stackoverflow.com/questions/71416/forward-declaring-an-enum-in-c
// Look more into this syntax:

namespace CLGEngine{
enum class Event; 
class IObserver {
public:
    virtual ~IObserver() {};
    virtual void OnNotify (Event e) = 0; //TODO: add Event support
};
}

// Why is Entity here again?