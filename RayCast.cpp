//
//  RayCast.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include <limits>
#include <cmath>

#include "RayCast.h"
#include "Intersection.h"
#include "World.h"

RayCast::RayCast()
:   Tracer()
{}

RayCast::RayCast(const std::shared_ptr<World> a_pWorld)
:   Tracer(a_pWorld)
{}

RayCast::~RayCast()
{}

RGBColor RayCast::traceRay(const Ray& a_ray) const
{
    Intersection inter(m_pWorld);
    Intersection nearest(m_pWorld);
    double t;
    double tmin = std::numeric_limits<double>::max();
    
    for (int i = 0; i < m_pWorld->m_objects.size(); ++i)
    {
        if (m_pWorld->m_objects[i]->intersect(a_ray, t, inter) && t < tmin)
        {
            nearest = inter;
            tmin = t;
            
            if (dot(nearest.m_normal, a_ray.m_d) > 0)
            {
                // Inside intersection
                nearest.m_normal = -nearest.m_normal;
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