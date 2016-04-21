//
//  Cube.cpp
//  RayTracer
//	Antoine Vella 12 035 861


#include "Cube.h"
#include <list>
Cube::Cube(const std::shared_ptr<GeometricTransform> a_pO2W,
	const std::shared_ptr<GeometricTransform> a_pW2O,
	double a_side)
	: GeometricObject(a_pO2W, a_pW2O),
	m_side(a_side),
	half_side(a_side / 2)

{}

BoundingBox Cube::objectBound() const
{
	Point p_min(-half_side, -half_side, -half_side);
	Point p_max(half_side, half_side, half_side);
	return BoundingBox(p_min, p_max);
}

bool Cube::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	double t2, t3;
	Ray objRay;
	(*m_worldToObject)(a_ray, &objRay);
	if (objectBound().intersect(objRay, t2, t3))
	{
		std::list<double> temps;
		double t0, t1, t2, t3, t4, t5, tHit;

		t0 = objRay.m_d.m_x == 0 ? 0 : (-half_side - objRay.m_o.m_x) / objRay.m_d.m_x;
		t1 = objRay.m_d.m_x == 0 ? 0 : (half_side - objRay.m_o.m_x) / objRay.m_d.m_x;
		t2 = objRay.m_d.m_y == 0 ? 0 : (-half_side - objRay.m_o.m_y) / objRay.m_d.m_y;
		t3 = objRay.m_d.m_y == 0 ? 0 : (half_side - objRay.m_o.m_y) / objRay.m_d.m_y;
		t4 = objRay.m_d.m_z == 0 ? 0 : (-half_side - objRay.m_o.m_z) / objRay.m_d.m_z;
		t5 = objRay.m_d.m_z == 0 ? 0 : (half_side - objRay.m_o.m_z) / objRay.m_d.m_z;

		if (planeCubeX(objRay, t0)){ temps.push_back(t0); }
		if (planeCubeX(objRay, t1)){ temps.push_back(t1); }
		if (planeCubeY(objRay, t2)){ temps.push_back(t2); }
		if (planeCubeY(objRay, t3)){ temps.push_back(t3); }
		if (planeCubeZ(objRay, t4)){ temps.push_back(t4); }
		if (planeCubeZ(objRay, t5)){ temps.push_back(t5); }

		if (temps.empty()){ return false; }

		temps.sort();

		Point pHit = a_ray(a_t);

		double a = 0;
		double b = 0;
		double c = 0;

		a_t = temps.front();

		if (abs(a_t - t0) < 0.01){ a = -1; }
		if (abs(a_t - t1) < 0.01){ a = 1; }
		if (abs(a_t - t2) < 0.01){ b = -1; }
		if (abs(a_t - t3) < 0.01){ b = 1; }
		if (abs(a_t - t4) < 0.01){ c = -1; }
		if (abs(a_t - t5) < 0.01){ c = 1; }


		Normal n(a, b, c);

		a_inter.m_hit = true;
		a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
		a_inter.m_normal = (*m_objectToWorld)(n);
		a_inter.m_object = shared_from_this();
		a_inter.m_color = m_color;

		return true;
	}
	return false;
}

double Cube::area() const
{
	double area = 6 * m_side*m_side;

	return area;
}
bool Cube::planeCubeY(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint)
	{
		return false;
	}

	Point pHit = a_ray(a_t);

	if (!((pHit.m_x > -half_side) && (pHit.m_x < half_side) && (pHit.m_z > -half_side) && (pHit.m_z < half_side)))
	{
		return false;
	}

	
	return true;
}

bool Cube::planeCubeX(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint)
	{
		return false;
	}

	Point pHit = a_ray(a_t);

	if (!((pHit.m_y > -half_side) && (pHit.m_y < half_side) && (pHit.m_z > -half_side) && (pHit.m_z < half_side)))
	{
		return false;
	}

	
	return true;
}

bool Cube::planeCubeZ(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint)
	{
		return false;
	}

	Point pHit = a_ray(a_t);

	if (!((pHit.m_y > -half_side) && (pHit.m_y < half_side) && (pHit.m_x > -half_side) && (pHit.m_x < half_side)))
	{
		return false;
	}

	
	return true;
}

