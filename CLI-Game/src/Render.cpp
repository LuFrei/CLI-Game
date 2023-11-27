#include <iostream>
#include <vector>
#include "Render.h"

namespace Render {
	std::vector<Rect> Renderer::rectangles;

	/// <summary>
	/// Counter to assign new Rets unique Ids.
	/// </summary>
	unsigned int rectIdCounter = 0;

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

		std::cout << "Deleting Renderer with rect id: " << rect.id << std::endl;

		// find the index of the correct Rect within the vector
		unsigned int idx = (unsigned int)rectangles.size()/2;

		if (rectangles[idx].id == rect.id) {
			std::cout << "Rect found, deleting ";
		}



	}

	void Renderer::UpdateRects() {

	}
}