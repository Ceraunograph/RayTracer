#include "Intersection.h"

void Intersection::setValue(LocalGeo _localGeo, Primitive* _primitive) {
	pos = _localGeo;
	normal = _primitive;
}
