#include "RayTracer.h"

void RayTracer::trace(Ray& ray, int depth, Color* color) {
	Color return_color;

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
	/*
    // There is an intersection, loop through all light source
    for (i = 0; i < #lights; i++) {
		lights[i].generateLightRay(in.local, &lray, &lcolor);
                                               
        // Check if the light is blocked or not
        if (!primitive->intersectP(lray))
		// If not, do shading calculation for this
		// light source
        *color += shading(in.local, brdf, lray, lcolor);
	}
	*/
	// Handle mirror reflection
	if (brdf.kr.r + brdf.kr.g + brdf.kr.b > 0) {
		reflectRay = createReflectRay(in.localGeo, ray);
 
		Color tempColor;
        // Make a recursive Call to trace the reflected ray
        trace(reflectRay, depth+1, &tempColor);
        *color += brdf.kr * tempColor;
	}
}

void RayTracer::setValue(AggregatePrimitive _ap, int _max_depth) {
	primitive = _ap;
	max_depth = _max_depth;
}

Ray RayTracer::createReflectRay(LocalGeo local, Ray ray) {
}

void RayTracer::shading(LocalGeo local, BRDF brdf, Color color) {
}