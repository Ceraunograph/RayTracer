#include "Transformation.h"

void Transformation::setValue(TMatrix* _m) {
	m = *_m;
	minvt = m;
	minvt.inverse();
	minvt.transpose();
}

Point Transformation::operator*(Point p) {
	Point new_point;
	float x, y, z;
	x = p.x * m.mat(0,0) + p.y * m.mat(0,1) + p.z * m.mat(0,2);
	y = p.x * m.mat(1,0) + p.y * m.mat(1,1) + p.z * m.mat(1,2);
	z = p.x * m.mat(2,0) + p.y * m.mat(2,1) + p.z * m.mat(2,2);
	new_point.setValue(x,y,z);
	return new_point;
}

Vector Transformation::operator*(Vector v) {
	Vector new_vector;
	float x, y, z;
	x = v.x * m.mat(0,0) + v.y * m.mat(0,1) + v.z * m.mat(0,2);
	y = v.x * m.mat(1,0) + v.y * m.mat(1,1) + v.z * m.mat(1,2);
	z = v.x * m.mat(2,0) + v.y * m.mat(2,1) + v.z * m.mat(2,2);
	new_vector.setValue(x,y,z);
	return new_vector;
}	

Normal Transformation::operator*(Normal n) {
	Normal new_normal;
	float x, y, z;
	x = n.x * minvt.mat(0,0) + n.y * minvt.mat(0,1) + n.z * minvt.mat(0,2);
	y = n.x * minvt.mat(1,0) + n.y * minvt.mat(1,1) + n.z * minvt.mat(1,2);
	z = n.x * minvt.mat(2,0) + n.y * minvt.mat(2,1) + n.z * minvt.mat(2,2);
	new_normal.setValue(x,y,z);
	return new_normal;
}


Ray Transformation::operator*(Ray r) {
	Ray new_ray;
	Point new_point;
	Vector new_vector;

	float px, py, pz, vx, vy, vz;

	px = r.pos.x * m.mat(0,0) + r.pos.y * m.mat(0,1) + r.pos.z * m.mat(0,2);
	py = r.pos.x * m.mat(1,0) + r.pos.y * m.mat(1,1) + r.pos.z * m.mat(1,2);
	pz = r.pos.x * m.mat(2,0) + r.pos.y * m.mat(2,1) + r.pos.z * m.mat(2,2);
	new_point.setValue(px,py,pz);

	vx = r.dir.x * m.mat(0,0) + r.dir.y * m.mat(0,1) + r.dir.z * m.mat(0,2);
	vy = r.dir.x * m.mat(1,0) + r.dir.y * m.mat(1,1) + r.dir.z * m.mat(1,2);
	vz = r.dir.x * m.mat(2,0) + r.dir.y * m.mat(2,1) + r.dir.z * m.mat(2,2);
	new_vector.setValue(vx,vy,vz);

	new_ray.setValue(new_point, new_vector, r.t_min, r.t_max);
	return new_ray;
}

LocalGeo Transformation::operator*(LocalGeo g) {
	LocalGeo new_localGeo;

	Normal new_normal;
	float nx, ny, nz;
	nx = g.normal.x * minvt.mat(0,0) + g.normal.y * minvt.mat(0,1) + g.normal.z * minvt.mat(0,2);
	ny = g.normal.x * minvt.mat(1,0) + g.normal.y * minvt.mat(1,1) + g.normal.z * minvt.mat(1,2);
	nz = g.normal.x * minvt.mat(2,0) + g.normal.y * minvt.mat(2,1) + g.normal.z * minvt.mat(2,2);
	new_normal.setValue(nx,ny,nz);

	Point new_point;
	float px, py, pz;
	px = g.pos.x * m.mat(0,0) + g.pos.y * m.mat(0,1) + g.pos.z * m.mat(0,2);
	py = g.pos.x * m.mat(1,0) + g.pos.y * m.mat(1,1) + g.pos.z * m.mat(1,2);
	pz = g.pos.x * m.mat(2,0) + g.pos.y * m.mat(2,1) + g.pos.z * m.mat(2,2);
	new_point.setValue(px,py,pz);

	new_localGeo.setValue(new_point, new_normal);
	return new_localGeo;
}