#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Point.h"
#include "Normal.h"

class LocalGeo {
public:
	Point pos;
	Normal normal;
	void setValue(Point pos, Normal normal);
};

#endif