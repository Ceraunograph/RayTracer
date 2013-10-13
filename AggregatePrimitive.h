#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H

class AggregatePrimitive : public primitive {
public:
	vector<Primitive*> primitiveList;

	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
