# Input System

## Feature Overview:
- ASCII based KeyCodes
- Getters for when key is:
	- Down
	- PressedThisCycle
	- ReleasedThisCycle

## Quick Start
1. #include "Input.h"\
2. Use `Input::InitActiveKeys()` to initialize Input system with keys you want to keep track of during the life time of your application.\
3. Sync key states with `Input::UpdateActiveKeys()` the updater to sync all cached keys.\
4. Use `Input::GetKeyDown()`, `Input::GetKeyDown()`, and `Input::GetKeyDown()` to get key states

```
#include "Input.h"

using namespace Input

main {
    bool running = true;

    // Initialize the keys Left, Right, Up, Down
    Input::InitActiveKeys(
        {
            KeyCode::Left,
            KeyCode::Right,
            KeyCode::Up,
            KeyCode::Down,
        }
    );

    while (running){
        // Keep key states updated
        Input::UpdateActiveKeys();

        // Get Key Press
        bool spaceDown = Input::GetKeyDown(KeyCode::Space);


        if(spaceDown)
            running = false;
    }
     
}
```

## Basic API

enum class KeyCode

static void Input:\:InitActiveKeys(std::vector<KeyCode> keys);

static void Input::UpdateActiveKeys();

static bool Input::GetKeyDown(KeyCode key);

static bool Input::GetKeyDownThisCycle(KeyCode key);

static bool Input::GetKeyUpThisCycle(KeyCode key);

## Methodology

The Input system keeps track of only the inputs the user will be able to use to interact with the application.\
While this great to keep memory usage only down to what we need, the current implementation leaves no room for user assignable keys.\

All states are tracked via the `UpdateActiveKeys` method, including KeyPressed and KeyReleased states.

`GetKeyDowm`, `GetKeyPressedThisCycle`, and `GetKeyReleasedThisCycle` are simply getters to the data collected from `UpdateActiveKeys`.\
While this may be a bit wasteful as we are potentially checking for keys we may not even or ever want to get the Release or Pressed states from, it is the most direct and simplest solution.
