//
//  Normal.cpp
//  RayTracer
//

#include <assert.h>
#include <cmath>

#include "Normal.h"

#include "Vector.h"

Normal::Normal()
:   m_x(0.0f),
    m_y(0.0f),
    m_z(0.0f)
{}

Normal::Normal(double a_k)
:   m_x(a_k),
    m_y(a_k),
    m_z(a_k)
{}

Normal::Normal(double a_x, double a_y, double a_z)
:   m_x(a_x),
    m_y(a_y),
    m_z(a_z)
{}

Normal::Normal(const Normal& a_n)
:   m_x(a_n.m_x),
    m_y(a_n.m_y),
    m_z(a_n.m_z)
{}

Normal::Normal(const Vector& a_v)
:   m_x(a_v.m_x),
    m_y(a_v.m_y),
    m_z(a_v.m_z)
{}

Normal::~Normal()
{}

Normal& Normal::operator=(const Normal& a_n)
{
    if (this == &a_n)
    {
        return *this;
    }
    
    m_x = a_n.m_x;
    m_y = a_n.m_y;
    m_z = a_n.m_z;
    
    return *this;
}

Normal& Normal::operator=(const Vector& a_v)
{
    m_x = a_v.m_x;
    m_y = a_v.m_y;
    m_z = a_v.m_z;
    
    return *this;
}

Normal& Normal::operator=(const Point& a_p)
{
    m_x = a_p.m_x;
    m_y = a_p.m_y;
    m_z = a_p.m_z;
    
    return *this;
}

double Normal::norm() const
{
    return sqrt(squareNorm());
}

Normal Normal::normalize() const
{
    double inv = 1.0f / norm();
    
    return Normal(m_x*inv, m_y*inv, m_z*inv);
}