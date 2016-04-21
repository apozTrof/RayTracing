//
//  MultipleObjects.cpp
//  RayTracer
//

#include <limits>
#include <cmath>

#include "MultipleObjects.h"
#include "World.h"
#include "Intersection.h"
#include "Normal.h"
#include "Vector.h"

MultipleObjects::MultipleObjects()
:   Tracer()
{}

MultipleObjects::MultipleObjects(const std::shared_ptr<World> a_pWorld)
:   Tracer(a_pWorld)
{}

MultipleObjects::~MultipleObjects()
{}

RGBColor MultipleObjects::traceRay(const Ray& a_ray) const
{
    Intersection inter(m_pWorld);
    double t;
    double tmin = std::numeric_limits<double>::max();
    unsigned long nbObjects = m_pWorld->m_objects.size();
    RGBColor color(m_pWorld->m_backgroundColor);
    
    Vector tmp(0,0,1);
        
    for (int i = 0; i < nbObjects; ++i)
    {
        if (m_pWorld->m_objects[i]->intersect(a_ray, t, inter) && t < tmin)
        {
            tmin = t;
            color = inter.m_color;
        }
    }
    
    return color;
}