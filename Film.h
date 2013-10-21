#ifndef FILM_H
#define FILM_H

//#define FREEIMAGE_LIB
//#include "FreeImage.h"
#include "CImg.h"
#include "Sample.h"
#include "Color.h"
#include <string>

using namespace cimg_library;

class Film {
public:
	int width, height;
	std::string filename;
	CImg<unsigned char> output_image;

	void setValue(int width, int height, std::string file);
	void commit(Sample& sample, Color& color);
	void writeImage();
};

#endif