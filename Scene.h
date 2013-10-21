#ifndef SCENE_H
#define SCENE_H

#include "Sampler.h"
#include "Sample.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Film.h"
#include "RayTracer.h"
#include "Parser.h"

class Color;

class Scene {
public:
	Sampler sampler;
	Sample sample;
	Camera camera;
	RayTracer raytracer;
	Ray ray;
	Color color;
	Film film;
	AggregatePrimitive ap;

	void render();
	void setValue(Parser* p);
};

#endif