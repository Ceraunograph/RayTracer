#include "Film.h"
#include <iostream>
#include <cmath>

void Film::setValue(int _width, int _height, std::string file) {
	width = _width;
	height = _height;
	filename = file;

	output_image = CImg<unsigned char>(_width, _height, 1, 32);
	//FreeImage_Initialise();
	//bitmap = FreeImage_Allocate(width, height, 24);

	//if(!bitmap){
	//	exit(1);
	//}
}

void Film::commit(Sample& sample, Color& color) {

	if (color.r > 1.0) color.r = 1.0;
	if (color.g > 1.0) color.g = 1.0;
	if (color.b > 1.0) color.b = 1.0;

	unsigned char pixel_color[] = { unsigned char(color.r*255.0+0.5), unsigned char(color.g*255.0+0.5), unsigned char(color.b*255.0+0.5) };
	output_image.draw_point(sample.x, sample.y, pixel_color);
}

void Film::writeImage() {
	output_image.save(filename.c_str());
}