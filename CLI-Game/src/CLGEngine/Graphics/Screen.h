#pragma once
#include <Windows.h>

namespace CLGEngine {
	/// <summary>
	/// Object that represents the viewport into the virttual world; i.e. 
	/// the client's screen that renders the game.
	/// </summary>
	class Screen
	{
	private:
		int width;
		int height;

		CHAR_INFO* data;

		bool squareCells;

		void ClearScreenData();
	public:

		Screen(int width, int height);

		// TODO: Implement this. A "cell" in this case should consist of two cells next to each other.
		void SetSquareCells(bool isSquare);
		/// <summary>
		/// Visually display all active Blocks based on their position and dimensions.
		/// </summary>
		void Draw();
	};
}