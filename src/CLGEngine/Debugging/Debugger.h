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
};

/* Notes:

Register a message & value in Game Code
Store it here
Value = pointer to value in code
Debugger renders data when relavent (prints message and rewrites data live by writing value of pointer.)

Live Look: auto update values
Message triggers: Prints messsage on a given trigger (adds counter is triggered multiple times.)
- Option for time stamp?
- Drop down for multiple time stamps?

*/

/* Going to try to just send a raw pointer and see if the other process can read it */