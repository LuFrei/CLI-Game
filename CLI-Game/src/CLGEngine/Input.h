#pragma once
#include <vector>

// - classless namespace?
// We don't need to instantiate Input, we just need it to be readily accessible...
// static class?
namespace Input {

	enum class KeyCode {
		Space = 0x20,
		Left = 0x25, Up, Right, Down,
		Alpha0 = 0x30, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		F1 = VK_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
	};


	class Input {
	private:
		/* For the purposes of this project, I'm hardcoding the bits eac hinput is stored in:
			Bit:Key
			1	Left
			2	Right
			3	Up
			4	Down
		*/

	public:
		/// <summary>
		/// Specify what keys we want to keep track of for user input.
		/// </summary>
		/// <param name="keys">Array of KeyCodes</param>
		static void InitActiveKeys(std::vector<KeyCode> keys);

		/// <summary>
		/// Update state of Active Keys
		/// </summary>
		static void UpdateActiveKeys();

		static bool GetKeyDown(KeyCode key);

		static bool GetKeyDownThisCycle(KeyCode key);

		static bool GetKeyUpThisCycle(KeyCode key);
	};
}