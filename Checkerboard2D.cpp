//
//
//  Alexandre Guertin 10 143 908
//  Antoine Vella 12 035 861
//  Checkerboard2D.cpp
//  RayTracer
//

#include <math.h>

#include "Checkerboard2D.h"
#include "GeometricObject.h"

Checkerboard2D::Checkerboard2D()
:   m_c1(RGBColor(1.0)),
    m_c2(RGBColor(0.0)),
    m_n(10.0)
{}

Checkerboard2D::Checkerboard2D(const Checkerboard2D& a_cb2)
:   m_c1(a_cb2.m_c1),
    m_c2(a_cb2.m_c2),
    m_n(a_cb2.m_n)
{}

Checkerboard2D::~Checkerboard2D()
{}

RGBColor Checkerboard2D::getColor(const Intersection& a_inter) const
{
	double x = a_inter.m_u;
	double y = a_inter.m_v;

	if (((int)std::floor(x*m_n) + (int)std::floor(y*m_n)) % 2 == 0) 
	{
		return m_c1;
	}
	else
	{
		return m_c2;
	}
}