#pragma once

#include "../Entity.h"

namespace CLGEngine{
class IObserver {
public:
    virtual ~IObserver() {};
    virtual void OnNotify () = 0; //TODO: add Event support
};
}