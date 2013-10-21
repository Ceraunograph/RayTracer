#include "Transformation.h"

void Transformation::setValue(Matrix4f& _m) {
	m = _m;
	minvt = m;
	minvt = minvt.inverse().eval();
	minvt.transposeInPlace();
}

Point Transformation::operator*(Point p) {
	Point new_point;
	float x, y, z, w;
	x = p.x * m(0,0) + p.y * m(0,1) + p.z * m(0,2) + m(0,3);
	y = p.x * m(1,0) + p.y * m(1,1) + p.z * m(1,2) + m(1,3);
	z = p.x * m(2,0) + p.y * m(2,1) + p.z * m(2,2) + m(2,3);
	new_point.setValue(x,y,z);
	return new_point;
}

Vector Transformation::operator*(Vector v) {
	Vector new_vector;
	float x, y, z;
	x = v.x * m(0,0) + v.y * m(0,1) + v.z * m(0,2);
	y = v.x * m(1,0) + v.y * m(1,1) + v.z * m(1,2);
	z = v.x * m(2,0) + v.y * m(2,1) + v.z * m(2,2);
	new_vector.setValue(x,y,z);
	return new_vector;
}	

Normal Transformation::operator*(Normal n) {
	Normal* new_normal = new Normal;
	float x, y, z;
	x = n.x * minvt(0,0) + n.y * minvt(0,1) + n.z * minvt(0,2);
	y = n.x * minvt(1,0) + n.y * minvt(1,1) + n.z * minvt(1,2);
	z = n.x * minvt(2,0) + n.y * minvt(2,1) + n.z * minvt(2,2);
	new_normal->setValue(x,y,z);
	return *new_normal;
}


Ray Transformation::operator*(Ray r) {
	Ray new_ray;
	Point new_point;
	Vector new_vector;

	float px, py, pz, vx, vy, vz;

	px = r.pos.x * m(0,0) + r.pos.y * m(0,1) + r.pos.z * m(0,2) + m(0,3);
	py = r.pos.x * m(1,0) + r.pos.y * m(1,1) + r.pos.z * m(1,2) + m(1,3);
	pz = r.pos.x * m(2,0) + r.pos.y * m(2,1) + r.pos.z * m(2,2) + m(2,3);
	new_point.setValue(px,py,pz);

	vx = r.dir.x * m(0,0) + r.dir.y * m(0,1) + r.dir.z * m(0,2);
	vy = r.dir.x * m(1,0) + r.dir.y * m(1,1) + r.dir.z * m(1,2);
	vz = r.dir.x * m(2,0) + r.dir.y * m(2,1) + r.dir.z * m(2,2);
	new_vector.setValue(vx,vy,vz);

	new_ray.setValue(new_point, new_vector, r.t_min, r.t_max);
	return new_ray;
}

LocalGeo Transformation::operator*(LocalGeo g) {
	LocalGeo new_localGeo;

	Normal new_normal;
	float nx, ny, nz;
	nx = g.normal.x * minvt(0,0) + g.normal.y * minvt(0,1) + g.normal.z * minvt(0,2);
	ny = g.normal.x * minvt(1,0) + g.normal.y * minvt(1,1) + g.normal.z * minvt(1,2);
	nz = g.normal.x * minvt(2,0) + g.normal.y * minvt(2,1) + g.normal.z * minvt(2,2);
	new_normal.setValue(nx,ny,nz);

	Point new_point;
	float px, py, pz;
	px = g.pos.x * m(0,0) + g.pos.y * m(0,1) + g.pos.z * m(0,2) + m(0,3);
	py = g.pos.x * m(1,0) + g.pos.y * m(1,1) + g.pos.z * m(1,2) + m(1,3);
	pz = g.pos.x * m(2,0) + g.pos.y * m(2,1) + g.pos.z * m(2,2) + m(2,3);
	new_point.setValue(px,py,pz);

	new_localGeo.setValue(new_point, new_normal);
	return new_localGeo;
}