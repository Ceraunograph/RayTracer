#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "LocalGeo.h"
#include "Primitive.h"

class LocalGeo;
class Primitive;

class Intersection {
public:
	LocalGeo localGeo;
	Primitive* primitive;
    void setValue(LocalGeo _localGeo, Primitive* _primitive);
};

#endif
