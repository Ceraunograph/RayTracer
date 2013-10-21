#include "Film.h"
#include <iostream>
#include <cmath>

void Film::setValue(int _width, int _height, std::string file) {
	width = _width;
	height = _height;
	filename = file;
	output_image = CImg<unsigned char>(_width, _height, 1, 32);
}

void Film::commit(Sample& sample, Color& color) {
	/*
	float largest_color = 1.0;
	if (color.r > color.g && color.r > color.b && color.r > 1.0) {
		largest_color = color.r;
	} else if (color.g > color.r && color.g > color.b && color.g > 1.0) {
		largest_color = color.g;
	} else if (color.b > color.r && color.b > color.g && color.b > 1.0) {
		largest_color = color.b;
	} else {
	}
	*/

	if (color.r > 1.0) color.r = 1.0;
	if (color.g > 1.0) color.g = 1.0;
	if (color.b > 1.0) color.b = 1.0;

	int pixel_color[] = { color.r*255.0, color.g*255.0, color.b*255.0 };
	output_image.draw_point(sample.x, sample.y, pixel_color);
}

void Film::writeImage() {
	output_image.save(filename.c_str());
}