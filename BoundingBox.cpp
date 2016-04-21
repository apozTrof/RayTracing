//
//  BoundingBox.cpp
//  RayTracer
//

#include <limits>
#include <algorithm>
#include <vector>
#include "BoundingBox.h"
#include "Vector.h"

BoundingBox::BoundingBox()
{
    m_pMin = Point(std::numeric_limits<double>::max());
    m_pMax = Point(std::numeric_limits<double>::lowest());
}

BoundingBox::BoundingBox(const Point& a_p)
{
    m_pMin = a_p;
    m_pMax = a_p;
}

BoundingBox::BoundingBox(const Point& m_p1, const Point& m_p2)
{
	m_pMin = Point(std::min(m_p1.m_x, m_p2.m_x), std::min(m_p1.m_y, m_p2.m_y), std::min(m_p1.m_z, m_p2.m_z));
	m_pMax = Point(std::max(m_p1.m_x, m_p2.m_x), std::max(m_p1.m_y, m_p2.m_y), std::max(m_p1.m_z, m_p2.m_z));
}

bool BoundingBox::overlaps(const BoundingBox& m_bb) const
{
	return ((m_bb.m_pMin.m_x >= m_pMin.m_x && m_bb.m_pMax.m_x <= m_pMax.m_x)
		|| (m_bb.m_pMin.m_y >= m_pMin.m_y && m_bb.m_pMax.m_y <= m_pMax.m_y)
		|| (m_bb.m_pMin.m_z >= m_pMin.m_z && m_bb.m_pMax.m_z <= m_pMax.m_z));
}

bool BoundingBox::contains(const Point& a_p) const
{
	return (a_p.m_x >= m_pMin.m_x && a_p.m_y >= m_pMin.m_y && a_p.m_z >= m_pMin.m_z && a_p.m_x <= m_pMax.m_x && a_p.m_y <= m_pMax.m_y && a_p.m_z <= m_pMax.m_z);
}

bool BoundingBox::intersect(const Ray& a_r, double& a_t0, double& a_t1) const
{
	std::vector<double> a_vBuffer;
	double t0, t1, t2, t3, t4, t5;

	t0 = a_r.m_d.m_x == 0 ? 0 : (m_pMin.m_x - a_r.m_o.m_x) / a_r.m_d.m_x;
	t1 = a_r.m_d.m_x == 0 ? 0 : (m_pMax.m_x - a_r.m_o.m_x) / a_r.m_d.m_x;
	t2 = a_r.m_d.m_y == 0 ? 0 : (m_pMin.m_y - a_r.m_o.m_y) / a_r.m_d.m_y;
	t3 = a_r.m_d.m_y == 0 ? 0 : (m_pMax.m_y - a_r.m_o.m_y) / a_r.m_d.m_y;
	t4 = a_r.m_d.m_z == 0 ? 0 : (m_pMin.m_z - a_r.m_o.m_z) / a_r.m_d.m_z;
	t5 = a_r.m_d.m_z == 0 ? 0 : (m_pMax.m_z - a_r.m_o.m_z) / a_r.m_d.m_z;

	if (boxPlaneX(a_r, t0)) { a_vBuffer.push_back(t0); }
	if (boxPlaneX(a_r, t1)) { a_vBuffer.push_back(t1); }
	if (boxPlaneY(a_r, t2)) { a_vBuffer.push_back(t2); }
	if (boxPlaneY(a_r, t3)) { a_vBuffer.push_back(t3); }
	if (boxPlaneZ(a_r, t4)) { a_vBuffer.push_back(t4); }
	if (boxPlaneZ(a_r, t5)) { a_vBuffer.push_back(t5); }

	if (a_vBuffer.empty()) { return false; }

	std::sort(a_vBuffer.begin(), a_vBuffer.end());

	a_t0 = a_vBuffer.front();
	a_t1 = a_vBuffer.back();

	return true;
}

bool BoundingBox::boxPlaneX(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint) { return false; }

	Point pHit = a_ray(a_t);

	if (!((pHit.m_y > m_pMin.m_y) && 
		  (pHit.m_y < m_pMax.m_y) && 
		  (pHit.m_z > m_pMin.m_z) && 
		  (pHit.m_z < m_pMax.m_z))) 
	{ return false; }
	
	return true;
}

bool BoundingBox::boxPlaneY(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint) { return false; }

	Point pHit = a_ray(a_t);

	if (!((pHit.m_x > m_pMin.m_x) && 
		  (pHit.m_x < m_pMax.m_x) && 
		  (pHit.m_z > m_pMin.m_z) && 
		  (pHit.m_z < m_pMax.m_z))) 
	{ return false; }

	return true;
}

bool BoundingBox::boxPlaneZ(const Ray& a_ray, double& a_t) const
{
	if (a_t > a_ray.m_maxt || a_t < a_ray.m_mint) { return false; }

	Point pHit = a_ray(a_t);

	if (!((pHit.m_y > m_pMin.m_y) && 
		  (pHit.m_y < m_pMax.m_y) && 
		  (pHit.m_x > m_pMin.m_x) && 
		  (pHit.m_x < m_pMax.m_x)))
	{ return false; }

	return true;
}

BoundingBox combine(const BoundingBox& m_bb, const Point& m_p)
{
	return combine(m_bb, BoundingBox(m_p));
}

BoundingBox combine(const BoundingBox& m_bb1, const BoundingBox& m_bb2)
{  
    return BoundingBox(Point(std::min(m_bb1.m_pMin.m_x, m_bb2.m_pMin.m_x), std::min(m_bb1.m_pMin.m_y, m_bb2.m_pMin.m_y), std::min(m_bb1.m_pMin.m_z, m_bb2.m_pMin.m_z)), 
					   Point(std::max(m_bb1.m_pMax.m_x, m_bb2.m_pMax.m_x), std::max(m_bb1.m_pMax.m_y, m_bb2.m_pMax.m_y), std::max(m_bb1.m_pMax.m_z, m_bb2.m_pMax.m_z)));
}