#include "Material.h"

void Material::setValue(BRDF _BRDF) {
	brdf = _BRDF;
}

void Material::getBRDF(LocalGeo& _local, BRDF* _brdf){
	_brdf = &brdf;
}
