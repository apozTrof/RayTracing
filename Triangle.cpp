//
//  Triangle.cpp
//  RayTracer
//	Antoine Vella 12 035 861


#include "Triangle.h"
#include "BoundingBox.h"

Triangle::Triangle(const std::shared_ptr<GeometricTransform> a_pO2W,
                   const std::shared_ptr<GeometricTransform> a_pW2O,
                   const Point& a_p1, const Point& a_p2, const Point& a_p3)
:   GeometricObject(a_pO2W,a_pW2O),
    m_p1(a_p1),
    m_p2(a_p2),
    m_p3(a_p3)
{
    m_n = cross(m_p2-m_p1, m_p3-m_p1).normalize();
}

BoundingBox Triangle::objectBound() const
{
	Point p1;
	(*m_worldToObject)(m_p1, &p1);
	Point p2;
	(*m_worldToObject)(m_p2, &p2);
	Point p3;
	(*m_worldToObject)(m_p3, &p3);

	BoundingBox bbBuf(p1, p2);
	bbBuf = combine(bbBuf, p3);
	return bbBuf;
}

BoundingBox Triangle::worldBound() const
{
    
    
	return (*m_objectToWorld)(objectBound());
}

bool Triangle::intersect(const Ray& a_ray, double& a_t, Intersection& a_inter) const
{
	double t2, t3;
	if (worldBound().intersect(a_ray, t2, t3))
	{
		//Barycentre

		double a = m_p1.m_x - m_p2.m_x;
		double b = m_p1.m_x - m_p3.m_x;
		double c = a_ray.m_d.m_x;
		double d = m_p1.m_x - a_ray.m_o.m_x;
		double e = m_p1.m_y - m_p2.m_y;
		double f = m_p1.m_y - m_p3.m_y;
		double g = a_ray.m_d.m_y;
		double h = m_p1.m_y - a_ray.m_o.m_y;
		double i = m_p1.m_z - m_p2.m_z;
		double j = m_p1.m_z - m_p3.m_z;
		double k = a_ray.m_d.m_z;
		double l = m_p1.m_z - a_ray.m_o.m_z;
		double denom = a*(f*k - g*j) + b*(g*i - e*k) + c*(e*j - f*i);
		double denBeta = 0, dGamma = 0, t = 0;
		if (denom != 0)
		{
			denBeta = (d*(f*k - g*j) + b*(g*l - h*k) + c*(h*j - f*l))
				/ denom;
			dGamma = (a*(h*k - g*l) + d*(g*i - e*k) + c*(e*l - h*i))
				/ denom;
			t = (a*(f*l - h*j) + b*(h*i - e*l) + d*(e*j - f*i))
				/ denom;
		}


		//intersection

		if (t < a_ray.m_mint || t > a_ray.m_maxt)
		{
			return false;
		}
		if (!((((denBeta + dGamma) < 1.0) && (denBeta + dGamma) > 0.0) && (denBeta<1.0 && denBeta>0.0) && (dGamma<1.0 && dGamma>0.0)))
		{
			return false;
		}

		Point pHit = a_ray(t);

		a_inter.m_hit = true;
		a_inter.m_hitPoint = pHit;
		a_inter.m_normal = m_n;
		a_inter.m_object = shared_from_this();
		a_inter.m_color = m_color;

		return true;
	}
	return false;
}

double Triangle::area() const
{
	double dCote1 = distance(m_p2, m_p1);
	double dCote2 = distance(m_p3, m_p1);
	return (1 / 2)*(dCote1*dCote2);
    
    return 0;
}