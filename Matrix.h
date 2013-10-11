#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	float mat[4][4];
	void setValue(	float n0,  float n1,  float n2,  float n3, 
					float n4,  float n5,  float n6,  float n7, 
					float n8,  float n9,  float n10, float n11, 
					float n12, float n13, float n14, float n15	);
};

#endif