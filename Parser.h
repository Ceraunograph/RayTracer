#ifndef PARSER_H
#define PARSER_H

#include "Point.h"
#include "Light.h"
#include "Primitive.h"
#include "Color.h"
#include "Shape.h"
#include "Material.h"
#include "BRDF.h"
#include "GeometricPrimitive.h"
#include "Transformation.h"

#include <vector>
#include <Eigen/LU>
#include <Eigen/Dense>
#include <Eigen/StdVector>

using namespace Eigen;

class Parser {
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	std::vector<GeometricPrimitive, Eigen::aligned_allocator<GeometricPrimitive>> primitives;
	std::vector<Point> vertices;
	std::vector<Point> verticesNormal;
	std::vector<Light> lights;
	Matrix4f toCamera;
	Matrix4f toCameraInverse;
	Matrix4f matrixStack;
	Color kd, ks, ka, kr, attenuation;
	float shininess;
	float width, height;
	int maxDepth;
	float lookFromX, lookFromY, lookFromZ, lookAtX, lookAtY, lookAtZ, lookUpX, lookUpY, lookUpZ, fov;

	void loadScene(std::string file);
};

#endif