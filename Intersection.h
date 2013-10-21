#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "LocalGeo.h"
#include "Primitive.h"

class LocalGeo;
class GeometricPrimitive;

class Intersection {
public:
	LocalGeo localGeo;
	GeometricPrimitive* primitive;
    void setValue(LocalGeo _localGeo, GeometricPrimitive* _primitive);
};

#endif
