#include "Matrix.h"

void Matrix::setValue(	float n0,  float n1,  float n2,  float n3, 
						float n4,  float n5,  float n6,  float n7, 
						float n8,  float n9,  float n10, float n11, 
						float n12, float n13, float n14, float n15	) {

	mat[0][0] = n0;
	mat[0][1] = n1;
	mat[0][2] = n2;
	mat[0][3] = n3;

	mat[1][0] = n4;
	mat[1][1] = n5;
	mat[1][2] = n6;
	mat[1][3] = n7;

	mat[2][0] = n8;
	mat[2][1] = n9;
	mat[2][2] = n10;
	mat[2][3] = n11;

	mat[3][0] = n12;
	mat[3][1] = n13;
	mat[3][2] = n14;
	mat[3][3] = n15;
}