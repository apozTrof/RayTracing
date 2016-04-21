//
//  Whitted.cpp
//  RayTracer
//

#include <limits>

#include "Whitted.h"
#include "Intersection.h"
#include "World.h"

Whitted::Whitted()
:   Tracer()
{}

Whitted::Whitted(const std::shared_ptr<World> a_pWorld)
:   Tracer(a_pWorld)
{}

Whitted::~Whitted()
{}

RGBColor Whitted::traceRay(const Ray& a_ray) const
{
	return traceRay(a_ray, a_ray.m_depth);
}

RGBColor Whitted::traceRay(const Ray& a_ray, int a_depth) const
{
	Intersection inter(m_pWorld);
	Intersection nearest(m_pWorld);
	double t;
	double tmin = std::numeric_limits<double>::max();

	if (a_depth <= m_pWorld->m_vp.m_maxDepth)
	{
		for (int i = 0; i < m_pWorld->m_objects.size(); ++i)
		{
			if (m_pWorld->m_objects[i]->intersect(a_ray, t, inter) && t < tmin && t > 0.001)
			{
				nearest = inter;
				tmin = t;
				// checking if it's inside or outside
				if (dot(nearest.m_normal, a_ray.m_d) > 0)
				{
					nearest.m_normal = -nearest.m_normal;
				}
			}
		}
	}

	if (nearest.m_hit)
	{
		return nearest.m_material->shade(nearest);
	}
	else
	{
		return m_pWorld->m_backgroundColor;
	}
}