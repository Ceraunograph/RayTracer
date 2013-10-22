#include "RayTracer.h"
#include <iostream>

void RayTracer::trace(Ray& ray, int depth, Color* color) {

	color->setValue(0.0, 0.0, 0.0);

	if (depth > max_depth) {
		color->setValue(0.0, 0.0, 0.0);
	} else {
		if (!primitive.intersect(ray, &thit, &in)) {
			// No intersection
			color->setValue(0.0, 0.0, 0.0);
		} else {
			//printf("INTERSECTION");
			// Obtain the brdf at intersection point
			in.primitive->getBRDF(in.localGeo, &brdf);

			// There is an intersection, loop through all light source
			for (std::vector<Light*>::iterator it = lights.begin(); it != lights.end(); it++){
				Ray* lray = new Ray;
				Color* lcolor = new Color;
				float dist;
				bool pointLight;

				(**it).generateLightRay(in.localGeo, lray, lcolor, &dist, &pointLight);

				// Check if the light is blocked or not (shadows)
				if (!primitive.intersectP(*lray)) {
					// If not blocked, do shading calculation for this
					// light source
					color->add(shading(in, brdf, *lray, ray, *lcolor, brdf.shine, dist, pointLight));
				}
			}
			if (lights.size() > 0) { 
				color->add(brdf.ka);
			}

			color->add(brdf.kr);

			// Handle mirror reflection
			if (brdf.shine > 0.0) {
				reflectRay = createReflectRay(in, ray, depth);
				// Make a recursive Call to trace the reflected ray
				Color* reflectColor = new Color;
				trace(reflectRay, depth+1.0, reflectColor);

				color->r += /*brdf.ks.r * */reflectColor->r;
				color->g += /*brdf.ks.g * */reflectColor->g;
				color->b += /*brdf.ks.b * */reflectColor->b;
			}
		}
	}
}

void RayTracer::setValue(AggregatePrimitive _ap, int _max_depth, std::vector<Light*> _lights, Color _attenuation) {
	primitive = _ap;
	max_depth = _max_depth;
	lights = _lights;
	attenuation = _attenuation;
}

Ray RayTracer::createReflectRay(Intersection in, Ray ray, int depth) {
	Vector normal_vector;
	Vector reflect;
	Vector viewRay;
	Ray return_ray;

	viewRay.setValue(-ray.dir.x, -ray.dir.y, -ray.dir.z);

	viewRay = in.primitive->objToWorld * (in.primitive->toCameraInverse * viewRay);
	viewRay.normalize();

	normal_vector.setValue(in.localGeo.normal.x, in.localGeo.normal.y, in.localGeo.normal.z);

	float scalar = 2.0 * viewRay.dotProduct(normal_vector);

	reflect.setValue((normal_vector.x * scalar) - viewRay.x, (normal_vector.y * scalar) - viewRay.y, (normal_vector.z * scalar) - viewRay.z);
	reflect.normalize();

	Point cameraSpacePos;
	cameraSpacePos.setValue(in.localGeo.pos.x, in.localGeo.pos.y, in.localGeo.pos.z);

	return_ray.setValue(cameraSpacePos, reflect, 0.00001f, ray.t_max);
	return_ray.dir.normalize();

	return in.primitive->worldToObj * return_ray;
}

Color RayTracer::shading(Intersection in, BRDF brdf, Ray lray, Ray vray, Color lcolor, float coeff, float dist, bool pointLight) {
	Color color;
	Vector normal_vector;

	lray.dir.normalize();
	vray.dir.normalize();

	normal_vector.setValue(in.localGeo.normal.x, in.localGeo.normal.y, in.localGeo.normal.z);
	float diffuse = lray.dir.dotProduct(normal_vector);

	if (diffuse < 0.0) {
		diffuse = 0.0;
	}

	Vector reflect;
	float scalar = 2.0 * lray.dir.dotProduct(normal_vector);

	if (scalar < 0.0) {
		scalar = 0.0;
	}

	reflect.setValue((in.localGeo.normal.x * scalar) - lray.dir.x, (in.localGeo.normal.y * scalar) - lray.dir.y, (in.localGeo.normal.z * scalar) - lray.dir.z);
	reflect.normalize();

	Ray tempRay;
	Vector tempVect;
	tempVect.setValue(-vray.dir.x, -vray.dir.y, -vray.dir.z);
	tempRay.setValue(vray.pos, tempVect, vray.t_min, vray.t_max);

	tempRay = in.primitive->toCameraInverse * tempRay;
	tempRay.dir.normalize();

	float specular = reflect.dotProduct(tempRay.dir);

	if (specular < 0) {
		specular = 0;
	}

	specular = pow(specular, coeff);

	float atten = 1.0;

	if (pointLight){ 
		atten = attenuation.r + attenuation.g * dist + attenuation.b * dist * dist ;
	}

	color.setValue((diffuse * lcolor.r * brdf.kd.r + specular * lcolor.r * brdf.ks.r) / atten,
		(diffuse * lcolor.g * brdf.kd.g + specular * lcolor.g * brdf.ks.g) / atten,
		(diffuse * lcolor.b * brdf.kd.b + specular * lcolor.b * brdf.ks.b) / atten);

	if (color.r < 0.000001) color.r = 0.0;
	if (color.g < 0.000001) color.g = 0.0;
	if (color.b < 0.000001) color.b = 0.0;

	return color;
}