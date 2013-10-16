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
void Light::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	Ray lightRay;
	Color lightColor;
	if (directional){
		lightRay.pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lightRay.dir.setValue(dir.x, dir.y, dir.z);
                lightRay.t_min = 0.0;
		lightRay.t_max = std::numeric_limits<float>::max();

		lightColor.setValue(color.r, color.g, color.b);

		lcolor = &lightColor;
		lray = &lightRay;
	}else if (point) {
		lightRay.pos.setValue(local.pos.x, local.pos.y, local.pos.z);
		lightRay.dir.createFromPoints(lightRay.pos, source);
		lightRay.t_min = 0.0;
		lightRay.t_max = std::numeric_limits<float>::max();

		lightColor.setValue(color.r, color.g, color.b);

		lcolor = &lightColor;
		lray = &lightRay;
	}else{
		// throw an exception maybe?
	}
}
