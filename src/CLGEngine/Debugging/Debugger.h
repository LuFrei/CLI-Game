#pragma once

#include <map>
#include <string>
#include <vector>

#include "../../../shared.h"

// TODO: Perhaps worth implementing some kind of singleton 
//       to make sure only ONE Debugger exists.
class Debugger{
private:
    // bool _running;
    static std::vector<std::string> _logHistory;

    static struct Shared::Data pData;
    static Shared::Data* sharedData;
    static std::vector<void*> watchedData;
    static std::vector<std::pair<void*, std::string>> testing_watchedData; //val*, type name
public:
    // bool running() {return _running;}
    Debugger();
    ~Debugger();
    static void ToggleActive();
    static void Open();
    static void Close();
    // template<typename T>
    static void AddToWatchList(std::string name, void* value);
    static void UpdateWatchList();
    static void Log(std::string text);
};
