#include <iostream>
#include <map>
#include <Windows.h>
#include <bitset>
#include <vector>
#include "Input.h"


namespace Input {
	std::map<KeyCode, bool> keyDownStates;
	std::map<KeyCode, bool> keyPressedStates;
	std::map<KeyCode, bool> keyReleasedStates;
	 
	enum KeyState {
		KeyState_Toggled = 1,
		KeyState_Down = 0x8000
	};

	void Input::InitActiveKeys(std::vector<KeyCode> keys) {
		for (KeyCode key : keys) {
			keyDownStates.insert({key, 0});
			keyPressedStates.insert({ key, 0 });
			keyReleasedStates.insert({ key, 0 });
		}
	}

	void Input::UpdateActiveKeys() {
		// Temporarily cached keys for Up/Down catches before storing them in keyStates
		std::map<KeyCode, bool> newStates;


		// Get new states af of this logic cycle.
		for (auto state : keyDownStates) {
			newStates.insert({ state.first, GetKeyState(static_cast<int>(state.first)) & KeyState_Down});
		}

		// get Key changes signifiying a downed state.
		for (auto state : newStates) {
			keyPressedStates[state.first] = 0;
			keyReleasedStates[state.first] = 0;
			if(newStates[state.first] != keyDownStates[state.first]) {
				if (newStates[state.first]) {
					keyPressedStates[state.first] = 1;
				} else {
					keyReleasedStates[state.first] = 1;
				}
			}
		}

		// update Down states
		keyDownStates = newStates;
	}

	bool Input::GetKeyDown(KeyCode key) {
		return keyDownStates[key];
	}

	bool Input::GetKeyDownThisCycle(KeyCode key) {		
		return keyPressedStates[key];
	}

	bool Input::GetKeyUpThisCycle(KeyCode key) {
		return keyReleasedStates[key];
	}

	// This is gross, disgusting, dirty, but I'm tired of playing Socrates on the best possible solution.
	// I just want it to work.
	
	/// <summary>
	/// stores input as bitmask to check state
	/// </summary>
	/// <param name="key"></param>
	/// <returns>Short representation of bit mask The keycode coresponds to.</returns>
	//short storeState(KeyCode key, bool down) {

	//}
}