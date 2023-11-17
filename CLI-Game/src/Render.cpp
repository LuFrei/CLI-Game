#include <iostream>
#include "Render.h"

namespace Render {
	/// <summary>
	/// Counter to assign new Rets unique Ids.
	/// </summary>
	int rectIdCounter = 0;

	Renderer::Renderer(int x, int y, int width, int height) {
		rect.id = rectIdCounter;
		rectIdCounter++;

		rect.x = x;
		rect.y = y;
		rect.width = width;
		rect.height = height;

		std::cout << "Created Renderer with Rect id: " << rect.id << std::endl;

		rectangles.push_back(rect);
	}

	Renderer::~Renderer() {
		// Delete the Rects
		// Remove it from Rectangles list

		std::cout << 
	}

	void Renderer::UpdateRects() {

	}
}