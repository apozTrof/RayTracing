//	Antoine Vella 12 035 861
//  Cone.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <cmath>

#include "Cone.h"

Cone::Cone(const std::shared_ptr<GeometricTransform> a_pO2W,
           const std::shared_ptr<GeometricTransform> a_pW2O,
           double a_height, double a_rad)
:   GeometricObject(a_pO2W,a_pW2O),
    m_height(a_height),
    m_rad(a_rad)
{}

BoundingBox Cone::objectBound() const
{
	Point p_min(-m_rad, 0, -m_rad);
	Point p_max(m_rad, m_height, m_rad);
	return BoundingBox(p_min, p_max);
}

bool Cone::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	double t2, t3;
	Ray objRay;
	(*m_worldToObject)(a_ray, &objRay);
	if (objectBound().intersect(objRay, t2, t3))
	{
		double t0 = std::numeric_limits<double>::max();
		double t1;
		double tHit = 0;
		bool a_intersection = false;

		if (HitSide(objRay, t0))
		{
			a_intersection = true;
			tHit = t0;
		}

		if (a_intersection)
		{

			Point pHit = objRay(tHit);

			double yRad = sqrt(pHit.m_x*pHit.m_x + pHit.m_z*pHit.m_z);
			double v = pHit.m_y / m_height;
			double cosPhi = pHit.m_z / yRad;
			double sinPhi = pHit.m_x / yRad;

			Vector dpdu(2 * M_PI*m_rad*(1 - v)*cosPhi, 0, -2 * M_PI*m_rad*(1 - v)*sinPhi);
			Vector dpdv(-m_rad*sinPhi, m_height, -m_rad*cosPhi);
			Normal n(cross(dpdu, dpdv).normalize());
			double phi = atan2(cosPhi, sinPhi) + M_PI;

			a_t = tHit;

			a_inter.m_hit = true;
			a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
			a_inter.m_normal = (*m_objectToWorld)(n);
			a_inter.m_object = shared_from_this();
			a_inter.m_color = m_color;
			a_inter.m_ray = a_ray;
			a_inter.m_material = m_pMaterial;
			a_inter.m_u = phi / (2 * M_PI);
			a_inter.m_v = v;
		}
		return a_intersection;
	}
	return false;
}


double Cone::area() const
{
	double area = M_PI*sqrt(m_rad*m_rad + m_height*m_height);//Surface
	area += M_PI*m_rad*m_rad;//Base
	return area;
}

bool Cone::HitSide(Ray objRay, double& t) const
{
	double y_d = objRay.m_d.m_y;
	double y_o = (objRay.m_o.m_y - m_height);
	double multiplicatif = (m_height / m_rad)*(m_height / m_rad);
	double a = multiplicatif*(objRay.m_d.m_x*objRay.m_d.m_x + objRay.m_d.m_z*objRay.m_d.m_z) - y_d * y_d;
	double b = 2 * (multiplicatif*(objRay.m_d.m_x * objRay.m_o.m_x + objRay.m_d.m_z * objRay.m_o.m_z) - y_d * y_o);
	double c = multiplicatif*(objRay.m_o.m_x*objRay.m_o.m_x + objRay.m_o.m_z*objRay.m_o.m_z) - y_o*y_o;

	double t0, t1;
	if (!QuadraticSolution(a, b, c, &t0, &t1))
	{
		return false;
	}

	if (t0 > objRay.m_maxt || t1 < objRay.m_mint)
	{
		return false;
	}
	double tHit = t0;
	Point p = objRay(tHit);
	if ((p.m_y < 0) || (p.m_y > m_height))
	{
		tHit = t1;
		p = objRay(tHit);
		if ((p.m_y < 0) || (p.m_y > m_height))
		{
			return false;
		}
	}

	if (t0 < objRay.m_mint)
	{
		tHit = t1;
		if (tHit > objRay.m_maxt)
		{
			return false;
		}
		p = objRay(tHit);
		if ((p.m_y < 0) || (p.m_y > m_height))
		{
			return false;
		}
	}

	t = tHit;

	return true;
}

bool Cone::HitBottom(Ray objRay, double& t) const
{
	double t0 = objRay.m_d.m_y == 0 ? 0 : (m_height - objRay.m_o.m_y) / (objRay.m_d.m_y);

	t = t0;
	Point p = objRay(t);

	if (t0 < objRay.m_mint)
	{
		if (t > objRay.m_maxt)
		{
			return false;
		}
	}

	if (p.m_x*p.m_x + p.m_z*p.m_z > m_rad*m_rad)
	{
		return false;
	}

	return true;
}
