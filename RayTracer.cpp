#include "RayTracer.h"

void RayTracer::trace(Ray& ray, int depth, Color* color) {
	Color return_color;
	return_color.setValue(0.0, 0.0, 0.0);

	if (depth > max_depth) {
		return_color.setValue(1.0, 1.0, 1.0);
		color = &return_color;
	}

	if (!primitive.intersect(ray, &thit, &in)) {
		// No intersection
		return_color.setValue(1.0, 1.0, 1.0);
		color = &return_color;
	}

	// Obtain the brdf at intersection point
	in.primitive->getBRDF(in.localGeo, &brdf);

	// There is an intersection, loop through all light source
	for (int i = 0; i < 0; i++) {
		Ray lray;
		Color lcolor;

		lights[i].generateLightRay(in.localGeo, &lray, &lcolor);

		// Check if the light is blocked or not
		if (!primitive.intersectP(lray)) {
			// If not, do shading calculation for this
			// light source
			Color tempColor;
			tempColor = shading(in.localGeo, brdf, lray, lcolor);
			return_color.r += tempColor.r;
			return_color.g += tempColor.g;
			return_color.b += tempColor.b;
			color = &return_color;
		}
	}

	// Handle mirror reflection
	if (brdf.kr.r + brdf.kr.g + brdf.kr.b > 0) {
		reflectRay = createReflectRay(in.localGeo, ray);

		Color tempColor;
		// Make a recursive Call to trace the reflected ray
		trace(reflectRay, depth+1, &tempColor);
		return_color.r += brdf.kr.r * tempColor.r;
		return_color.g += brdf.kr.g * tempColor.g;
		return_color.b += brdf.kr.b * tempColor.b;
		color = &return_color;
	}
}

void RayTracer::setValue(AggregatePrimitive _ap, int _max_depth) {
	primitive = _ap;
	max_depth = _max_depth;
}

Ray RayTracer::createReflectRay(LocalGeo local, Ray ray) {
	Vector normal_vector;
	normal_vector.setValue(local.normal.x, local.normal.y, local.normal.z);

	Point ray_pos = local.pos;

	Vector original_ray_dir;
	original_ray_dir.setValue(ray.dir.x, ray.dir.y, ray.dir.z);

	float temp = original_ray_dir.dotProduct(normal_vector)*2;
	original_ray_dir.multiply(temp);

	Vector ray_vector;
	ray_vector.setValue(ray_pos.x, ray_pos.y, ray_pos.z);

	ray_vector.subtract(original_ray_dir);

	Ray return_ray;
	return_ray.setValue(ray_pos, ray_vector, ray.t_min, ray.t_max);
	return return_ray;
}

Color RayTracer::shading(LocalGeo local, BRDF brdf, Ray ray, Color color) {
	Color ret_color;

	float diffuse;
	Vector normal_vector;
	normal_vector.setValue(local.normal.x, local.normal.y, local.normal.z);



	return ret_color;
}