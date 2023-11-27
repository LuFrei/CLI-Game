#pragma once

#include <vector>

// We can store all created instances to update every cycle
namespace Render {

	struct Rect {
	public:
		int id;
		int x, y, width, height;
	};

	class Renderer{
	private:
		static std::vector<Rect> rectangles;
	public:
		Rect rect;
		Renderer(int x, int y, int width, int height);
		~Renderer();

		static void UpdateRects();
	};
}