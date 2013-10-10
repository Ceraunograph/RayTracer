#include "Ray.h"

void Ray::setValue(Point p, Vector v, float min, float max) {
	pos = p;
	dir = v;
	t_min = min;
	t_max = max;
}