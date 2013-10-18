#include "Scene.h"
#include <vector>

void Scene::render() {
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}

void Scene::setValue(Parser* p) {
	sampler.setValue(p->width, p->height);
	camera.setValue(p->lookFromX, p->lookFromY, p->lookFromZ, p->lookAtX, p->lookAtY, p->lookAtZ, p->lookUpX, p->lookUpY, p->lookUpZ, p->fov, p->width, p->height);

	AggregatePrimitive ap;

	ap.setValue(p->primitives);

	raytracer.setValue(ap, p->maxDepth);
	film.setValue(p->width, p->height);
}