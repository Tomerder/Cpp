#include "Modernizing3.h"

#include <map>

struct Color {
	float a;
	float r;
	float g;
	float b;
	float percent;

	Color() : a(0.0f), r(0), g(0), b(0), percent(0.0f) {}
	Color(float alpha, float red, float green, float blue) : a(alpha), r(red), g(green), b(blue) {}
};

// Adapted from Mandelbrot visualizer
// https://github.com/ansman/mandelbrot/blob/master/coloration.cpp

namespace Coloration {

	int colorationSetup = 0;
	std::map<float, Color> colorMap;

	Color colorArray[] = {
		Color(0.00, 142, 0, 0),
		Color(0.25, 255, 199, 47),
		Color(0.50, 1, 1, 1),
		Color(0.75, 0, 96, 177),
		Color(1.00, 0, 0, 0),
	};

	void setupColoration() {
		for (unsigned int i = 0; i < sizeof(colorArray) / sizeof(Color); ++i)
			colorMap[colorArray[i].percent] = colorArray[i];

		colorationSetup = 1;
	}

	typedef float color;
	typedef float CalcType;

	color * applyColor(CalcType * data, unsigned int width, unsigned int height) {

		color *tex = (color *)malloc(3 * width*height);

		for (unsigned int i = 0; i < width*height; ++i) {
			std::map<float, Color>::iterator it;

			it = colorMap.find(data[i]);

			if (it != colorMap.end()) {
				tex[i * 3] = it->second.r;
				tex[i * 3 + 1] = it->second.g;
				tex[i * 3 + 2] = it->second.b;
				continue;
			}

			std::map<float, Color>::iterator upper = colorMap.lower_bound(data[i]);
			std::map<float, Color>::iterator lower = upper;
			--lower;

			float scale = (data[i] - lower->first) / (upper->first - lower->first);

			Color c1 = lower->second, c2 = upper->second;

			float r, g, b;

			r = c1.r + scale * (c2.r - c1.r);
			g = c1.g + scale * (c2.g - c1.g);
			b = c1.b + scale * (c2.b - c1.b);

			tex[i * 3] = r;
			tex[i * 3 + 1] = g;
			tex[i * 3 + 2] = b;
		}

		return tex;
	}
}