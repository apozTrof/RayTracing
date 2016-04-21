//
//  RGBColor.cpp
//  RayTracer
//

#include <cmath>

#include "RGBColor.h"

RGBColor::RGBColor()
:   m_r(0.0),
    m_g(0.0),
    m_b(0.0)
{}

RGBColor::RGBColor(double a_color)
:   m_r(a_color),
    m_g(a_color),
    m_b(a_color)
{}

RGBColor::RGBColor(double a_r, double a_g, double a_b)
:   m_r(a_r),
    m_g(a_g),
    m_b(a_b)
{}

RGBColor::RGBColor(const RGBColor& a_color)
:   m_r(a_color.m_r),
    m_g(a_color.m_g),
    m_b(a_color.m_b)
{}

RGBColor::~RGBColor()
{}

RGBColor RGBColor::powc(const double a_k) const
{
    return (RGBColor(pow(m_r, a_k), pow(m_g,a_k), pow(m_b, a_k)));
}