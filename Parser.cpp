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

	attenuation.setValue(1.0, 0.0, 0.0);

	idenMatrix << 1, 0, 0, 0,
				  0, 1, 0, 0,
				  0, 0, 1, 0, 
				  0, 0, 0, 1;

	matrixStack.push_back(idenMatrix);

	filename = "output.jpg";

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
				filename = splitline[1];
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

				Vector lookFrom, lookAt, lookUp;
				Point lookAtPoint, lookFromPoint;
				lookFrom.setValue(lookFromX, lookFromY, lookFromZ);
				lookAt.setValue(lookAtX, lookAtY, lookAtZ);
				lookUp.setValue(lookUpX, lookUpY, lookUpZ);

				lookAtPoint.setValue(lookAtX, lookAtY, lookAtZ);
				lookFromPoint.setValue(lookFromX, lookFromY, lookFromZ);

				Vector vx, vy, vz;
				vz.createFromPoints(lookAtPoint, lookFromPoint);
				vx = lookUp.crossProduct(vz);
				vy = vz.crossProduct(vx);	

				vx.normalize();
				vy.normalize();
				vz.normalize();

				Matrix4f transMatrix;
				transMatrix(0,0) = 1.0; 
				transMatrix(0,1) = 0.0;
				transMatrix(0,2) = 0.0;
				transMatrix(0,3) = -lookFromX;
				transMatrix(1,0) = 0.0;
				transMatrix(1,1) = 1.0;
				transMatrix(1,2) = 0.0;
				transMatrix(1,3) = -lookFromY;
				transMatrix(2,0) = 0.0;
				transMatrix(2,1) = 0.0;
				transMatrix(2,2) = 1.0;
				transMatrix(2,3) = -lookFromZ;
				transMatrix(3,0) = 0.0;
				transMatrix(3,1) = 0.0;
				transMatrix(3,2) = 0.0;
				transMatrix(3,3) = 1.0;

				Matrix4f rotateMatrix;
				rotateMatrix(0,0) = vx.x; 
				rotateMatrix(0,1) = vx.y;
				rotateMatrix(0,2) = vx.z;
				rotateMatrix(0,3) = 0.0;
				rotateMatrix(1,0) = vy.x;
				rotateMatrix(1,1) = vy.y;
				rotateMatrix(1,2) = vy.z;
				rotateMatrix(1,3) = 0.0;
				rotateMatrix(2,0) = vz.x;
				rotateMatrix(2,1) = vz.y;
				rotateMatrix(2,2) = vz.z;
				rotateMatrix(2,3) = 0.0;
				rotateMatrix(3,0) = 0.0;
				rotateMatrix(3,1) = 0.0;
				rotateMatrix(3,2) = 0.0;
				rotateMatrix(3,3) = 1.0;

				toCamera = rotateMatrix * transMatrix;
				toCameraInverse = toCamera.inverse();
				//matrixStack.push_back(toCameraInverse);
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

				Matrix4f inverse = matrixStack.back().inverse();
				Matrix4f toWorld = matrixStack.back() * toCameraInverse;

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(toWorld);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* sphere = new GeometricPrimitive;
				sphere->setValue(*tMatrix, *tInverseMatrix, shape, material);

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

				Matrix4f inverse = matrixStack.back().inverse();
				Matrix4f toWorld = matrixStack.back() * toCameraInverse;

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(toWorld);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* triangle = new GeometricPrimitive;
				triangle->setValue(*tMatrix, *tInverseMatrix, shape, material);

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

				Matrix4f inverse = matrixStack.back().inverse();
				Matrix4f toWorld = matrixStack.back() * toCameraInverse;

				Transformation* tMatrix = new Transformation;
				Transformation* tInverseMatrix = new Transformation;

				tMatrix->setValue(toWorld);
				tInverseMatrix->setValue(inverse);

				GeometricPrimitive* triangle = new GeometricPrimitive;
				triangle->setValue(*tMatrix, *tInverseMatrix, shape, material);

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
				matrixStack.back() = translate.inverse() * matrixStack.back();
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
					rotate(1,1) = cos(angle * 3.14159265/180.0);
					rotate(1,2) = -sin(angle * 3.14159265/180.0);
					rotate(1,3) = 0.0;
					rotate(2,0) = 0.0;
					rotate(2,1) = sin(angle * 3.14159265/180.0);
					rotate(2,2) = cos(angle * 3.14159265/180.0);
					rotate(2,3) = 0.0;
					rotate(3,0) = 0.0;
					rotate(3,1) = 0.0;
					rotate(3,2) = 0.0;
					rotate(3,3) = 1.0;
				} else if (y == 1.0) {
					rotate(0,0) = cos(angle * 3.14159265/180.0);
					rotate(0,1) = 0.0;
					rotate(0,2) = sin(angle * 3.14159265/180.0);
					rotate(0,3) = 0.0;
					rotate(1,0) = 0.0;
					rotate(1,1) = 1.0;
					rotate(1,2) = 0.0;
					rotate(1,3) = 0.0;
					rotate(2,0) = -sin(angle * 3.14159265/180.0);
					rotate(2,1) = 0.0;
					rotate(2,2) = cos(angle * 3.14159265/180.0);
					rotate(2,3) = 0.0;
					rotate(3,0) = 0.0;
					rotate(3,1) = 0.0;
					rotate(3,2) = 0.0;
					rotate(3,3) = 1.0;
				} else if (z == 1.0) {
					rotate(0,0) = cos(angle * 3.14159265/180.0);
					rotate(0,1) = -sin(angle * 3.14159265/180.0);
					rotate(0,2) = 0.0;
					rotate(0,3) = 0.0;
					rotate(1,0) = sin(angle * 3.14159265/180.0);
					rotate(1,1) = cos(angle * 3.14159265/180.0);
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
				matrixStack.back() =  rotate.inverse() * matrixStack.back();
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
				matrixStack.back() =  scale.inverse() * matrixStack.back();
			}
			//pushTransform
			//  Push the current modeling transform on the stack as in OpenGL. 
			//  You might want to do pushTransform immediately after setting 
			//   the camera to preserve the “identity” transformation.
			else if(!splitline[0].compare("pushTransform")) {
				//mst.push();
				matrixStack.push_back(matrixStack.back());
			}
			//popTransform
			//  Pop the current transform from the stack as in OpenGL. 
			//  The sequence of popTransform and pushTransform can be used if 
			//  desired before every primitive to reset the transformation 
			//  (assuming the initial camera transformation is on the stack as 
			//  discussed above).
			else if(!splitline[0].compare("popTransform")) {
				//mst.pop();
				matrixStack.pop_back();
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
				attenuation.setValue(atof(splitline[1].c_str()),atof(splitline[2].c_str()),atof(splitline[3].c_str()));
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