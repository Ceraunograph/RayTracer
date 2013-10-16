#ifndef FILM_H
#define FILM_H

#include "CImg.h"
#include "Sample.h"
#include "Color.h"

using namespace cimg_library;

class Film {
public:
	CImg<unsigned char> output_image;
	int width, height;
	void setValue(int width, int height);
	void commit(Sample& sample, Color& color);
	void writeImage();
};

#endif