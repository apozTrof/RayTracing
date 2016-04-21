//
//  PerfectDiffuse.cpp
//  RayTracer
//

#define _USE_MATH_DEFINES

#include "math.h"

#include "PerfectDiffuse.h"

PerfectDiffuse::PerfectDiffuse()
:   BRDF(),
    m_k(0.0),
    m_c(0.0)
{}

PerfectDiffuse::PerfectDiffuse(const PerfectDiffuse& a_pd)
:   BRDF(a_pd),
    m_k(a_pd.m_k),
    m_c(a_pd.m_c)
{}

PerfectDiffuse::~PerfectDiffuse()
{}

RGBColor PerfectDiffuse::f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const
{
    return m_k * m_c * M_1_PI;
}
