#include <iostream>
#include <map>
#include <Windows.h>
#include <bitset>
#include <vector>
#include "Input.h"

#define KS_DOWN 0x8000
#define KS_CHANGED 1

namespace Input {
	int keys[254];

	void Input::UpdateAllInputState() {
		for(int i = 1; i < 254; i++){
			int keyState = GetAsyncKeyState(i) & KS_DOWN;
			keyState += ((keys[i] & KS_DOWN) != keyState);
			keys[i] = keyState;
		}
	}

	bool Input::GetKeyPressed(KeyCode key){
		return keys[key] & KS_DOWN;
	}

	bool Input::GetKeyJustPressed(KeyCode key){
		return GetKeyPressed(key) 
			&& (keys[key] & KS_CHANGED);
	}

	bool Input::GetKeyJustReleased(KeyCode key){
		return !GetKeyPressed(key) 
			&& (keys[key] & KS_CHANGED);
	}
}