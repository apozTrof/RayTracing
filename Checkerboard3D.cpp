//
//  Checkerboard3D.cpp
//  RayTracer
//

#include <math.h>

#include "Checkerboard3D.h"
#include "GeometricObject.h"

Checkerboard3D::Checkerboard3D()
:   m_c1(RGBColor(1.0)),
    m_c2(RGBColor(0.0)),
    m_size(50.0)
{}

Checkerboard3D::Checkerboard3D(const Checkerboard3D& a_cb3)
:   m_c1(a_cb3.m_c1),
    m_c2(a_cb3.m_c2),
    m_size(a_cb3.m_size)
{}

Checkerboard3D::~Checkerboard3D()
{}

RGBColor Checkerboard3D::getColor(const Intersection& a_inter) const
{
    double x = a_inter.m_hitPoint.m_x;
    double y = a_inter.m_hitPoint.m_y;
    double z = a_inter.m_hitPoint.m_z;
    
    if (((int)std::floor(x/m_size) + (int)std::floor(y/m_size) + (int)std::floor(z/m_size)) % 2 == 0 )
    {
        return m_c1;
    }
    else
    {
        return m_c2;
    }
}