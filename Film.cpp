#include "Film.h"
#include <iostream>
#include <cmath>

void Film::setValue(int _width, int _height) {
	width = _width;
	height = _height;
	output_image = CImg<unsigned char>(_width, _height, 1, 32);
}

void Film::commit(Sample& sample, Color& color) {

	float largest_color = 1.0;
	if (color.r > color.g && color.r > color.b && color.r > 1.0) {
		largest_color = color.r;
	} else if (color.g > color.r && color.g > color.b && color.g > 1.0) {
		largest_color = color.g;
	} else if (color.b > color.r && color.b > color.g && color.b > 1.0) {
		largest_color = color.b;
	} else {
	}

	int pixel_color[] = { (color.r/largest_color)*255, (color.g/largest_color)*255, (color.b/largest_color)*255 };
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