#include "Shape.h"
#include "LocalGeo.h"
#include "Normal.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <iostream>
#include "Parser.h"
#include "Scene.h"
using namespace std;

int main( int argc, const char* argv[] )
{
	Parser parser;
	Scene scene;
	parser.loadScene(argv[1]);
	scene.setValue(&parser);
	scene.render();
	return 0;
}


