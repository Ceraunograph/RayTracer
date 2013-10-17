#include "Parser.h"
#include "Scene.h"

void main(int argc, char *argv[]) {
	Parser parser;
	Scene scene;
	parser.loadScene(argv[1]);
	scene.setValue(&parser);
	scene.render();
}