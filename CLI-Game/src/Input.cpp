#include <iostream>
#include <map>
#include <Windows.h>
#include <bitset>
#include <vector>
#include "Input.h"


namespace Input {
	std::map<KeyCode, bool> keyStates;
	std::map<KeyCode, bool> keyDownState;
	std::map<KeyCode, bool> keyDownState;

	enum KeyState {
		KeyState_Toggled = 1,
		KeyState_Down = 0x8000
	};

	void Input::SetActiveKeys(std::vector<KeyCode> keys) {
		for (KeyCode key : keys) {
			keyStates.insert({key, 0});
		}
	}

	void Input::UpdateActiveKeys() {
		std::map<KeyCode, bool> currentStates;

		for (KeyCode key : keys) {
			keyStates.insert({ key, 0 });
		}

		for (auto state : keyStates) {
			currentStates.second = GetKeyState(static_cast<int>(state.first)) & KeyState_Down;
		}

		for (auto state : keyStates) {
			state.second = GetKeyState(static_cast<int>(state.first)) & KeyState_Down;
		}
	}

	bool Input::GetKeyDown(KeyCode key) {
		return keyStates[key];
	}

	/*GET KEY DOWN
	* 
	* Return TRUE if the key was pressed on this call of the function.
	* Return FALSE if the key is not down OR is down, but was already down before this was called.
	* 
	* 
	*/


	bool Input::GetKeyDownThisCycle(KeyCode key) {


		bool currentKeyState = GetKeyState(static_cast<int>(key)) & KeyState_Down;

		if (keyStates[key] == currentKeyState) {
			return 0;
		}
		

		return true;
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