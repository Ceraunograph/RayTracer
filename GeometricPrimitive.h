#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H

class GeometricPrimitive : public primitive {
public:
	Transformation objToWorld, worldToObj;
	Shape* shape;
	Material* mat;
	
	void setValue(Transformation _objToWorld, Transformation _worldToObj, Shape* shape, Material* mat);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
