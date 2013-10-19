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
	Ray lightRay;
	Color lightColor;
	if (directional){
		*pointLight = false;
		lray->pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lray->dir.setValue(dir.x, dir.y, dir.z);
		*dist = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		lray->t_min = 0.0;
		lray->t_max = std::numeric_limits<float>::max();
		//lray->dir.normalize();

		lcolor->setValue(color.r, color.g, color.b);
	}else if (point) {
		*pointLight = true;
		lray->pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lray->dir.createFromPoints(lray->pos, source);
		*dist = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
		lray->t_min = 0.0;
		lray->t_max = std::numeric_limits<float>::max();
		//lray->dir.normalize();

		lcolor->setValue(color.r, color.g, color.b);

	}else{
		// throw an exception maybe?
	}
}