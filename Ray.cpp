//
//  Ray.cpp
//  RayTracer
//

#include <limits>

#include "Ray.h"

Ray::Ray()
:   m_o(0.0, 0.0, 0.0),
    m_d(0.0, 0.0, 1.0),
    m_depth(0),
    m_mint(std::numeric_limits<double>::epsilon()),
    m_maxt(std::numeric_limits<double>::infinity())
{}

Ray::Ray(const Point& a_origin, const Vector& a_direction)
:   m_o(a_origin),
    m_d(a_direction),
    m_depth(0),
    m_mint(std::numeric_limits<double>::epsilon()),
    m_maxt(std::numeric_limits<double>::infinity())
{}

Ray::Ray(const Point& a_origin, const Vector& a_direction, int a_depth, double a_mint, double a_maxt)
:   m_o(a_origin),
    m_d(a_direction),
    m_depth(a_depth),
    m_mint(a_mint),
    m_maxt(a_maxt)
{}

Ray::Ray(const Ray& a_ray)
:   m_o(a_ray.m_o),
    m_d(a_ray.m_d),
    m_depth(a_ray.m_depth),
    m_mint(a_ray.m_mint),
    m_maxt(a_ray.m_maxt)
{}

Ray::~Ray()
{}

Ray& Ray::operator=(const Ray &a_ray)
{
    if (this == &a_ray)
    {
        return (*this);
    }
    
    m_o = a_ray.m_o;
    m_d = a_ray.m_d;
    m_depth = a_ray.m_depth;
    m_mint = a_ray.m_mint;
    m_maxt = a_ray.m_maxt;
    
    return *this;
}