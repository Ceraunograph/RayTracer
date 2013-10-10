#ifndef COLOR_H
#define COLOR_H

class Color {
public:
	float r,g,b;
	void setValue(float r, float g, float b);
	void add(Color c);
	void subtract(Color c);
	void multiply(float s);
	void divide(float s);
};

#endif