#pragma once
#include <Windows.h>
#include <vector>
#include "Vector2.h"
#include "../Graphics/Screen.h"

namespace CLGEngine {
namespace CORE {
	/// @brief
	/// Represents the main window the app is running on. 
	/// Works as a glorified wrapper for HWND
	class ConsoleWindow {
	// Main Window (This is going to be messy...)
	private:
		/* Note on Main Window it is no different than any other created window, expect: 
			- it's automatically created, therefore needs to be fetched.
			- There can only be ONE
			- We cannot delete it (i believe it shuts the program down)
			- We cannot create it (its done for us)
		*/	
		static ConsoleWindow* _mainWindow; // Difference betwee nusing a ptr here?>
		ConsoleWindow(HWND handle); // KEpeing this private for the sole purpose to create a CoinsoleWindow for the MainWindow
	public:
		static ConsoleWindow* GetMainWindow();
	
	// Main Logic
	public:
		HWND h_window;
		RECT windowRect;

		Vector2<LONG> position;
		Vector2<LONG> size;
		// TODO: the distinciton of whtehr this is a console window should be in Screen
		//		If changing in the future, check here.
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