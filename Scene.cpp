#include "Scene.h"

void Scene::render() {
	while (!sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}


//void main(int argc, char *argv[]) {
//	parser.loadscene(argv[1]);
//	initialize();
//}