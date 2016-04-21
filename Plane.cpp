//
//  Plane.cpp
//  RayTracer
//	Antoine Vella 12 035 861


#include "Plane.h"

Plane::Plane(const std::shared_ptr<GeometricTransform> a_pO2W,
             const std::shared_ptr<GeometricTransform> a_pW2O,
             double a_xMin, double a_xMax,
             double a_zMin, double a_zMax)
:   GeometricObject(a_pO2W, a_pW2O),
    m_xMin(a_xMin),
    m_xMax(a_xMax),
    m_zMin(a_zMin),
    m_zMax(a_zMax)
{}

BoundingBox Plane::objectBound() const
{
	Point pMin = Point(m_xMin, -1, m_zMin);
	Point pMax = Point(m_xMax, 1, m_zMax);

	return BoundingBox(pMin, pMax);
}

bool Plane::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	Ray objRay;
	(*m_worldToObject)(a_ray, &objRay);
	double t0 = -objRay.m_o.m_y / objRay.m_d.m_y;
	//on a un pixel d'epaisseur, correctif pas encore trouve
	if (t0 > objRay.m_maxt || t0 < objRay.m_mint)
	{
		return false;
	}

	double tHit = t0;

	Point pHit = objRay(tHit);

	if (!((pHit.m_x >= m_xMin) && (pHit.m_x <= m_xMax) && (pHit.m_z >= m_zMin) && (pHit.m_z <= m_zMax)))
	{
		return false;
	}

	Normal n(0, 1, 0);

	a_t = tHit;

	a_inter.m_hit = true;
	a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
	a_inter.m_normal = (*m_objectToWorld)(n);
	a_inter.m_object = shared_from_this();
	a_inter.m_color = m_color;
	a_inter.m_ray = a_ray;
	a_inter.m_material = m_pMaterial;
	a_inter.m_u = (pHit.m_x - m_xMin) / (m_xMax - m_xMin);
	a_inter.m_v = (pHit.m_z - m_zMin) / (m_zMax - m_zMin);

	return true;
}

double Plane::area() const
{
	return std::abs(((m_xMax - m_xMin) * (m_zMax - m_zMin)));
}

