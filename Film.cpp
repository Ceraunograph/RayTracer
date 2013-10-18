#include "Film.h"
#include <iostream>

void Film::setValue(int _width, int _height) {
	width = _width;
	height = _height;
	output_image = CImg<unsigned char>(_width, _height, 1, 32);
}

void Film::commit(Sample& sample, Color& color) {
	int pixel_color[] = { color.r*255, color.g*255, color.b*255 };
	output_image.draw_point(sample.x, sample.y, pixel_color);
	/*
	int total_pixels = width * height;
	int pixels_so_far = sample.x *sample.y;
	
	if (pixels_so_far == 0)
		pixels_so_far = 1;

	std::cout << total_pixels/pixels_so_far << "\n";
	*/
	
}

void Film::writeImage() {
	output_image.save("output.jpg");
}