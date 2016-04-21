//
//  Tracer.cpp
//  RayTracer
//

#include "Tracer.h"

Tracer::Tracer()
:   m_pWorld(nullptr)
{}

Tracer::Tracer(const std::shared_ptr<World> a_pWorld)
:   m_pWorld(a_pWorld)
{}

Tracer::~Tracer()
{}

RGBColor Tracer::traceRay(const Ray& a_ray) const
{
    return RGBColor(0.0);
}

RGBColor Tracer::traceRay(const Ray& a_ray, int a_depth) const
{
    return RGBColor(0.0);
}