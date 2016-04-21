//
//  GlossySpecular.cpp
//  RayTracer
//

#include "math.h"

#include "GlossySpecular.h"

GlossySpecular::GlossySpecular()
:   BRDF(),
    m_k(0.0),
    m_exp(1.0)
{}

GlossySpecular::GlossySpecular(const GlossySpecular& a_gs)
:   BRDF(a_gs),
    m_k(a_gs.m_k),
    m_exp(a_gs.m_exp)
{}

GlossySpecular::~GlossySpecular()
{}

RGBColor GlossySpecular::f(const Intersection& a_inter, const Vector& a_wi, const Vector& a_wo) const
{
    RGBColor L;
    
	Vector t = -a_wi + a_inter.m_normal * (dot(a_inter.m_normal, a_wi)) * 2;
	double l = pow(dot(t, a_wo), m_exp);
	
	L = m_k*l;
	return L;
}