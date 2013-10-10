#include <iostream>
#include "Color.h"
#include "Sample.h"
#include "Sampler.h"
#include "Vector.h"
using namespace std;

int main() {
	Vector v, w;
	v.setValue(1.0, 2.0, 3.0);
	w.setValue(4.0, 5.0, 6.0);
	v.normalize();
	printf("%f\n", v.z);
	return 0;
}