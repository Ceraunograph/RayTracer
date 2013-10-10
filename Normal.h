#ifndef NORMAL_H
#define NORMAL_H

class Normal {
public:
	float x, y, z;
	void setValue(float x, float y, float z);
	void add(Normal n);
	void subtract(Normal n);
};

#endif