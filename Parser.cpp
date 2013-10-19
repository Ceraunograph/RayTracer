#include "Parser.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;


void Parser::loadScene(std::string file) {

	maxDepth = 0;
	shininess = 1.0;
	kr.setValue(0.0, 0.0, 0.0);
	ka.setValue(0.0, 0.0, 0.0);
	ks.setValue(0.0, 0.0, 0.0);
	kd.setValue(0.0, 0.0, 0.0);

	matrixStack(0,0) = 1;
	matrixStack(0,1) = 0;
	matrixStack(0,2) = 0;
	matrixStack(0,3) = 0;
	matrixStack(1,0) = 0;
	matrixStack(1,1) = 1;
	matrixStack(1,2) = 0;
	matrixStack(1,3) = 0;
	matrixStack(2,0) = 0;
	matrixStack(2,1) = 0;
	matrixStack(2,2) = 1;
	matrixStack(2,3) = 0;
	matrixStack(3,0) = 0;
	matrixStack(3,1) = 0;
	matrixStack(3,2) = 0;
	matrixStack(3,3) = 1;

	std::string fname = "output.bmp";

	std::ifstream inpfile(file.c_str());
	if(!inpfile.is_open()) {
		std::cout << "Unable to open file" << std::endl;
	} else {
		std::string line;

		while(inpfile.good()) {
			std::vector<std::string> splitline;
			std::string buf;

			std::getline(inpfile,line);
			std::stringstream ss(line);

			while (ss >> buf) {
				splitline.push_back(buf);
			}
			//Ignore blank lines
			if(splitline.size() == 0) {
				continue;
			}

			//Ignore comments
			if(splitline[0][0] == '#') {
				continue;
			}

			//Valid commands:
			//size width height
			//  must be first command of file, controls image size
			else if(!splitline[0].compare("size")) {

				width = atoi(splitline[1].c_str());
				height = atoi(splitline[2].c_str());

			}
			//maxdepth depth
			//  max # of bounces for ray (default 5)
			else if(!splitline[0].compare("maxdepth")) {
				// maxdepth: atoi(splitline[1].c_str())

				maxDepth = atoi(splitline[1].c_str());
			}
			//output filename
			//  output file to write image to 
			else if(!splitline[0].compare("output")) {
				fname = splitline[1];
			}

			//camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
			//  speciﬁes the camera in the standard way, as in homework 2.
			else if(!splitline[0].compare("camera")) {
				// lookfrom:
				//    atof(splitline[1].c_str())
				//    atof(splitline[2].c_str())
				//    atof(splitline[3].c_str())
				// lookat:
				//    atof(splitline[4].c_str())
				//    atof(splitline[5].c_str())
				//    atof(splitline[6].c_str())
				// up:
				//    atof(splitline[7].c_str())
				//    atof(splitline[8].c_str())
				//    atof(splitline[9].c_str())
				// fov: atof(splitline[10].c_str());

				lookFromX = atof(splitline[1].c_str());
				lookFromY = atof(splitline[2].c_str());
				lookFromZ = atof(splitline[3].c_str());
				lookAtX = atof(splitline[4].c_str());
				lookAtY = atof(splitline[5].c_str());
				lookAtZ = atof(splitline[6].c_str());
				lookUpX = atof(splitline[7].c_str());
				lookUpY = atof(splitline[8].c_str());
				lookUpZ= atof(splitline[9].c_str());
				fov = atof(splitline[10].c_str());

				Matrix4f trans;
				trans(0,0) = 1.0; 
				trans(0,1) = 0.0;
				trans(0,2) = 0.0;
				trans(0,3) = -lookFromX;
				trans(1,0) = 0.0;
				trans(1,1) = 1.0;
				trans(1,2) = 0.0;
				trans(1,3) = -lookFromY;
				trans(2,0) = 0.0;
				trans(2,1) = 0.0;
				trans(2,2) = 1.0;
				trans(2,3) = -lookFromZ;
				trans(3,0) = 0.0;
				trans(3,1) = 0.0;
				trans(3,2) = 0.0;
				trans(3,3) = 1.0;
				
				Matrix4f rotate1;
				Vector vector1;
				vector1.setValue(lookAtX - lookFromX, lookAtY - lookFromY, lookAtZ - lookFromZ);
				vector1.normalize();
				Vector vector2;
				vector2.setValue(0.0, lookAtY - lookFromY, lookAtZ - lookFromZ);
				vector2.normalize();
				float cosAngle = vector1.dotProduct(vector2);
				float sinAngle = vector1.crossProduct(vector2).magnitude(); 

				rotate1(0,0) = cosAngle;
				rotate1(0,1) = 0.0;
				rotate1(0,2) = sinAngle;
				rotate1(0,3) = 0.0;
				rotate1(1,0) = 0.0;
				rotate1(1,1) = 1.0;
				rotate1(1,2) = 0.0;
				rotate1(1,3) = 0.0;
				rotate1(2,0) = -sinAngle;
				rotate1(2,1) = 0.0;
				rotate1(2,2) = cosAngle;
				rotate1(2,3) = 0.0;
				rotate1(3,0) = 0.0;
				rotate1(3,1) = 0.0;
				rotate1(3,2) = 0.0;
				rotate1(3,3) = 1.0;

				Matrix4f rotate2;
				vector1.setValue(lookAtX - lookFromX, lookAtY - lookFromY, lookAtZ - lookFromZ);
				vector1.normalize();
				vector2.setValue(0.0, lookAtY - lookFromY, lookAtZ - lookFromZ);
				vector2.normalize();
				cosAngle = vector1.dotProduct(vector2);
				sinAngle = vector1.crossProduct(vector2).magnitude(); 
				rotate2(0,0) = 1.0; 
				rotate2(0,1) = 0.0;
				rotate2(0,2) = 0.0;
				rotate2(0,3) = 0.0;
				rotate2(1,0) = 0.0;
				rotate2(1,1) = cosAngle;
				rotate2(1,2) = -sinAngle;
				rotate2(1,3) = 0.0;
				rotate2(2,0) = 0.0;
				rotate2(2,1) = sinAngle;
				rotate2(2,2) = cosAngle;
				rotate2(2,3) = 0.0;
				rotate2(3,0) = 0.0;
				rotate2(3,1) = 0.0;
				rotate2(3,2) = 0.0;
				rotate2(3,3) = 1.0;

				Matrix4f rotate3;
				vector1.setValue(lookUpX - lookFromX, lookUpY - lookFromY, lookUpZ - lookFromZ);
				vector1.normalize();
				vector2.setValue(0.0, lookUpY - lookFromY, lookUpZ - lookFromZ);
				vector2.normalize();
				cosAngle = vector1.dotProduct(vector2);
				sinAngle = vector1.crossProduct(vector2).magnitude(); 
				rotate3(0,0) = cosAngle; 
				rotate3(0,1) = -sinAngle;
				rotate3(0,2) = 0.0;
				rotate3(0,3) = 0.0;
				rotate3(1,0) = sinAngle;
				rotate3(1,1) = cosAngle;
				rotate3(1,2) = 0.0;
				rotate3(1,3) = 0.0;
				rotate3(2,0) = 0.0;
				rotate3(2,1) = 0.0;
				rotate3(2,2) = 1.0;
				rotate3(2,3) = 0.0;
				rotate3(3,0) = 0.0;
				rotate3(3,1) = 0.0;
				rotate3(3,2) = 0.0;
				rotate3(3,3) = 1.0;

				Matrix4f rotate4;
				vector1.setValue(0.0, lookUpY - lookFromY, lookUpZ - lookFromZ);
				vector1.normalize();
				vector2.setValue(0.0, 1.0, 0.0);
				vector2.normalize();
				cosAngle = vector1.dotProduct(vector2);
				sinAngle = vector1.crossProduct(vector2).magnitude(); 		
				rotate4(0,0) = 1.0; 
				rotate4(0,1) = 0.0;
				rotate4(0,2) = 0.0;
				rotate4(0,3) = 0.0;
				rotate4(1,0) = 0.0;
				rotate4(1,1) = cosAngle;
				rotate4(1,2) = -sinAngle;
				rotate4(1,3) = 0.0;
				rotate4(2,0) = 0.0;
				rotate4(2,1) = sinAngle;
				rotate4(2,2) = cosAngle;
				rotate4(2,3) = 0.0;
				rotate4(3,0) = 0.0;
				rotate4(3,1) = 0.0;
				rotate4(3,2) = 0.0;
				rotate4(3,3) = 1.0;
				
				toCamera = rotate4 * rotate3 * rotate2 * rotate1 * trans;
				toCameraInverse = toCamera.inverse();
				matrixStack = toCamera;
			}

			//sphere x y z radius
			//  Deﬁnes a sphere with a given position and radius.
			else if(!splitline[0].compare("sphere")) {
				// x: atof(splitline[1].c_str())
				// y: atof(splitline[1].c_str())
				// z: atof(splitline[1].c_str())
				// r: atof(splitline[4].c_str())
				// Create new sphere:
				//   Store 4 numbers
				//   Store current property values
				//   Store current top of matrix stack

				Point* point = new Point;

				Shape* shape = new Shape;
				shape->setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()), atof(splitline[4].c_str()), *point, *point, *point, 0.0);

				BRDF* brdf = new BRDF;
				brdf->setValue(kd, ks, ka, kr, shininess);

				Material* material = new Material;
				material->setValue(*brdf);

				Matrix4f inverse = matrixStack.inverse();

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(matrixStack);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* sphere = new GeometricPrimitive;
				sphere->setValue(*tInverseMatrix, *tMatrix, shape, material);

				primitives.push_back(*sphere);

			}
			//maxverts number
			//  Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
			//  It must be set before vertices are deﬁned.
			else if(!splitline[0].compare("maxverts")) {
				// Care if you want
				// Here, either declare array size
				// Or you can just use a STL vector, in which case you can ignore this
			}
			//maxvertnorms number
			//  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
			//  It must be set before vertices with normals are deﬁned.
			else if(!splitline[0].compare("maxvertnorms")) {
				// Care if you want
			}
			//vertex x y z
			//  Deﬁnes a vertex at the given location.
			//  The vertex is put into a pile, starting to be numbered at 0.
			else if(!splitline[0].compare("vertex")) {
				// x: atof(splitline[1].c_str()),
				// y: atof(splitline[2].c_str()),
				// z: atof(splitline[3].c_str()));
				// Create a new vertex with these 3 values, store in some array
				Point* p = new Point;
				p->setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
				vertices.push_back(*p);
			}
			//vertexnormal x y z nx ny nz
			//  Similar to the above, but deﬁne a surface normal with each vertex.
			//  The vertex and vertexnormal set of vertices are completely independent
			//  (as are maxverts and maxvertnorms).
			else if(!splitline[0].compare("vertexnormal")) {
				// x: atof(splitline[1].c_str()),
				// y: atof(splitline[2].c_str()),
				// z: atof(splitline[3].c_str()));
				// nx: atof(splitline[4].c_str()),
				// ny: atof(splitline[5].c_str()),
				// nz: atof(splitline[6].c_str()));
				// Create a new vertex+normal with these 6 values, store in some array

				Point* p = new Point;
				p->setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
				verticesNormal.push_back(*p);

			}
			//tri v1 v2 v3
			//  Create a triangle out of the vertices involved (which have previously been speciﬁed with
			//  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
			//  should internally compute a face normal for this triangle.
			else if(!splitline[0].compare("tri")) {
				// v1: atof(splitline[1].c_str())
				// v2: atof(splitline[2].c_str())
				// v3: atof(splitline[3].c_str())
				// Create new triangle:
				//   Store pointer to array of vertices
				//   Store 3 integers to index into array
				//   Store current property values
				//   Store current top of matrix stack
				Shape* shape = new Shape;
				shape->setValue(0, 0, 0, 0, vertices[atof(splitline[1].c_str())], vertices[atof(splitline[2].c_str())], vertices[atof(splitline[3].c_str())], 1.0);

				BRDF* brdf = new BRDF;
				brdf->setValue(kd, ks, ka, kr, shininess);

				Material* material = new Material;
				material->setValue(*brdf);

				Matrix4f inverse = matrixStack.inverse();

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(matrixStack);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* triangle = new GeometricPrimitive;
				triangle->setValue(*tInverseMatrix, *tMatrix, shape, material);

				primitives.push_back(*triangle);
			}
			//trinormal v1 v2 v3
			//  Same as above but for vertices speciﬁed with normals.
			//  In this case, each vertex has an associated normal, 
			//  and when doing shading, you should interpolate the normals 
			//  for intermediate points on the triangle.
			else if(!splitline[0].compare("trinormal")) {
				// v1: atof(splitline[1].c_str())
				// v2: atof(splitline[2].c_str())
				// v3: atof(splitline[3].c_str())
				// Create new triangle:
				//   Store pointer to array of vertices (Different array than above)
				//   Store 3 integers to index into array
				//   Store current property values
				//   Store current top of matrix stack
				Shape* shape = new Shape;
				shape->setValue(NULL, NULL, NULL, NULL, verticesNormal[atof(splitline[1].c_str())], verticesNormal[atof(splitline[2].c_str())], verticesNormal[atof(splitline[3].c_str())], 1.0);

				BRDF* brdf = new BRDF;
				brdf->setValue(kd, ks, ka, kr, shininess);

				Material* material = new Material;
				material->setValue(*brdf);

				Matrix4f inverse = matrixStack.inverse();

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(matrixStack);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* triangle = new GeometricPrimitive;
				triangle->setValue(*tInverseMatrix, *tMatrix, shape, material);

				primitives.push_back(*triangle);
			}

			//translate x y z
			//  A translation 3-vector
			else if(!splitline[0].compare("translate")) {
				// x: atof(splitline[1].c_str())
				// y: atof(splitline[2].c_str())
				// z: atof(splitline[3].c_str())
				// Update top of matrix stack
				Matrix4f translate;
				translate(0,0) = 1.0; 
				translate(0,1) = 0.0;
				translate(0,2) = 0.0;
				translate(0,3) = atof(splitline[1].c_str());
				translate(1,0) = 0.0;
				translate(1,1) = 1.0;
				translate(1,2) = 0.0;
				translate(1,3) = atof(splitline[2].c_str());
				translate(2,0) = 0.0;
				translate(2,1) = 0.0;
				translate(2,2) = 1.0;
				translate(2,3) = atof(splitline[3].c_str());
				translate(3,0) = 0.0;
				translate(3,1) = 0.0;
				translate(3,2) = 0.0;
				translate(3,3) = 1.0;
				matrixStack = translate * matrixStack;
			}
			//rotate x y z angle
			//  Rotate by angle (in degrees) about the given axis as in OpenGL.
			else if(!splitline[0].compare("rotate")) {
				// x: atof(splitline[1].c_str())
				// y: atof(splitline[2].c_str())
				// z: atof(splitline[3].c_str())
				// angle: atof(splitline[4].c_str())
				// Update top of matrix stack
				Matrix4f rotate;
				float x = atof(splitline[1].c_str());
				float y = atof(splitline[2].c_str());
				float z = atof(splitline[3].c_str());
				float angle = atof(splitline[4].c_str());
				if (x == 1.0) {
					rotate(0,0) = 1.0;
					rotate(0,1) = 0.0;
					rotate(0,2) = 0.0;
					rotate(0,3) = 0.0;
					rotate(1,0) = 0.0;
					rotate(1,1) = cos(angle);
					rotate(1,2) = -sin(angle);
					rotate(1,3) = 0.0;
					rotate(2,0) = 0.0;
					rotate(2,1) = sin(angle);
					rotate(2,2) = cos(angle);
					rotate(2,3) = 0.0;
					rotate(3,0) = 0.0;
					rotate(3,1) = 0.0;
					rotate(3,2) = 0.0;
					rotate(3,3) = 1.0;
				} else if (y == 1.0) {
					rotate(0,0) = cos(angle);
					rotate(0,1) = 0.0;
					rotate(0,2) = sin(angle);
					rotate(0,3) = 0.0;
					rotate(1,0) = 0.0;
					rotate(1,1) = 1.0;
					rotate(1,2) = 0.0;
					rotate(1,3) = 0.0;
					rotate(2,0) = -sin(angle);
					rotate(2,1) = 0.0;
					rotate(2,2) = cos(angle);
					rotate(2,3) = 0.0;
					rotate(3,0) = 0.0;
					rotate(3,1) = 0.0;
					rotate(3,2) = 0.0;
					rotate(3,3) = 1.0;
				} else if (z == 1.0) {
					rotate(0,0) = cos(angle);
					rotate(0,1) = -sin(angle);
					rotate(0,2) = 0.0;
					rotate(0,3) = 0.0;
					rotate(1,0) = sin(angle);
					rotate(1,1) = cos(angle);
					rotate(1,2) = 0.0;
					rotate(1,3) = 0.0;
					rotate(2,0) = 0.0;
					rotate(2,1) = 0.0;
					rotate(2,2) = 1.0;
					rotate(2,3) = 0.0;
					rotate(3,0) = 0.0;
					rotate(3,1) = 0.0;
					rotate(3,2) = 0.0;
					rotate(3,3) = 1.0;
				} else {
				}
				matrixStack = rotate * matrixStack;
			}
			//scale x y z
			//  Scale by the corresponding amount in each axis (a non-uniform scaling).
			else if(!splitline[0].compare("scale")) {
				// x: atof(splitline[1].c_str())
				// y: atof(splitline[2].c_str())
				// z: atof(splitline[3].c_str())
				// Update top of matrix stack
				Matrix4f scale;
				scale(0,0) = atof(splitline[1].c_str());
				scale(0,1) = 0.0;
				scale(0,2) = 0.0;
				scale(0,3) = 0.0;
				scale(1,0) = 0.0;
				scale(1,1) = atof(splitline[2].c_str());
				scale(1,2) = 0.0;
				scale(1,3) = 0.0;
				scale(2,0) = 0.0;
				scale(2,1) = 0.0;
				scale(2,2) = atof(splitline[3].c_str());
				scale(2,3) = 0.0;
				scale(3,0) = 0.0;
				scale(3,1) = 0.0;
				scale(3,2) = 0.0;
				scale(3,3) = 1.0;
				matrixStack = scale * matrixStack;


			}
			//pushTransform
			//  Push the current modeling transform on the stack as in OpenGL. 
			//  You might want to do pushTransform immediately after setting 
			//   the camera to preserve the “identity” transformation.
			else if(!splitline[0].compare("pushTransform")) {
				//mst.push();
				Matrix4f camera = toCamera;
				matrixStack = camera;
			}
			//popTransform
			//  Pop the current transform from the stack as in OpenGL. 
			//  The sequence of popTransform and pushTransform can be used if 
			//  desired before every primitive to reset the transformation 
			//  (assuming the initial camera transformation is on the stack as 
			//  discussed above).
			else if(!splitline[0].compare("popTransform")) {
				//mst.pop();
				matrixStack(0,0) = 1;
				matrixStack(0,1) = 0;
				matrixStack(0,2) = 0;
				matrixStack(0,3) = 0;
				matrixStack(1,0) = 0;
				matrixStack(1,1) = 1;
				matrixStack(1,2) = 0;
				matrixStack(1,3) = 0;
				matrixStack(2,0) = 0;
				matrixStack(2,1) = 0;
				matrixStack(2,2) = 1;
				matrixStack(2,3) = 0;
				matrixStack(3,0) = 0;
				matrixStack(3,1) = 0;
				matrixStack(3,2) = 0;
				matrixStack(3,3) = 1;

				//ka.setValue(0, 0, 0);
				//kd.setValue(0, 0, 0);
				//kr.setValue(0, 0, 0);
				//ks.setValue(0, 0, 0);
				//shininess = 1;
			}

			//directional x y z r g b
			//  The direction to the light source, and the color, as in OpenGL.
			else if(!splitline[0].compare("directional")) {
				// x: atof(splitline[1].c_str()),
				// y: atof(splitline[2].c_str()),
				// z: atof(splitline[3].c_str()));
				// r: atof(splitline[4].c_str()),
				// g: atof(splitline[5].c_str()),
				// b: atof(splitline[6].c_str()));
				// add light to scene...
				Vector dir;
				dir.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
				Color color;
				color.setValue(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
				Light* light = new Light;

				Point point;
				point.setValue(1,1,1);

				light->setValue(point, dir, true, false, color);
				lights.push_back(*light);
			}
			//point x y z r g b
			//  The location of a point source and the color, as in OpenGL.
			else if(!splitline[0].compare("point")) {
				// x: atof(splitline[1].c_str()),
				// y: atof(splitline[2].c_str()),
				// z: atof(splitline[3].c_str()));
				// r: atof(splitline[4].c_str()),
				// g: atof(splitline[5].c_str()),
				// b: atof(splitline[6].c_str()));
				// add light to scene...
				Point pos;
				pos.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
				Color color;
				color.setValue(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
				Light* light = new Light;
				Vector vect;
				vect.setValue(1,1,1);

				light->setValue(pos, vect, false, true, color);
				lights.push_back(*light);

			}
			//attenuation const linear quadratic
			//  Sets the constant, linear and quadratic attenuations 
			//  (default 1,0,0) as in OpenGL.
			else if(!splitline[0].compare("attenuation")) {
				// const: atof(splitline[1].c_str())
				// linear: atof(splitline[2].c_str())
				// quadratic: atof(splitline[3].c_str())
			}
			//ambient r g b
			//  The global ambient color to be added for each object 
			//  (default is .2,.2,.2)
			else if(!splitline[0].compare("ambient")) {
				// r: atof(splitline[1].c_str())
				// g: atof(splitline[2].c_str())
				// b: atof(splitline[3].c_str())
				ka.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
			}

			//diﬀuse r g b
			//  speciﬁes the diﬀuse color of the surface.
			else if(!splitline[0].compare("diffuse")) {
				// r: atof(splitline[1].c_str())
				// g: atof(splitline[2].c_str())
				// b: atof(splitline[3].c_str())
				// Update current properties
				kd.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
			}
			//specular r g b 
			//  speciﬁes the specular color of the surface.
			else if(!splitline[0].compare("specular")) {
				// r: atof(splitline[1].c_str())
				// g: atof(splitline[2].c_str())
				// b: atof(splitline[3].c_str())
				// Update current properties
				ks.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
			}
			//shininess s
			//  speciﬁes the shininess of the surface.
			else if(!splitline[0].compare("shininess")) {
				// shininess: atof(splitline[1].c_str())
				// Update current properties
				shininess = atof(splitline[1].c_str());
			}
			//emission r g b
			//  gives the emissive color of the surface.
			else if(!splitline[0].compare("emission")) {
				// r: atof(splitline[1].c_str())
				// g: atof(splitline[2].c_str())
				// b: atof(splitline[3].c_str())
				// Update current properties
				kr.setValue(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
			} else {
				std::cerr << "Unknown command: " << splitline[0] << std::endl;
			}
		}

		inpfile.close();
	}
}