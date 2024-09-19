#pragma once

namespace CLGEngine{
namespace Input {


	// Keycodes taken from Microsoft's Virtual-Key Code Page:
	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	enum KeyCode {
		LeftMouseButton = VK_LBUTTON, RightMouseButton, Cancel, MiddleMouseButton, X1MouseButton, X2MouseButton,
		Backspace = VK_BACK, Tab,
		Clear = VK_CLEAR, Enter,
		Shift = VK_SHIFT, Control, Alt, Pause, CapsLock,
		Escape = VK_ESCAPE,
		Space = VK_SPACE, PageUp, PageDown, End, Home,
		Left, Up, Right, Down,
		Select, Print, Execute, PrintScreen, Insert, Delete, Help,
		Alpha0, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LeftWin, RightWin, Applications,
		Sleep = VK_SLEEP,
		Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Multiply, Add, Seperator, Subtract, Decimal, Divide,
		F1 = VK_F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
		NumLockk = VK_NUMLOCK, ScrollLock,
		LeftShift = VK_LSHIFT, RightShift, LeftControl, RightControl, LeftAlt, RightAlt,
		BrowserBack, BrowserForward /*Are these mouse 4 and 5?*/, BrowserRefresh, BrowserStop, BrowserSearch, BrowserFavorites, BrowserHome,
		VolumeMute, VolumeDown, VolumeUp, MediaNext, MediaPrvious, MediaStop, MediaPlayPause,
		StartApp1, StartApp2,
		SemiColon = VK_OEM_1, Plus, Comma, Dash, Period, ForwSlash, Tilde,
		LeftBracket = VK_OEM_4, BackSlash, RightBracket, Quotes, Misc,
		OEM1 = 0xE1, RT102_AngleBraces, OEM2, OEM3, IME_Proc, OEM4, OEM5 = 0xE9, OEM6, OEM7, OEM8, OEM9, OEM10, OEM11, OEM12, OEM13, OEM14, OEM15, OEM16, OEM17,
		Attn, CrSel, ExSel, Erase_EOF, Play, Zoom, PA1 = VK_PA1, OEM_Clear
	};


	class Input {
	public:
		static void UpdateAllInputState();
		static bool GetKeyPressed(KeyCode key);
		static bool GetKeyJustPressed(KeyCode key);
		static bool GetKeyJustReleased(KeyCode key);
	};
}
}