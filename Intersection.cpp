//
//  Intersection.cpp
//  RayTracer
//

#include "Intersection.h"

Intersection::Intersection(const std::shared_ptr<World> a_pWorld)
:   m_pWorld(a_pWorld),
    m_hit(false),
    m_hitPoint(),
    m_normal(),
    m_color(RGBColor(0,0,0)),
    m_object(nullptr),
    m_depth(0),
    m_material(nullptr),
    m_u(0.0),
    m_v(0.0)
{}

Intersection::Intersection(const Intersection& a_i)
:   m_pWorld(a_i.m_pWorld),
    m_hit(a_i.m_hit),
    m_hitPoint(a_i.m_hitPoint),
    m_normal(a_i.m_normal),
    m_color(a_i.m_color),
    m_object(a_i.m_object),
    m_depth(a_i.m_depth),
    m_material(a_i.m_material),
    m_u(a_i.m_u),
    m_v(a_i.m_v)
{}

Intersection::~Intersection()
{}