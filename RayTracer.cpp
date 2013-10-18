#include "RayTracer.h"

void RayTracer::trace(Ray& ray, int depth, Color* color) {


	if (depth > max_depth) {
		color->setValue(0.0, 0.0, 0.0);
	}

	if (!primitive.intersect(ray, &thit, &in)) {
		// No intersection

		color->setValue(0.0, 0.0, 0.0);
	} else {
		//printf("INTERSECTION");
		// Obtain the brdf at intersection point
		in.primitive->getBRDF(in.localGeo, &brdf);

		// There is an intersection, loop through all light source
		for (std::vector<Light>::iterator it = lights.begin(); it != lights.end(); it++){
			Ray lray;
			Color lcolor;

			(*it).generateLightRay(in.localGeo, &lray, &lcolor);

			// Check if the light is blocked or not (shadows)
			if (!primitive.intersectP(lray, thit, in)) {
				// If not blocked, do shading calculation for this
				// light source

				Color tempColor;
				tempColor = shading(in.localGeo, brdf, lray, ray, lcolor, brdf.shine);
				color->r += tempColor.r;
				color->g += tempColor.g;
				color->b += tempColor.b;
			}
		}
		color->r += brdf.ka.r;
		color->g += brdf.ka.g;
		color->b += brdf.ka.b;
		/*
		// Handle mirror reflection
		if (brdf.kr.r + brdf.kr.g + brdf.kr.b > 0) {
		reflectRay = createReflectRay(in.localGeo, ray);

		Color tempColor;
		// Make a recursive Call to trace the reflected ray
		trace(reflectRay, depth+1, &tempColor);
		color->r += brdf.kr.r * tempColor.r;
		color->g += brdf.kr.g * tempColor.g;
		color->b += brdf.kr.b * tempColor.b;
		}
		*/
	}
}

void RayTracer::setValue(AggregatePrimitive _ap, int _max_depth, std::vector<Light> _lights) {
	primitive = _ap;
	max_depth = _max_depth;
	lights = _lights;
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

Color RayTracer::shading(LocalGeo local, BRDF brdf, Ray lray, Ray vray, Color lcolor, float coeff) {
	Color color;
	Vector normal_vector;
	normal_vector.setValue(local.normal.x, local.normal.y, local.normal.z);

	float diffuse = normal_vector.dotProduct(lray.dir);

	Vector reflect;
	float scalar = 2 * lray.dir.dotProduct(normal_vector);
	reflect.setValue(local.normal.x * scalar, local.normal.y * scalar, local.normal.z * scalar);
	reflect.setValue(reflect.x - lray.dir.x, reflect.y - lray.dir.y, reflect.z - lray.dir.z);  //reflect vector
	reflect.normalize();
	float specular = reflect.dotProduct(vray.dir);
	specular = pow(specular, coeff);

	color.setValue(diffuse * lcolor.r * brdf.kd.r + specular * lcolor.r * brdf.ks.r,
		diffuse * lcolor.g * brdf.kd.g + specular * lcolor.g * brdf.ks.g, 
		diffuse * lcolor.b * brdf.kd.b + specular * lcolor.b * brdf.ks.b);

	return color;
}