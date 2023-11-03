#pragma once

// - classless namespace?
// We don't need to instantiate Input, we just need it to be readily accessible...
// static class?
namespace Input {
	enum KeyState {
		KeyState_Toggled = 1,
		KeyState_Down = 0x8000
	};

	static enum KeyCode {
		KeyCode_Space = 0x20,
		KeyCode_Left = 0x25,
		KeyCode_Up,
		KeyCode_Right,
		KeyCode_Down,
		KeyCode_0 = 0x30,
		KeyCode_1,
		KeyCode_2,
		KeyCode_3,
		KeyCode_4,
		KeyCode_5,
		KeyCode_6,
		KeyCode_7,
		KeyCode_8,
		KeyCode_9,
		KeyCode_A = 0x41,
		KeyCode_B,
		KeyCode_C,
		KeyCode_D,
		KeyCode_E,
		KeyCode_F,
		KeyCode_G,
		KeyCode_H,
		KeyCode_I,
		KeyCode_J,
		KeyCode_K,
		KeyCode_L,
		KeyCode_M,
		KeyCode_N,
		KeyCode_O,
		KeyCode_P,
		KeyCode_Q,
		KeyCode_R,
		KeyCode_S,
		KeyCode_T,
		KeyCode_U,
		KeyCode_V,
		KeyCode_W,
		KeyCode_X,
		KeyCode_Y,
		KeyCode_Z,
	};

	bool GetKeyDown(KeyCode key);

	bool GetKeyToggled(KeyCode key);
}