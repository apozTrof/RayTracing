//	Antoine Vella 12 035 861
//  Disk.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <cmath>

#include "Disk.h"

Disk::Disk(const std::shared_ptr<GeometricTransform> a_pO2W,
           const std::shared_ptr<GeometricTransform> a_pW2O,
           double a_height, double a_innerRad, double a_outerRad)
:   GeometricObject(a_pO2W,a_pW2O),
    m_height(a_height),
    m_iRad(a_innerRad),
    m_oRad(a_outerRad)
{}

BoundingBox Disk::objectBound() const
{
	return BoundingBox(Point(-m_oRad, m_height, -m_oRad), Point(m_oRad, m_height, m_oRad));
}

bool Disk::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	double t0;

	Ray objRay;
	(*m_worldToObject)(a_ray, &objRay);

	t0 = (m_height - objRay.m_o.m_y) / objRay.m_d.m_y;

	//on verifie t
	if (t0 > objRay.m_maxt || t0 < objRay.m_mint) // j hesite entre <= et <
		return false;

	//calcul dist centre / pt intersect
	Point pHit = objRay(t0);
	double dist = distance(pHit, Point(0, m_height, 0));

	if (dist > m_oRad || dist < m_iRad)
	{
		return false;
	}

	a_t = t0;
	a_inter.m_hit = true;
	a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
	a_inter.m_normal = (*m_objectToWorld)(Point(0, 1, 0));
	a_inter.m_object = shared_from_this();
	a_inter.m_color = m_color;

	return true;
}

double Disk::area() const
{
	return M_PI*((m_oRad*m_oRad) - (m_iRad*m_iRad));
}