#pragma once

#include <map>
#include <string>

class Debugger{
private:
    // TODO: test if we can do variable data types.
    std::map<std::string, int> watchList;
public:
    Debugger();
    void AddToWatchList(std::string name, int* value);
    void DrawList();
};