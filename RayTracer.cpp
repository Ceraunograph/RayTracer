#include "RayTracer.h"

void RayTracer::trace(Ray& ray, int depth, Color* color) {
	Color return_color;

	if (depth > max_depth) {
		return_color.setValue(1.0, 1.0, 1.0);
		color = &return_color;
    }

    if (!primitive.intersect(ray, &thit, &in) {
        return_color.setValue(1.0, 1.0, 1.0);
		color = &return_color;
    }

    // Obtain the brdf at intersection point
    in.primitive->getBRDF(in.local, &brdf);
 
    // There is an intersection, loop through all light source
    for (i = 0; i < #lights; i++) {
		lights[i].generateLightRay(in.local, &lray, &lcolor);
                                               
        // Check if the light is blocked or not
        if (!primitive->intersectP(lray))
		// If not, do shading calculation for this
		// light source
        *color += shading(in.local, brdf, lray, lcolor);
	}
 
	// Handle mirror reflection
	if (brdf.kr > 0) {
		reflectRay = createReflectRay(in.local, ray);
 
        // Make a recursive Call to trace the reflected ray
        trace(reflectRay, depth+1, &tempColor);
        *color += brdf.kr * tempColor;
	}
}