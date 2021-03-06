#include "Light.h"
#include <limits>

void Light::setValue(Point _source, Vector _dir, bool _directional, bool _point, Color _color){
	directional = _directional;
	point = _point;
	if (directional) {
		dir = _dir;
	}else if (point) {
		source = _source;
	}
	color = _color;
}
void Light::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor, float* dist, bool* pointLight){
	if (directional){
		*pointLight = false;
		lray->pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lray->dir.setValue(dir.x, dir.y, dir.z);
		*dist = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		lray->dir.normalize();
		lray->t_min = 0.00001f;
		lray->t_max = std::numeric_limits<float>::max();

		lcolor->setValue(color.r, color.g, color.b);
	}else if (point) {
		*pointLight = true;
		lray->pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lray->dir.createFromPoints(lray->pos, source);
		*dist = sqrt(pow(lray->dir.x,2.0) + pow(lray->dir.y,2.0) + pow(lray->dir.z,2.0));
		lray->dir.normalize();
		lray->t_min = 0.00001f;

		if (lray->dir.x != 0.0) {
			lray->t_max = (source.x - local.pos.x)/lray->dir.x;
		} else if (lray->dir.y != 0.0) {
			lray->t_max = (source.y - local.pos.y)/lray->dir.y;
		} else {
			lray->t_max = (source.z - local.pos.z)/lray->dir.z;
		}

		lcolor->setValue(color.r, color.g, color.b);
	}else{
		// throw an exception maybe?
	}
}