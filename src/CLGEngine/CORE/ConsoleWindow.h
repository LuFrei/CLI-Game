#pragma once
#include <Windows.h>
#include "Vector2.h"
#include "../Graphics/Screen.h"

namespace CLGEngine {
namespace CORE {
	/// <summary>
	/// Represents the main window the app is running on.
	/// </summary>
	class ConsoleWindow {
	public:
		HWND h_window;
		RECT windowRect;

		Vector2<LONG> position;
		Vector2<LONG> size;
		CLGEngine::Screen* screen;

		ConsoleWindow();
		~ConsoleWindow();

		/// @brief Move relative to current position in pixels.
		/// @param distance pixel distance
		void Move(Vector2<LONG> distance);
		
		/// @brief Move to specific location in Pixels.
		/// @param newPosition pixel coordinate
		void SetPosition(Vector2<LONG> newPosition);
		
		void Resize(Vector2<LONG> deltaSize);
		void SetSize(Vector2<LONG> newsize);
	};


} // namespace CORE
} // namespace CLGEngine