//
//  PerfectSpecular.cpp
//  RayTracer
//

#include "Normal.h"
#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular()
:   BRDF(),
    m_k(0.0),
    m_c(RGBColor(0.0))
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& a_ps)
:   BRDF(a_ps),
    m_k(a_ps.m_k),
    m_c(a_ps.m_c)
{}

PerfectSpecular::~PerfectSpecular()
{}

RGBColor PerfectSpecular::fSample(const Intersection& a_inter, Vector& a_wi, const Vector& a_wo) const
{
	a_wi = a_wo + a_inter.m_normal * dot(a_inter.m_normal, -a_wo) * 2;

	return (m_k * m_c) / dot(a_wi, a_inter.m_normal);
}