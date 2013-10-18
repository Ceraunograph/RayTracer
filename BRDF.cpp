#include "BRDF.h"

void BRDF::setValue(Color _kd, Color _ks, Color _ka, Color _kr, float _shine) {
	kd = _kd;
	ks = _ks;
	ka = _ka;
	kr = _kr;
	shine = _shine;
}