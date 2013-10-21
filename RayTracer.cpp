#include "RayTracer.h"
#include <iostream>

void RayTracer::trace(Ray& ray, int depth, Color* color) {

	color->setValue(0.0, 0.0, 0.0);

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
			Ray* lray = new Ray;
			Color* lcolor = new Color;
			float dist;
			bool pointLight;

			(*it).generateLightRay(in.localGeo, lray, lcolor, &dist, &pointLight);
			
			// Check if the light is blocked or not (shadows)
			if (!primitive.intersectP(*lray, thit, in)) {
				// If not blocked, do shading calculation for this
				// light source

				Color tempColor;
				tempColor = shading(in, brdf, *lray, ray, *lcolor, brdf.shine, dist, pointLight);
				color->add(tempColor);
			} else {
				//color->setValue(0.0, 0.0, 0.0);
			}
			/*
			Color tempColor;
			tempColor = shading(in, brdf, *lray, ray, *lcolor, brdf.shine, dist, pointLight);
			color->add(tempColor);
			*/
		}


		if (lights.size() > 0) {
			color->add(brdf.ka);
		} else {
			//std::cout << "no ambient";
		}

		color->add(brdf.kr);


		//std::cout << "hello";
		/*
		// Handle mirror reflection
		if (brdf.kr.r + brdf.kr.g + brdf.kr.b > 0) {
		reflectRay = createReflectRay(in.localGeo, ray);

		Color* tempColor = new Color;
		// Make a recursive Call to trace the reflected ray
		trace(reflectRay, depth+1, tempColor);
		color->r += brdf.kr.r * tempColor->r;
		color->g += brdf.kr.g * tempColor->g;
		color->b += brdf.kr.b * tempColor->b;
		}
		*/

	}
}

void RayTracer::setValue(AggregatePrimitive _ap, int _max_depth, std::vector<Light> _lights, Color _attenuation) {
	primitive = _ap;
	max_depth = _max_depth;
	lights = _lights;
	attenuation = _attenuation;
}

Ray RayTracer::createReflectRay(LocalGeo local, Ray ray) {
	Vector* normal_vector = new Vector;
	normal_vector->setValue(local.normal.x, local.normal.y, local.normal.z);

	Point ray_pos = local.pos;

	Vector* original_ray_dir = new Vector;
	original_ray_dir->setValue(ray.dir.x, ray.dir.y, ray.dir.z);

	float temp = original_ray_dir->dotProduct(*normal_vector)*2;
	original_ray_dir->multiply(temp);

	Vector ray_vector;
	ray_vector.setValue(ray_pos.x, ray_pos.y, ray_pos.z);

	ray_vector.subtract(*original_ray_dir);

	Ray return_ray;
	return_ray.setValue(ray_pos, ray_vector, ray.t_min, ray.t_max);
	return return_ray;
}

Color RayTracer::shading(Intersection in, BRDF brdf, Ray lray, Ray vray, Color lcolor, float coeff, float dist, bool pointLight) {
	Color color;
	Vector normal_vector;

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

	reflect.setValue(in.localGeo.normal.x * scalar, in.localGeo.normal.y * scalar, in.localGeo.normal.z * scalar);
	reflect.setValue(reflect.x - lray.dir.x, reflect.y - lray.dir.y, reflect.z - lray.dir.z);
	reflect.normalize();
	
	Ray tempRay;
	Vector tempVect;
	tempVect.setValue(-vray.dir.x, -vray.dir.y, -vray.dir.z);
	tempRay.setValue(vray.pos, tempVect, vray.t_min, vray.t_max);

	tempRay = in.primitive->objToWorld * tempRay;
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