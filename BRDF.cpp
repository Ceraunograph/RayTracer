#include "BRDF.h"

void BRDF::setValue(Color _kd, Color _ks, Color _ka, Color _kr) {
	kd = _kd;
	ks = _ks;
	ka = _ka;
	kr = _kr;
}