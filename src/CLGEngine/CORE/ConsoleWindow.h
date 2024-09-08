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

		CORE::Vector2<LONG> position;
		CORE::Vector2<LONG> size;
		Graphics::Screen* screen;

		ConsoleWindow();
		~ConsoleWindow();
				
		/// <summary>
		/// Move relative to current position in pixels.
		/// </summary>
		/// <param name="distance">pixel distance</param>
		void Move(Vector2<LONG> distance);
		/// <summary>
		/// Move to specific location in Pixels.
		/// </summary>
		/// <param name="newPosition">pixel coordinate</param>
		void SetPosition(Vector2<LONG> newPosition);
		/// <summary>
		///  relative to current size in pixels.
		/// </summary>
		/// <param name="distance">pixel distance</param>
		void Resize(Vector2<LONG> deltaSize);
		void SetSize(Vector2<LONG> newsize);
	};


} // namespace CORE
} // namespace CLGEngine