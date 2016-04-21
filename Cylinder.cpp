//
//  Cylinder.cpp
//  RayTracer
//	Antoine Vella 12 035 861


#define _USE_MATH_DEFINES

#include <cmath>
#include <limits>

#include "Cylinder.h"

Cylinder::Cylinder(const std::shared_ptr<GeometricTransform> a_pO2W,
                   const std::shared_ptr<GeometricTransform> a_pW2O,
                   double a_rad, double a_yMin, double a_yMax)
:   GeometricObject(a_pO2W, a_pW2O),
    m_rad(a_rad),
    m_yMin(a_yMin),
    m_yMax(a_yMax)
{}

BoundingBox Cylinder::objectBound() const
{
	return BoundingBox(Point(-m_rad, m_yMin, -m_rad), Point(m_rad, m_yMax, m_rad));
}

bool Cylinder::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	Ray objRay;
	(*m_worldToObject)(a_ray, &objRay);

	double a = objRay.m_d.m_x*objRay.m_d.m_x + objRay.m_d.m_z*objRay.m_d.m_z;
	double b = 2 * (objRay.m_d.m_x * objRay.m_o.m_x + objRay.m_d.m_z * objRay.m_o.m_z);
	double c = objRay.m_o.m_x*objRay.m_o.m_x + objRay.m_o.m_z*objRay.m_o.m_z - m_rad*m_rad;
    
	double t0, t1;
	bool check = QuadraticSolution(a, b, c, &t0, &t1);
	if (!check)
	{
		return false;
	}

	if (t0 > objRay.m_maxt || t1 < objRay.m_mint)
	{
		return false;
	}

	
	double tHit = t0;

	if (t0 < objRay.m_mint)
	{
		tHit = t1;
		if (tHit > objRay.m_maxt)
		{
			return false;
		}
	}

	Point pHit = objRay(tHit);
	
	if (pHit.m_y<m_yMin || pHit.m_y>m_yMax )
		return false;
	 
	double temps = m_yMax - m_yMin;
	/*double theta = asin(pHit.m_x / m_rad);
	double u = theta / (2 * M_PI);
	double v = ((pHit.m_y) - m_yMin) / (m_yMax - m_yMin);*/
	Vector dpdu(2 * M_PI*pHit.m_z, 0, -2 * M_PI*pHit.m_x);
	Vector dpdv(0, temps, 0);
	Normal n(cross(dpdv, dpdu).normalize());

	double phi = atan2(pHit.m_x, pHit.m_z) + M_PI;

	a_t = tHit;
	
	
	
	a_inter.m_hit = true;
	a_inter.m_hitPoint = (*m_objectToWorld)(pHit);
	a_inter.m_normal = (*m_objectToWorld)(n);
	a_inter.m_object = shared_from_this();
	a_inter.m_color = m_color;
	a_inter.m_ray = a_ray;
	a_inter.m_material = m_pMaterial;
	a_inter.m_u = phi / (2 * M_PI);
	a_inter.m_v = (pHit.m_y - m_yMin) / (m_yMax - m_yMin);




    return true;
}

double Cylinder::area() const
{
    
    
    return 2*M_PI*m_rad*(m_yMax-m_yMin);
}
