//
//  PointLight.cpp
//  RayTracer
//

#include "PointLight.h"

PointLight::PointLight()
:   Light(),
    m_ls(1.0),
    m_color(RGBColor(1.0)),
    m_pos(Point(0.0))
{}

PointLight::PointLight(double a_ls, const RGBColor& a_color, const Point& a_pos)
:   Light(),
    m_ls(a_ls),
    m_color(a_color),
    m_pos(a_pos)
{}

PointLight::~PointLight()
{}

Vector PointLight::getDirection(const Intersection& a_inter) const
{
    return ((m_pos - a_inter.m_hitPoint).normalize());
}

