#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Point.h"
#include "Normal.h"

class Point;
class Normal;

class LocalGeo {
public:
	Point pos;
	Normal normal;
	void setValue(Point pos, Normal normal);
};

#endif